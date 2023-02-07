#include <string>

struct Board
{
    int tab[12];

    Board();
    Board(const int tab[12]);
    // Board(Board& ref);
    Board move(int i0, int j0, int new_i, int new_j) const;
    float estimate_cost() const;
    int get_empty_coords() const;
    bool istarget() const;
    // bool operator==(Board &rhs) const;
    std::string toString()  const;

};
