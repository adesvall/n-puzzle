#include "Board.hpp"

class State
{
public:

    int     f;
    int     g;
    Board   board;
    int     i0;
    int     j0;
    State   *parent;

public:
    State(Board board, int i0, int j0, State* parent, int f );
    ~State();
    bool operator<(const State& rhs) const;
};
