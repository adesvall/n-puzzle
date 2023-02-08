#include "State.hpp"

State::State()
{}

State::State(Board board, int i0, int j0, State* parent, int f)
: f(f), board(board), i0(i0), j0(j0), parent(parent), isclosed(false)
{
    g = board.estimate_cost();
}

State::~State()
{}


bool State::operator<(const State& rhs) const
{
    if (g == rhs.g)
        return f > rhs.f;
    return g > rhs.g;
    
    if (f + g == rhs.f + rhs.g)
        return g > rhs.g;
    return f + g > rhs.f + rhs.g; 
}


// e(x) = 2 * 4 / 16 + 4 * 4 / 16 + 8 * 4 / 16 = 3.5
// ratio = 9232897 / 4199164 = 2.2