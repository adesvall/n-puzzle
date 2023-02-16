#include "main.hpp"
#include <limits>
#include <cmath>
#include <unordered_set>
#include <list>

using namespace std;

string fringe_first_search(Board& init)
{
    string res;

    Board::side = true;
    while (init.size > 3)
    {
        res += a_star(init);
        cout << init.toString() << endl;

        Board::fringe = true;
        res += a_star(init);
        cout << init.toString() << endl;
        Board::fringe = false;

        init = init.remove_fringe();
        cout << init.toString() << endl;
    }
    Board::side = false;
    res += ida_star(init);
    return res;
}


