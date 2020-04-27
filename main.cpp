#include <iostream>

#include "chip.h"

using namespace std;

int main()
{
        pack a = {{true, false, false}, {true, false, true, false}, {true, false}};

        cout << "a:" << endl << chip::unpack(a) << endl;
        
        chip __and({1, 1}, {1}, [](const pack &in, pack &out) {
                out[0][0] = in[0][0] & in[1][0];
        });

        pack first = {{true}, {false}};
        pack second = {{true}, {true}};

        cout << endl << "first: " << chip::unpack(__and(first)) << endl;
        cout << endl << "second: " << chip::unpack(__and(second)) << endl;
}
