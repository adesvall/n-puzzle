#include <string>
#include <vector>

struct Board
{
    std::vector<int> tab;

    Board();
    Board(std::vector<int> tab);
    // Board(Board& ref);
    int size()  const;
    bool is_solvable()  const;
    int number_of_inversions()  const;
    Board move(int i0, int j0, int new_i, int new_j) const;
    float estimate_cost() const;
    int get_empty_coords() const;
    bool istarget() const;
    // bool operator==(Board &rhs) const;
    std::string toString()  const;

};
