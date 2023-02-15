#include "main.hpp"
#include <limits>
#include <cmath>
#include <unordered_set>
#include <list>

using namespace std;

int dfs(State& node, int threshold, unordered_set<string>& visited, int depth = 0)  {
    visited.insert(node.board.toString());
    int f = node.g + node.h;
    if (f > threshold) {
        return f;
    }
    if (node.board.istarget()) {
        print_res(&node);
        return -1;
    }

    int min = numeric_limits<int>::max();
    vector<State> children;

    node.getNeighbors(children);
    for (State &child : children)   {
        if (visited.count(child.board.toString()))
            continue;
        int t = dfs(child, threshold, visited, depth + 1);
        if (t == -1)
            return -1;
        if (t < min)
            min = t;
    }
    // if (min == numeric_limits<int>::max())
    // cout << "depth\t" << depth << "\tthreshold " << threshold << "\tvisited " << visited.size() << endl;

    return min;
}

int stack_dfs(State& init, int threshold, unordered_set<string>& visited)  {
    list<State> stack;
    stack.push_back(init);
    int next_threshold = numeric_limits<int>::max();

    while (!stack.empty())  {
        State& curr = stack.back();
        if (visited.count(curr.board.toString())) {
            stack.pop_back();
            continue;
        }
        visited.insert(curr.board.toString());
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
        curr.getNeighbors(stack);
    }
    return next_threshold;
}

void ida_star(Board& init) {
    int ij = init.get_empty_coords();
    State root(init, ij / init.size, ij % init.size, (State*)NULL, 0);
    unordered_set<string> visited;
    int threshold = root.h;
    // cout << init.toString() << endl;
    // exit(2);
    while (threshold != -1) {
        cout << "threshold " << threshold;
        threshold = stack_dfs(root, threshold, visited);
        cout << "\tvisited " << visited.size() << endl;
        visited.clear();
    }
}
