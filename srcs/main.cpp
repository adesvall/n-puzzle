#include "main.hpp"
#include <cstdio>
#include <fstream>
#include <cstdlib>

void recursive_print(const State *curr, std::ofstream& out)
{
    if (curr->parent)
    {
        recursive_print(curr->parent, out);
        out << curr->i0 << ' ' << curr->j0 << std::endl;
    }
}

void print_res(const State *curr)
{
    std::ofstream out("sol.txt");
    recursive_print(curr, out);
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
    if (!init.is_solvable())
    {
        std::cout << "Not solvable." << std::endl;
        return 0;
    }
    // ida_star(init);
    a_star(init);
    return 0;
}
