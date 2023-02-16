#include "Board.hpp"
#include <hashtable.h>
#include <sstream>
#include <cmath>

bool Board::fringe = false;
bool Board::side = false;

Board::Board()
{}
Board::Board(int n)
{
    size = n;
    for (int i = 0; i < n*n; i++)
    {
        tab.push_back(i);
    }
}

Board::Board(std::vector<int> tab) : tab(tab)
{
    size = (int)sqrt(tab.size());
}

int Board::number_of_inversions()  const
{
    int count = 0;

    for (size_t i = 0; i < tab.size(); i++)
    {
        for (size_t j = i + 1; j < tab.size() && tab[i]; j++)
            count += ((tab[i] > tab[j]) && tab[j]);
    }
    return count;
}

bool Board::is_solvable() const
{
    int n = size;
    int inv = number_of_inversions();

    if (n % 2)
        return inv % 2 == 0;
    else
    {
        int ij = get_empty_coords();
        int row = ij / n;
        return row % 2 == inv % 2;
    }
}

bool isFringe(int k, int size)
{
    return k % size == size-1 || k / size == size - 1;
}
bool isSide(int k, int size)
{
    return k / size == size - 1;
}
bool doesCount(int k, int size)
{
    if (Board::fringe)
        return isFringe(k, size);
    else if (Board::side)
        return isSide(k, size);
    return true;
}


int Board::linear_conflicts()  const
{
    int count = 0;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (tab[size * i + j] && tab[size * i + j] % size == j
            && (doesCount(tab[size * i + j], size))) {
                for (size_t i2 = i + 1; i2 < size; i2++)
                {
                    if (tab[size * i2 + j] && tab[size * i2 + j] % size == j
                    && tab[size * i2 + j] < tab[size * i + j]
                    && (doesCount(tab[size * i2 + j], size)))
                        count++;
                }
            }

            if (tab[size * i + j] && tab[size * i + j] / size == i
            && (doesCount(tab[size * i + j], size))) {
                for (size_t j2 = j + 1; j2 < size; j2++)
                {
                    if (tab[size * i + j2] && tab[size * i + j2] / size == i
                    && tab[size * i + j2] < tab[size * i + j]
                    && (doesCount(tab[size * i + j2], size)))
                        count++;
                }
            }
        }
    }
    return count;
}
/*
float Board::partition_cost()  const
{
    float resFringe = 0;
    float resInside = 0;
    
    resFringe = 2 * linear_conflicts();
    resInside = resFringe;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            int dist = abs(i - tab[size*i+j] / size) + abs(j - tab[size*i+j] % size);
            if (isFringe(tab[i*size+j], size))
                resFringe += dist;
            else if (tab[i*size+j])
                resInside += dist;
        }
    }

    if (resFringe > resInside)
        return resFringe;
    return resInside;
}*/
#include <iostream>
int Board::estimate_cost() const
{
    // return partition_cost();
    int res = 2*linear_conflicts();
    int n = size;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!tab[n*i+j])
                continue;
            int dist = abs(i - tab[n*i+j] / n) + abs(j - tab[n*i+j] % n);
            if (!doesCount(tab[n*i+j], size))
                dist = doesCount(n*i+j, size);
            if (Board::fringe && isSide(tab[n*i+j], size))
                dist *= 100;
            res += dist;
        }
    }
    return res;
}

Board Board::move(int i0, int j0, int new_i, int new_j)   const
{
    Board res(this->tab);

    if (tab[size * i0 + j0] != 0)
        throw std::invalid_argument("Invalid move");

    res.tab[size * i0 + j0] = res.tab[size * new_i + new_j];
    res.tab[size * new_i + new_j] = 0;
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
        if ((doesCount(i, size)) && tab[i] != (int)i)
            return false;
    }
    return true;
}

std::string Board::toString()  const
{
    std::stringstream stream;

    for (size_t i = 0; i < tab.size(); i++)
    {

        if (doesCount(tab[i], size) || !tab[i])
            stream << tab[i];
        else
            stream << '*';
        if ((i+1) % size == 0)
            stream << '\n';
        else
            stream << ',';
    }
    return stream.str();
}


Board Board::remove_fringe()   const
{
    Board res;
    res.size = size - 1;
    for (size_t i = 0; i < size*size; i++)
    {
        if (isFringe(i, size))
            continue;
        int val = tab[i] / size * res.size + tab[i] % size;
        res.tab.push_back(val);
    }
    return res;
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