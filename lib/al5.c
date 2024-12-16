#include "al5.h"


int convert_flags_(int flags_from, int flags_num, int const flags_conv[][2], int from_index)
{
    int flags_to = 0;
    for (int i = 0; i < flags_num; ++i) {
        if ((flags_from & flags_conv[i][from_index]) == flags_conv[i][from_index]) {
            flags_to |= flags_conv[i][1 - from_index];
        }
    }
    return flags_to;
}
