#include "al5.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


CAMLprim value ml_al_install_audio(value unit)
{
    CAMLparam1(unit);
    if (!al_install_audio()) {
        caml_failwith("al_install_audio");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_audio_installed, Val_bool)

ml_function_noarg(al_uninstall_audio)

ml_function_noarg_ret(al_get_allegro_audio_version, Val_int)


#define SampleId_val(v) (*((ALLEGRO_SAMPLE_ID *)Data_custom_val(v)))

static struct custom_operations allegro_sample_id_ops = {
  "org.allegro5.sample_id",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

static value alloc_sample_id(ALLEGRO_SAMPLE_ID c_sample_id)
{
    CAMLparam0();
    CAMLlocal1(v);
    v = caml_alloc_custom(&allegro_sample_id_ops, sizeof(c_sample_id), 1, 256);
    SampleId_val(v) = c_sample_id;
    CAMLreturn(v);
}


enum {
    ML_PLAYMODE_ONCE,
    ML_PLAYMODE_LOOP,
    ML_PLAYMODE_LOOP_ONCE,
    ML_PLAYMODE_BIDIR,
};

#if ALLEGRO_VERSION_INT < 0x05020800
    #define ALLEGRO_PLAYMODE_LOOP_ONCE ALLEGRO_PLAYMODE_ONCE
#endif

value convert_playmode_from_c(int c_playmode)
{
    int playmode;
    switch (c_playmode) {
        case ALLEGRO_PLAYMODE_ONCE: playmode = ML_PLAYMODE_ONCE; break;
        case ALLEGRO_PLAYMODE_LOOP: playmode = ML_PLAYMODE_LOOP; break;
#if ALLEGRO_VERSION_INT >= 0x05020800
        case ALLEGRO_PLAYMODE_LOOP_ONCE: playmode = ML_PLAYMODE_LOOP_ONCE; break;
#endif
        case ALLEGRO_PLAYMODE_BIDIR: playmode = ML_PLAYMODE_BIDIR; break;
        default: playmode = -1;
    }
    return Val_int(playmode);
}

value convert_playmode_from_ml(value playmode)
{
    CAMLparam1(playmode);
    static int const playmode_conv[] = {
        [ML_PLAYMODE_ONCE] = ALLEGRO_PLAYMODE_ONCE,
        [ML_PLAYMODE_LOOP] = ALLEGRO_PLAYMODE_LOOP,
        [ML_PLAYMODE_LOOP_ONCE] = ALLEGRO_PLAYMODE_LOOP_ONCE,
        [ML_PLAYMODE_BIDIR] = ALLEGRO_PLAYMODE_BIDIR,
    };
    CAMLreturnT(int, playmode_conv[Int_val(playmode)]);
}


ml_function_1arg_ret(al_load_sample, String_val, Val_ptr)

CAMLprim value ml_al_save_sample(value filename, value spl)
{
    CAMLparam2(filename, spl);
    bool success = al_save_sample(String_val(filename), Ptr_val(spl));
    CAMLreturn(Val_bool(success));
}

ml_function_1arg(al_destroy_sample, Ptr_val)

CAMLprim value ml_al_reserve_samples(value count)
{
    CAMLparam1(count);
    if (!al_reserve_samples(Int_val(count))) {
        caml_failwith("al_reserve_samples");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_play_sample(value spl, value gain, value pan, value speed, value loop)
{
    CAMLparam5(spl, gain, pan, speed, loop);
    ALLEGRO_SAMPLE_ID c_spl_id;
    bool success = al_play_sample(Ptr_val(spl),
        Double_val(gain), Double_val(pan), Double_val(speed),
        convert_playmode_from_ml(loop),
        &c_spl_id);
    if (success) {
        CAMLreturn(caml_alloc_some(alloc_sample_id(c_spl_id)));
    }
    CAMLreturn(Val_none);
}

CAMLprim value ml_al_stop_sample(value spl_id)
{
    CAMLparam1(spl_id);
    al_stop_sample(&SampleId_val(spl_id));
    CAMLreturn(Val_unit);
}

ml_function_noarg(al_stop_samples)


CAMLprim value ml_al_load_audio_stream(value filename, value buffer_count, value samples)
{
    CAMLparam3(filename, buffer_count, samples);
    ALLEGRO_AUDIO_STREAM *c_stream = al_load_audio_stream(
        String_val(filename), Long_val(buffer_count), Int_val(samples));
    CAMLreturn(Val_ptr(c_stream));
}

ml_function_1arg(al_destroy_audio_stream, Ptr_val)

ml_function_1arg_ret(al_get_audio_stream_event_source, Ptr_val, Val_ptr)

ml_function_1arg_ret(al_rewind_audio_stream, Ptr_val, Val_bool)

ml_function_1arg_ret(al_detach_audio_stream, Ptr_val, Val_bool)

ml_function_1arg_ret(al_get_audio_stream_playing, Ptr_val, Val_bool)

CAMLprim value ml_al_set_audio_stream_playing(value stream, value playing)
{
    CAMLparam2(stream, playing);
    bool success = al_set_audio_stream_playing(Ptr_val(stream), Bool_val(playing));
    CAMLreturn(Val_bool(success));
}

ml_function_1arg_ret(al_get_audio_stream_playmode, Ptr_val, convert_playmode_from_c)

CAMLprim value ml_al_set_audio_stream_playmode(value stream, value playmode)
{
    CAMLparam2(stream, playmode);
    bool success = al_set_audio_stream_playmode(Ptr_val(stream), convert_playmode_from_ml(playmode));
    CAMLreturn(Val_bool(success));
}


ml_function_noarg_ret(al_get_default_mixer, Val_ptr)

CAMLprim value ml_al_attach_audio_stream_to_mixer(value stream, value mixer)
{
    CAMLparam2(stream, mixer);
    bool success = al_attach_audio_stream_to_mixer(Ptr_val(stream), Ptr_val(mixer));
    CAMLreturn(Val_bool(success));
}
