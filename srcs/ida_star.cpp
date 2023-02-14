#include "main.hpp"
#include <limits>
#include <cmath>
#include <unordered_map>

using namespace std;

int dfs(State& node, int threshold, unordered_map<string, State*>& visited, int depth = 0)  {
    visited[node.board.toString()] = &node;
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

void ida_star(Board& init) {
    int ij = init.get_empty_coords();
    State root(init, ij / init.size, ij % init.size, (State*)NULL, 0);
    unordered_map<string, State*> visited;
    int threshold = root.h;
    // cout << init.toString() << endl;
    // exit(2);
    while (threshold != -1) {
        cout << "threshold " << threshold;
        threshold = dfs(root, threshold, visited);
        cout << "\tvisited " << visited.size() << endl;
        visited.clear();
    }
}
