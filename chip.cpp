#include <iostream>

#include "chip.h"

std::string chip::unpack(const pack &in)
{
	std::string out;

	size_t counter = 0;

	for (auto row : in) {
		out += std::to_string(counter++) + ":\t[";
		for (auto i : row)
			out += (i ? "1" : "0");
		out += "]\n";
	}

	return out;
}

chip::chip(const specs &in, const specs &out, const circuit &c)
	: input(in), output(out), type(l_immediate)
{
	functor = c;
}

const pack &chip::operator()(const pack &in) const
{
        if (type != l_immediate) {
                std::cout << "[CHIP]: Only immediate modes are available." << std::endl;
                return in;
        }

        pack *out = new pack(input.size());

        for (size_t i = 0; i < out->size(); i++)
                out[i].assign(input[i], row(input[i]));

        functor(in, *out);

        return *out;
}
