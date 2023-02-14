#include <unordered_map>
#include "State.hpp"
#include <deque>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp> 
#include <fstream>
#include <iostream>

using namespace std;

unordered_map<string, int> compute_db(int n)
{
    unordered_map<string, int>  db;
    State init(n);
    deque<State> breadth;

    breadth.push_back(init);
    while (!breadth.empty())
    {
        State* curr = &breadth.front();
        vector<State> neighbors = curr->getNeighbors();
        for (State n : neighbors)
        {
            if (!db.count(n.board.toString()))
            {
                db[n.board.toString()] = curr->g + 1;
                breadth.push_back(n);
            }
        }
        breadth.pop_front();
        if (breadth.size() % 100000 == 0)
            cout << breadth.size() << '\t' << db.size() << endl;
    }
    return db;
}

int main()
{
    ofstream ofs("4puzzle.db", std::ios::binary);
    unordered_map<string, int> db;
    auto hash = db.hash_function();
    unordered_map<size_t, int> db2;
    
    // cout << sizeof(boost::heap::fibonacci_heap<State *, boost::heap::mutable_<true>, boost::heap::compare<PointerCompare<State>>>::handle_type);
    // cout << endl << sizeof(int) << endl;
    // return 0;
    db = compute_db(3);
    for (auto p : db)
    {
        db2[hash(p.first)] = p.second;
    }
    cout << db2.size();

    cout << " main good" << endl;

    boost::archive::binary_oarchive oa(ofs);
    // write unordered_map instance to archive
    oa << db2;
    // archive and stream closed when destructors are called
}