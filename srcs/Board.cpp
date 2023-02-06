#include "Board.hpp"

Board::Board(const int tab[12])
{
    for (int i = 0; i < 12; i++) {
        this->tab[i] = tab[i];
    }
    // this->tab = tab; ça prend l'addresse ou ça copie ?
}

float Board::estimate_cost() const
{
    return 0;
}

Board Board::move(int i0, int j0, int new_i, int new_j)   const
{
    Board res(this->tab);

    res.tab[4 * i0 + j0] = res.tab[4 * new_i + new_j];
    res.tab[4 * new_i + new_j] = 0;
    return res;
}

int Board::get_empty_coords()   const
{
    for (int i = 0; i < 12; i++) {
        if (tab[i] == 0)
            return i;
    }
    return -1;
}

bool Board::istarget()  const
{
    for (int i = 0; i < 12; i++)
    {
        if (tab[i] != i)
            return false;
    }
    return true;
}
