#ifndef CHIP_H_
#define CHIP_H_

#include <bitset>
#include <functional>
#include <string>
#include <vector>

typedef std::vector <std::vector <bool>> pack;
typedef std::vector <bool> row;
typedef std::vector <size_t> specs;
typedef std::function <void (const pack &, pack &)> circuit;

/**
 * @brief Represents an
 * arbitrary chip, with
 * I as input and O as
 * output.
 */
class chip {
public:
	enum label {
		l_immediate,
		l_graph,
	};

	struct node {
		specs bits_in;
		specs bits_out;
		circuit transformer;
	};

	static std::string unpack(const pack &);
private:
	specs input;
	specs output;

	label type;

	node *graph;
	
	circuit functor;
public:
	chip(const std::string &);

	chip(const specs &, const specs &, const circuit &);

	const pack &operator()(const pack &) const;
};

#endif
