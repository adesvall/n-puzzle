#include "Board.hpp"
#include <hashtable.h>
#include <sstream>

Board::Board()
{}

Board::Board(const int tab[12])
{
    for (int i = 0; i < 12; i++) {
        this->tab[i] = tab[i];
    }
    // this->tab = tab; ça prend l'addresse ou ça copie ?
}

// Board::Board(Board& ref) : Board(ref.tab)
// {}





float Board::estimate_cost() const
{
    float res = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int dist = abs(i - tab[4*i+j] / 4) + abs(j - tab[4*i+j] % 4);
            res += dist;
        }
    }
    return res;
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

// bool Board::operator==(Board &rhs) const   {
    
//     for (int i = 0; i < 12; i++)
//     {
//         if (tab[i] != rhs.tab[i])
//             return false;
//     }
//     return true;
// }

std::string Board::toString()  const
{
    std::stringstream stream;

    for (int i = 0; i < 12; i++)
    {
        stream << tab[i];
        stream << ',';           
    }
    return stream.str();
}

// namespace std
// {
//   template <>
//   struct hash<Board>
//   {
//     size_t operator()(Board const & b) const
//     {
//         hash<std::string> hasheur;
//         return hasheur(b.toString());
//     }
//   };
// }