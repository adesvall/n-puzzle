#include "State.hpp"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <unordered_map>
// #include "/usr/include/boost/heap/fibonacci_heap.hpp"
#include <iostream>
#include <sstream>
std::vector<int> parse(const char *arg);

void print_res(const State *curr)
{
    std::stringstream res;

    if (!curr->parent)
        return;
    res << curr->i0 << ' ' << curr->j0 << std::endl;
    print_res(curr->parent);
    std::cout << res.str();
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tn-puzzle n       <--  randomly generates board of size n * n and solve it" << std::endl;
        std::cout << "    or" << std::endl;
        std::cout << "\tn-puzzle file    <--  parse file and solve it" << std::endl;
        return 0;
    }

    Board init(parse(argv[1]));
    // std::cout << init.size << init.tab.size() << std::endl;
    if (false && !init.is_solvable())
    {
        std::cout << "Not solvable." << std::endl;
        return 0;
    }
    int n = init.size;
    // int inittab[12] = {4, 9, 0, 5,   10, 7, 1, 2,   11, 8, 3, 6};
    // Board init(inittab);
    int ij = init.get_empty_coords();

    boost::heap::fibonacci_heap<State*, boost::heap::mutable_<true>, boost::heap::compare<PointerCompare<State>>>    opened;
    std::allocator<std::pair<Board, State>> a;
    std::unordered_map<std::string, State> all(a);

    State state(init, ij / n, ij % n, (State*)NULL, 0);
    all.emplace(init.toString(), state); // double copie
    all[init.toString()].handle = opened.push(&all[init.toString()]);

    while (!opened.empty())
    {

        if (all.count("0,1,2,3\n4,5,6,7\n8,9,10,11\n12,13,14,15\n"))
        {
            // printf("trouvé\n");
            // print_res(curr->;
            State* curr = &all["0,1,2,3\n4,5,6,7\n8,9,10,11\n12,13,14,15\n"];
            print_res(curr);
            all.clear();
            opened.clear();
            exit(0);
        }
        // std::cout << "size:" << opened.size() << std::endl;
        // if (opened.size() >= 100)
        // {
        //     for (int i=0; i<100; i++)
        //     {
        //         std::cout << opened.top()->f + opened.top()->g << std::endl;
        //         opened.pop();
        //     }
        //     exit(1);
        // }
        State *curr = opened.top();
        opened.pop();
        if (true)
        {
            std::cout << "opened : " << opened.size() << "  all: " << all.size() << std::endl;
            std::cout << curr->board.toString() << curr->g << " " << curr->h << std::endl;
        }
        curr->isclosed = true;
        // if (curr->f == 6)
        //     exit(100);
        std::vector<State> neighbors = curr->getNeibours();
        for (std::vector<State>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            std::string newboard = it->board.toString();

            if (all.count(newboard)) {
                State &tomodify = all[newboard];
                if (!tomodify.isclosed && tomodify.g > curr->g + 1)
                {
                    (*tomodify.handle)->g = curr->g + 1;
                    opened.update(tomodify.handle);
                }
            }
            else    {
                all.emplace(newboard, *it);
                all[newboard].handle = opened.push(&all[newboard]);
            }
        }
    }
    std::cout << all.count("0,1,2,3\n4,5,6,7\n8,9,10,11\n12,13,14,15\n") << std::endl;
    return 0;
}
