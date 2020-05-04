#include <iostream>
#include <vector>

#include <cmath>

#include "chip.h"
#include "clock.h"
#include "standard.h"
#include "aug_chip.h"

#define DELAY 100

using namespace std;

using namespace std_chips;
using namespace std_seq_chips;

vector <chip> coll = {__not, __and, __or};

vector <string> corr = {"NOT", "AND", "OR"};

bool increment(pack_t &ins)
{
	size_t i = 0;
	size_t j = 0;

	while (true) {
		if (i >= ins.size())
			return false;

		if (ins[i][j]) {
			ins[i][j] = false;
		} else {
			ins[i][j] = true;
			break;
		}

		if (j + 1 >= ins[i].size()) {
			j = 0;
			i++;
		} else {
			j++;
		}
	}

	return true;
}

void process_raw(const chip &cp, const pack_t &ins)
{
	for (size_t i = 0; i < ins.size(); i++) {
		for (size_t j = 0; j < ins[i].size(); j++)
			cout << (ins[i][j] ? "1" : "0");
	}
	
	cout << "|";

	pack_t out = cp(ins);

	for (size_t i = 0; i < out.size(); i++) {
		for (size_t j = 0; j < out[i].size(); j++)
			cout << (out[i][j] ? "1" : "0");
	}

	cout << endl;
}

void process_pack_ted(const chip &cp, const pack_t &ins)
{
	for (size_t i = 0; i < ins.size(); i++) {
		cout << "[";
		for (size_t j = 0; j < ins[i].size(); j++)
			cout << (ins[i][j] ? "1" : "0");
		cout << "]";
	}
	
	cout << "|";

	pack_t out = cp(ins);

	for (size_t i = 0; i < out.size(); i++) {
		cout << "[";
		for (size_t j = 0; j < out[i].size(); j++)
			cout << (out[i][j] ? "1" : "0");
		cout << "]";
	}

	cout << endl;
}

void process(size_t i)
{
	cout << string(30, '=') << endl;
	cout << "TRUTH TABLE: [" << corr[i] << "]" << endl;
	cout << string(30, '=') << endl;
	
	cout << endl << "RAW BINARY:" << endl;
	cout << string(coll[i].pins() + 1, '_') << endl;

	specs input = coll[i].specs_in();

        pack_t ins = pack_t(input.size());

	bool ok;

        for (size_t i = 0; i < input.size(); i++)
                ins[i].assign(input[i], false);

	do {
		process_raw(coll[i], ins);
		ok = increment(ins);
	} while (ok);

	cout << endl;
	
	cout << endl << "PACKED BINARY:" << endl;
	cout << string(coll[i].pins() + 1, '_') << endl;
        
	for (size_t i = 0; i < input.size(); i++)
                ins[i].assign(input[i], false);

	do {
		process_pack_ted(coll[i], ins);
		ok = increment(ins);
	} while (ok);

	cout << endl;
}

struct __dff_mem {
	bool prev;
	chip __clk;
};

int main()
{
	for (size_t i = 0; i < coll.size(); i++)
		process(i);

	aug_chip <__dff_mem> __dff({1}, {1}, [&](const pack_t &in, pack_t &out, __dff_mem &data) {
			out[0][0] = false;

			if (data.__clk({})[0][0]) {
				out[0][0] = data.prev;
				data.prev = in[0][0];
			}
	}, {false, __make_clock <100> ()});

	srand(clock());

	int sig;

	cout << "Enter signal: ";
	cin >> sig;

	pack_t ins = {{sig % 2}};

	cout << "CPS " << CLOCKS_PER_SEC << endl;
	while (true) {
		if (__dff(ins)[0][0]) {
			cout << "SENT SIGNAL @ " << clock() << endl;
		}
	}
}
