#include "main.hpp"
#include <cstdio>
#include <fstream>
#include <cstdlib>

void print_res(std::string moves)
{
    std::ofstream out("sol.txt");
    out << moves;
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
    // a_star(init);
    // std::cout << init.fringe << std::endl;
    // print_res(a_star(init));
    // print_res(ida_star(init));
    // print_res(fringe_first_search(init));
    print_res(fringe_partial_search(init));
    return 0;
}
