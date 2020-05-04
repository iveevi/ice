#ifndef CLOCK_H_
#define CLOCK_H_

#include "chip.h"

namespace std_seq_chips {
	const double __epsilon = 1e-10;

	template <int millis>
	const chip &__make_clock() {
		chip *__clk_ptr = new chip({0}, {1}, [](const pack_t &in, pack_t &out) {
			out[0][0] = (clock() % (millis * CLOCKS_PER_SEC / 1000) == 0);
		});

		return *__clk_ptr;
	}
}

#endif
