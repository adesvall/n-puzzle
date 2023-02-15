#include "Board.hpp"
#include <boost/heap/fibonacci_heap.hpp>

template <typename T>
class PointerCompare
{
public:
    // Comparator function
    bool operator()(const T* o1, const T* o2) const
    {
        return (*o1 < *o2);
    }
};

class State
{
public:

    int             g;
    int             h;
    Board           board;
    int             i0;
    int             j0;
    const State     *parent;
    bool            isclosed;
    boost::heap::fibonacci_heap<State *, boost::heap::mutable_<true>, boost::heap::compare<PointerCompare<State>>>::handle_type handle;

public:
    State();
    State(int n);
    State(Board board, int i0, int j0, const State* parent, int g );
    ~State();
    std::vector<State> getNeighbors() const;
    template <typename T>
    void getNeighbors(T& vec) const
    {
        for (int dr = 0; dr < 4; dr++)
        {
            // std::cout << vec.size() <<  "dr = " << dr << std::endl;
            int new_i = i0 + (dr == 2) - (dr == 0);
            int new_j = j0 + (dr == 1) - (dr == 3);
            if (!(0 <= new_i && new_i < (int)board.size))
                continue;
            if (!(0 <= new_j && new_j < (int)board.size))
                continue;
            // if (parent && parent->i0 == new_i && parent->j0 == new_j)
            //     continue;
            
            // vec.emplace(vec.begin(), board.move(i0, j0, new_i, new_j), new_i, new_j, this, g + 1);
            vec.emplace_back(board.move(i0, j0, new_i, new_j), new_i, new_j, this, g + 1);
        }
    }

    bool operator<(const State& rhs) const;
};

