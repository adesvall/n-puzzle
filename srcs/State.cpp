#include "State.hpp"


State::State()
{}

State::State(int n) : board(n)
{}

State::State(Board board, int i0, int j0, const State* parent, int g)
: g(g), board(board), i0(i0), j0(j0), parent(parent), isclosed(false)
{
    h = board.estimate_cost();
}

State::~State()
{}

std::vector<State> State::getNeibours() const
{
    std::vector<State> res;

    for (int dr = 0; dr < 4; dr++)
    {
        int new_i = i0 + (dr == 2) - (dr == 0);
        int new_j = j0 + (dr == 1) - (dr == 3);
        if (!(0 <= new_i && new_i < (int)board.size))
            continue;
        if (!(0 <= new_j && new_j < (int)board.size))
            continue;
        State state(board.move(i0, j0, new_i, new_j), new_i, new_j, this, g + 1);
        res.push_back(state);
    }
    return res;
}


bool State::operator<(const State& rhs) const
{
    // if (h == rhs.h)
    //     return g > rhs.g;
    // return h > rhs.h;
    
    if (g + h == rhs.g + rhs.h)
        return h > rhs.h;
    return g + h > rhs.g + rhs.h; 
}


