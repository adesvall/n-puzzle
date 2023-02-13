#include <unordered_map>
#include <State.hpp>
#include <deque>

using namespace std;



unordered_map<string, int> compute_db()
{
    unordered_map<string, int>  db;
    State init;
    deque<State> breadth;
    
    breadth.push_back(init);
    while (!breadth.empty())
    {
        State* curr = &breadth.front();
        std::vector<State> neighbors = curr->getNeibours();
        for (std::vector<State>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            if (!db.count(it->board.toString(true)))
            {
                db[it->board.toString(true)] = curr->g + 1;
                breadth.push_back(*it);
            }
        }
    }
    return db;
}