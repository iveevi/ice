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

		out += "]";
		if (counter == in.size())
			break;

		out += "\n";
	}

	return out;
}

chip::chip(const specs &in, const specs &out, const circuit &c)
	: input(in), output(out), type(l_immediate)
{
	functor = c;
}

size_t chip::pins() const
{
	size_t counter = 0;

	for (size_t i : input)
		counter += i;

	for (size_t i : output)
		counter += i;

	return counter;
}

size_t chip::pins_in() const
{
	size_t counter = 0;

	for (size_t i : input)
		counter += i;

	return counter;
}

size_t chip::pins_out() const
{
	size_t counter = 0;

	for (size_t i : output)
		counter += i;

	return counter;
}

const specs &chip::specs_in() const
{
	return input;
}

const specs &chip::specs_out() const
{
	return output;
}

const pack &chip::operator()(const pack &in) const
{
        if (type != l_immediate) {
                std::cout << "[CHIP]: Only immediate modes are available." << std::endl;
                return in;
        }

        pack *out = new pack(output.size());

        for (size_t i = 0; i < output.size(); i++)
                (*out)[i].assign(output[i], false);

        functor(in, *out);

        return *out;
}
