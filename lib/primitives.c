#include "graphics.h"

#include <allegro5/allegro_primitives.h>


ml_function_noarg_ret(al_get_allegro_primitives_version, Val_int)

CAMLprim value ml_al_init_primitives_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_primitives_addon()) {
        caml_failwith("al_init_primitives_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_primitives_addon_initialized, Val_bool)

ml_function_noarg(al_shutdown_primitives_addon)


CAMLprim value ml_al_draw_line(value pos1, value pos2, value color, value thickness)
{
    CAMLparam4(pos1, pos2, color, thickness);
    al_draw_line(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_triangle(value pos1, value pos2, value pos3, value color, value thickness)
{
    CAMLparam5(pos1, pos2, pos3, color, thickness);
    al_draw_triangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(pos3), PosY_val(pos3),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_triangle(value pos1, value pos2, value pos3, value color)
{
    CAMLparam4(pos1, pos2, pos3, color);
    al_draw_filled_triangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(pos3), PosY_val(pos3),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rectangle(value pos1, value pos2, value color, value thickness)
{
    CAMLparam4(pos1, pos2, color, thickness);
    al_draw_rectangle(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_rectangle(value pos1, value pos2, value color)
{
    CAMLparam3(pos1, pos2, color);
    al_draw_filled_rectangle(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rounded_rectangle(value pos1, value pos2, value r, value color, value thickness)
{
    CAMLparam5(pos1, pos2, r, color, thickness);
    al_draw_rounded_rectangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(r), PosY_val(r),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_rounded_rectangle(value pos1, value pos2, value r, value color)
{
    CAMLparam4(pos1, pos2, r, color);
    al_draw_filled_rounded_rectangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(r), PosY_val(r),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_pieslice(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_pieslice(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_pieslice_bytecode(value * argv, int argc)
{
    return ml_al_draw_pieslice(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_filled_pieslice(value cpos, value r, value start_theta, value delta_theta, value color)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    al_draw_filled_pieslice(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_ellipse(value cpos, value r, value color, value thickness)
{
    CAMLparam4(cpos, r, color, thickness);
    al_draw_ellipse(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_ellipse(value cpos, value r, value color)
{
    CAMLparam3(cpos, r, color);
    al_draw_filled_ellipse(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_circle(value cpos, value r, value color, value thickness)
{
    CAMLparam4(cpos, r, color, thickness);
    al_draw_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color),
        Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_circle(value cpos, value r, value color)
{
    CAMLparam3(cpos, r, color);
    al_draw_filled_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_arc(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_arc(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_arc_bytecode(value * argv, int argc)
{
    return ml_al_draw_arc(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_elliptical_arc(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_elliptical_arc(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_elliptical_arc_bytecode(value * argv, int argc)
{
    return ml_al_draw_elliptical_arc(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}


static void convert_points(value points, float c_points[][2])
{
    CAMLparam1(points);
    int point_count = Wosize_val(points);
    CAMLlocal1(p);
    for (int i = 0; i < point_count; ++i) {
        p = Field(points, i);
        c_points[i][0] = Double_val(Field(p, 0));
        c_points[i][1] = Double_val(Field(p, 1));
    }
    CAMLreturn0;
}

enum {
    ML_LINE_JOIN_NONE,
    ML_LINE_JOIN_BEVEL,
    ML_LINE_JOIN_ROUND,
};
enum {
    ML_LINE_JOIN_MITER,
};

enum {
    ML_LINE_CAP_NONE,
    ML_LINE_CAP_SQUARE,
    ML_LINE_CAP_ROUND,
    ML_LINE_CAP_TRIANGLE,
    ML_LINE_CAP_CLOSED,
};

static int convert_line_join(value join_style)
{
    CAMLparam1(join_style);
    if (Is_block(join_style)) {
        CAMLreturnT(int, ALLEGRO_LINE_JOIN_MITER);
    }
    int c_join_style = (int[]){
            [ML_LINE_JOIN_NONE] = ALLEGRO_LINE_JOIN_NONE,
            [ML_LINE_JOIN_BEVEL] = ALLEGRO_LINE_JOIN_BEVEL,
            [ML_LINE_JOIN_ROUND] = ALLEGRO_LINE_JOIN_ROUND,
        }[Int_val(join_style)];
    CAMLreturnT(int, c_join_style);
}

static int convert_line_cap(value cap_style)
{
    CAMLparam1(cap_style);
    int c_cap_style = (int[]){
            [ML_LINE_CAP_NONE] = ALLEGRO_LINE_CAP_NONE,
            [ML_LINE_CAP_SQUARE] = ALLEGRO_LINE_CAP_SQUARE,
            [ML_LINE_CAP_ROUND] = ALLEGRO_LINE_CAP_ROUND,
            [ML_LINE_CAP_TRIANGLE] = ALLEGRO_LINE_CAP_TRIANGLE,
            [ML_LINE_CAP_CLOSED] = ALLEGRO_LINE_CAP_CLOSED,
        }[Int_val(cap_style)];
    CAMLreturnT(int, c_cap_style);
}

CAMLprim value ml_al_draw_polyline(value vertices, value join_style, value cap_style, value color, value thickness)
{
    CAMLparam5(vertices, join_style, cap_style, color, thickness);
    int vertex_count = Wosize_val(vertices);
    float c_vertices[vertex_count][2];
    convert_points(vertices, c_vertices);
    float miter_limit = Is_block(join_style) ? Double_val(Field(join_style, 0)) : 0.f;
    al_draw_polyline((float *)c_vertices, sizeof(*c_vertices), vertex_count,
        convert_line_join(join_style), convert_line_cap(cap_style),
        AlColor_val(color), Double_val(thickness), miter_limit);
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_polygon(value vertices, value join_style, value color, value thickness)
{
    CAMLparam4(vertices, join_style, color, thickness);
    int vertex_count = Wosize_val(vertices);
    float c_vertices[vertex_count][2];
    convert_points(vertices, c_vertices);
    float miter_limit = Is_block(join_style) ? Double_val(Field(join_style, 0)) : 0.f;
    al_draw_polygon((float *)c_vertices, vertex_count, convert_line_join(join_style),
        AlColor_val(color), Double_val(thickness), miter_limit);
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_polygon(value vertices, value color)
{
    CAMLparam2(vertices, color);
    int vertex_count = Wosize_val(vertices);
    float c_vertices[vertex_count][2];
    convert_points(vertices, c_vertices);
    al_draw_filled_polygon((float *)c_vertices, vertex_count, AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_polygon_with_holes(value polygon, value holes, value color)
{
    CAMLparam3(polygon, holes, color);
    CAMLlocal1(h);
    int hole_count = 0;
    for (h = holes; h != Val_emptylist; h = Field(h, 1)) {
        ++hole_count;
    }
    int vertex_counts[1 + hole_count + 1];
    vertex_counts[0] = Wosize_val(polygon);
    int vertex_total = vertex_counts[0];
    int i = 0;
    for (h = holes; h != Val_emptylist; h = Field(h, 1)) {
        ++i;
        vertex_counts[i] = Wosize_val(Field(h, 0));
        vertex_total += vertex_counts[i];
    }
    vertex_counts[1 + hole_count] = 0;
    float c_vertices[vertex_total][2];
    convert_points(polygon, c_vertices);
    int pos = 0;
    for (h = holes; h != Val_emptylist; h = Field(h, 1)) {
        pos += vertex_counts[i];
        convert_points(Field(h, 0), c_vertices + pos);
    }
    al_draw_filled_polygon_with_holes((float *)c_vertices, vertex_counts, AlColor_val(color));
    CAMLreturn(Val_unit);
}
