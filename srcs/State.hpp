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

    int     g;
    float     h;
    Board   board;
    int     i0;
    int     j0;
    const State   *parent;
    bool    isclosed;
    boost::heap::fibonacci_heap<State *, boost::heap::mutable_<true>, boost::heap::compare<PointerCompare<State>>>::handle_type handle;

public:
    State();
    State(Board board, int i0, int j0, const State* parent, int g );
    ~State();
    std::vector<State> getNeibours() const;
    bool operator<(const State& rhs) const;
};

