#include "Board.hpp"
#include <hashtable.h>
#include <sstream>
#include <cmath>

Board::Board()
{}

Board::Board(std::vector<int> tab) : tab(tab)
{}

// Board::Board(Board& ref) : Board(ref.tab)
// {}


int Board::size()   const
{
    return sqrt(tab.size());
}

int Board::number_of_inversions()  const
{
    int count = 0;

    for (size_t i = 0; i < tab.size(); i++)
    {
        for (size_t j = i + 1; j < tab.size(); j++)
            count += tab[i] > tab[j];
    }
    return count;
}

bool Board::is_solvable() const
{
    int n = size();

    if (n % 2)
        return number_of_inversions() % 2 == 0;
    else
    {
        int ij = get_empty_coords();
        int row = ij / n;
        return row % 2 != number_of_inversions() % 2;
    }
}

float Board::estimate_cost() const
{
    float res = 0;
    int n = size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
    for (size_t i = 0; i < tab.size(); i++) {
        if (tab[i] == 0)
            return i;
    }
    return -1;
}

bool Board::istarget()  const
{
    for (size_t i = 0; i < tab.size(); i++)
    {
        if (tab[i] != (int)i)
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

    for (size_t i = 0; i < tab.size(); i++)
    {
        stream << tab[i];
        if ((i+1) % size() == 0)
            stream << '\n';
        else
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