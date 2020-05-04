#ifndef STANDARD_H_
#define STANDARD_H_

#include "chip.h"

/* This file contains common
 * chips, for the convenience of
 * other users: instead of having
 * to create these chips from
 * bottom up, they can use higher
 * level chips or the chip they want
 * to make itself. */

namespace std_chips {
	chip __not({1}, {1}, [](const pack_t &in, pack_t &out) {
		out[0][0] = !in[0][0];
	});

	chip __and({2}, {1}, [](const pack_t &in, pack_t &out) {
		out[0][0] = in[0][0] & in[0][1];
	});

	chip __or({2}, {1}, [](const pack_t &in, pack_t &out) {
		out[0][0] = in[0][0] | in[0][1];
	});
}

#endif
