#include "main.hpp"
#include <limits>
#include <cmath>
#include <unordered_set>
#include <list>

using namespace std;

list<int>   make_fringe_list()
{
    list<int> res;
    size_t size = Board::size;
    int j = 0;
    for (; j < (int)size; j++)
        res.push_back(size*(size-1) + j);
    j = size - 2;
    for (; j >= 0; j--)
        res.push_back(j*size + size-1);
    return res;
}

string fringe_partial_search(Board& init)
{
    string res;

    Board::emptySelection();
    // res += a_star(init, true);
    while (Board::size > 3)
    {
        list<int> fringe = make_fringe_list();
        list<int>::iterator it = fringe.begin();
        while (it!=fringe.end() && Board::size % 2)
        {
            Board::addSelection(*it++);
            Board::addSelection(*it++);
            if (it != fringe.end() && it != ----fringe.end())
                Board::addSelection(*it++);
            res += a_star(init);
            cout << init.toString() << Board::size << endl;
        }
        list<int>::reverse_iterator itr = fringe.rbegin();
        while (itr!=fringe.rend() && Board::size % 2 == 0)
        {
            Board::addSelection(*itr++);
            Board::addSelection(*itr++);
            if (itr != fringe.rend() && itr != ----fringe.rend())
                Board::addSelection(*itr++);
            res += a_star(init);
            cout << init.toString() << Board::size << endl;
        }

        Board::emptySelection();
        init = init.remove_fringe();
        cout << init.toString() << Board::size << endl;
    }
    res += ida_star(init);
    cout << init.toString() << Board::size << endl;

    return res;
}

string fringe_first_search(Board& init)
{
    string res;

    while (Board::size > 3)
    {
        Board::bottomSelection();
        res += ida_star(init);
        cout << init.toString() << Board::size << endl;

        Board::fringeSelection();
        res += ida_star(init);
        cout << init.toString() << Board::size << endl;

        Board::emptySelection();
        init = init.remove_fringe();
        cout << init.toString() << Board::size << endl;
    }
    res += ida_star(init);
    return res;
}



