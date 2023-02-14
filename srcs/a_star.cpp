#include "main.hpp"
#include <unordered_map>

void a_star(Board& init)
{
    boost::heap::fibonacci_heap<State*, boost::heap::mutable_<true>, boost::heap::compare<PointerCompare<State>>>    opened;
    std::allocator<std::pair<Board, State>> a;
    std::unordered_map<std::string, State> all(a);

    int n = init.size;
    // std::string goalstr =  "0,1,2,3\n4,5,6,7\n8,9,10,11\n12,13,14,15\n";
    std::string goalstr =  Board(n).toString();


    int ij = init.get_empty_coords();
    State state(init, ij / n, ij % n, (State*)NULL, 0);
    all.emplace(init.toString(), state);
    all[init.toString()].handle = opened.push(&all[init.toString()]);

    while (!opened.empty())
    {
        if (all.count(goalstr))
        {
            // printf("trouvé\n");
            // print_res(curr->;
            State* curr = &all[goalstr];
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
            std::cout << "opened : " << opened.size() << "\tall: " << all.size();
            // std::cout << curr->board.toString();
            std::cout << "\tf: " << curr->g+curr->h << " g: " << curr->g << " h: " << curr->h << std::endl;
        }
        curr->isclosed = true;
        // if (curr->f == 6)
        //     exit(100);
        std::vector<State> neighbors = curr->getNeighbors();
        for (std::vector<State>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            std::string newboard = it->board.toString();

            if (all.count(newboard)) {
                State &tomodify = all[newboard];
                if (!tomodify.isclosed && tomodify.g > curr->g + 1)
                {
                    (*tomodify.handle)->g = curr->g + 1;
                    (*tomodify.handle)->parent = curr;
                    opened.update(tomodify.handle);
                }
            }
            else    {
                all.emplace(newboard, *it);
                all[newboard].handle = opened.push(&all[newboard]);
            }
        }
    }
    std::cout << "Fatal no solution found after exploring everything." << std::endl;
}