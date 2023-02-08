#include "State.hpp"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <unordered_map>
// #include "/usr/include/boost/heap/fibonacci_heap.hpp"
#include <iostream>
#include <sstream>
std::vector<int> parse(const char *arg);

void print_res(State *curr)
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
    (void) argc;
    (void) argv;
    if (argc != 2)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tn-puzzle n       <--  randomly generates board of size n * n and solve it" << std::endl;
        std::cout << "    or" << std::endl;
        std::cout << "\tn-puzzle file    <--  parse file and solve it" << std::endl;
        return 0;
    }

    Board init(parse(argv[1]));
    std::cout << init.size << init.tab.size() << std::endl;
    if (!init.is_solvable())
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
        State *curr = opened.top();
        opened.pop();
        std::cout << "Problème.\n" << curr->board.toString() << std::endl;
        curr->isclosed = true;

        int i0 = curr->i0;
        int j0 = curr->j0;
        for (int dr = 0; dr < 4; dr++)
        {
            int new_i = i0 + (dr == 2) - (dr == 0);
            int new_j = j0 + (dr == 1) - (dr == 3);
            if (!(0 <= new_i && new_i < n))
                continue;
            if (!(0 <= new_j && new_j < n))
                continue;

            Board newboard((curr->board).move(i0, j0, new_i, new_j));

            if (newboard.istarget())
            {
                // printf("trouvé\n");
                // print_res(curr->;
                print_res(curr);
                printf("%d %d\n", new_i, new_j);
                all.clear();
                opened.clear();
                exit(0);
            }

            if (all.count(newboard.toString())) {
                State &tomodify = all[newboard.toString()];
                if (!tomodify.isclosed && tomodify.f > curr->f + 1)
                {
                    (*tomodify.handle)->f = curr->f + 1;
                    opened.increase(tomodify.handle);
                }
            }
            else    {
                State state(newboard, new_i, new_j, curr, curr->f + 1);
                all.emplace(newboard.toString(), state);
                all[newboard.toString()].handle = opened.push(&all[newboard.toString()]);
            }
        }
    }

    return 0;
}
