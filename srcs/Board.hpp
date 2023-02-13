#include <string>
#include <vector>

struct Board
{
    std::vector<int> tab;
    size_t size;

    Board();
    Board(int n);
    Board(std::vector<int> tab);
    // Board(Board& ref);
    bool is_solvable()  const;
    int number_of_inversions()  const;
    Board move(int i0, int j0, int new_i, int new_j) const;
    int linear_conflicts(bool partition = false) const;
    float partition_cost() const;
    float estimate_cost() const;
    int get_empty_coords() const;
    bool istarget() const;
    // bool operator==(Board &rhs) const;
    std::string toString(bool fringe = false)  const;

};
