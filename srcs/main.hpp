#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include "State.hpp"

std::vector<int> parse(const char *arg);
void print_res(const State *curr);
void a_star(Board& init);
void ida_star(Board& init);


#endif