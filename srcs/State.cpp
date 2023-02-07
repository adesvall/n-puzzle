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
    return f + g > rhs.f + rhs.g; 
}
