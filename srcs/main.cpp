#include "State.hpp"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <unordered_map>



int get_empty_coords(int *board)
{
    for (int i = 0; i < 12; i++) {
        if (board[i] == 0)
            return i;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int n = 4;
    Board init((int[12]){4, 3, 1, 7,    0, 9, 2, 6,     5, 8, 10, 11});
    int ij = init.get_empty_coords();


    std::priority_queue<State> opened;
    // std::unordered_map<int[12], State&> openedmap;
    std::vector<State*> closed;


    opened.emplace(init, ij / n, ij % n, (State*)NULL, 0);
    // openedmap.insert(board, (State&)opened.top());

    while (!opened.empty())
    {
        const State &curr = opened.top();
        opened.pop();

        int i0 = curr.i0;
        int j0 = curr.j0;
        for (int dr = 0; dr < 4; dr++)
        {
            int new_i = i0 + (dr == 2) - (dr == 0);
            int new_j = j0 + (dr == 1) - (dr == 3);
            if (!(0 <= new_i && new_i < 3))
                continue;
            if (!(0 <= new_j && new_j < 4))
                continue;

            Board newboard = curr.board.move(i0, j0, new_i, new_j);

            if (newboard.istarget())
            {
                printf("trouvé\n");
                // print_res(curr);
                printf("%d, %d\n", new_i, new_j);
                exit(0);
            }

            // if h not in openset:
            //     openset[h] = State(f+1, newboard, new_empty, curr)
            //     heapq.heappush(opened, openset[h])
            // elif f+1 < openset[h].f:
            //     openset[h].f = f+1
            //     heapq.heapify(opened)
        }
    }

    return 0;
}
