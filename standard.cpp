#include "chip.h"

/* This file contains common
 * chips, for the convenience of
 * other users: instead of having
 * to create these chips from
 * bottom up, they can use higher
 * level chips or the chip they want
 * to make itself. */

chip __and({1, 1}, {1}, [](const pack &in, pack &out) {
        out[0][0] = in[0][0] & in[1][0];
});

namespace std_chips {
}
