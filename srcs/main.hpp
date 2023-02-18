#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include "State.hpp"

std::vector<int> parse(const char *arg);
void print_res(std::string moves);
std::string a_star(Board& init, bool flex = false);
std::string ida_star(Board& init);
std::string fringe_first_search(Board& init);
std::string fringe_partial_search(Board& init);

template<typename T>
void recursive_print(const State *curr, T& out)
{
    if (curr->parent)
    {
        recursive_print(curr->parent, out);
        out << curr->i0 << ' ' << curr->j0 << std::endl;
    }
}


#endif