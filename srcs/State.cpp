#include "State.hpp"

State::State(Board board, int i0, int j0, State* parent, int f)
: board(board), i0(i0), j0(j0), parent(parent), f(f)
{
    g = board.estimate_cost();
}

State::~State()
{}


bool State::operator<(const State& rhs) const
{
    return f + g < rhs.f + rhs.g; 
}
