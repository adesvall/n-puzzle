#include <string>
#include <vector>
#include <set>

struct Board
{
    std::vector<int> tab;

    static size_t size;
    static std::set<int> selection;

    Board();
    Board(int n);
    Board(std::vector<int> tab);
    // Board(Board& ref);
    bool is_solvable()  const;
    int number_of_inversions()  const;
    Board move(int i0, int j0, int new_i, int new_j) const;
    int linear_conflicts() const;
    float partition_cost() const;
    int estimate_cost() const;
    int get_empty_coords() const;
    bool istarget() const;
    // bool operator==(Board &rhs) const;
    std::string toString()  const;
    Board remove_fringe()   const;

    static void emptySelection();
    static void fringeSelection();
    static void bottomSelection();
    static void addSelection(int k);

};
