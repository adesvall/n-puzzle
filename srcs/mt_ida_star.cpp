#include "main.hpp"
#include <limits>
#include <cmath>
#include <unordered_set>
#include <list>
#include <thread>
#include <mutex>

using namespace std;

list<State> divide_stack(list<State>& stack, unordered_set<string>& visited)  {
    list<State> res;
    list<State>::iterator it = stack.begin();

    while (it != stack.end())   {
        State* me = &*it;
        list<State>::iterator it_copy(it++);

        if (visited.count(it->board.toString())) {
            stack.erase(it);
            it = it_copy;
            continue;
        }
        if (it_copy == stack.end())
            return list<State>();
        if (it_copy->parent != me)  {
            res.push_back(*it);
            stack.erase(it);
            return res;
        }
        res.push_back(*it);
        it = it_copy;
    }
    return res;
}

int multithreaded_dfs(State &init, int threshold, unordered_set<string>& visited)  {
    list<State> to_treat;
    unordered_set<string> visited;
    mutex mtx_visited;
    thread threads[4];

    to_treat.push_back(init);
    int next_threshold = numeric_limits<int>::max();
    int i = 0;
    while (i < 4)   {
        threads[i] = thread(thread_dfs, ref(to_treat), threshold, ref(visited));
        threads[i].join();
        i++;
    }

    return next_threshold;
}

int thread_dfs(list<State>& initStack, int threshold, unordered_set<string>& visited)  {
    list<State> stack = initStack;
    int next_threshold = numeric_limits<int>::max();

    while (!stack.empty())  {
        State& curr = stack.back();
        if (visited.count(curr.board.toString())) {
            stack.pop_back();
            continue;
        }
        if (curr.board.istarget())  {
            print_res(&curr);
            return -1;
        }
        if (curr.g + curr.h > threshold)    {
            if (curr.g + curr.h < next_threshold)
                next_threshold = curr.g + curr.h;
            stack.pop_back();
            continue;
        }
        // cout << "\t" << curr.g + curr.h << endl;
        visited.insert(curr.board.toString());
        curr.getNeighbors(stack);
        while (visited.count(stack.back().board.toString()))
            stack.pop_back();
    }
    return next_threshold;
}