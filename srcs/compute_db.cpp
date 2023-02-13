#include <map>
#include "State.hpp"
#include <deque>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

using namespace std;

map<string, int> compute_db(int n)
{
    map<string, int>  db;
    State init(4);
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

int main()
{
    std::ofstream ofs("4puzzle.db");
    map<std::string, int> db = compute_db(4);

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write map instance to archive
        oa << db;
        // archive and stream closed when destructors are called
    }
}