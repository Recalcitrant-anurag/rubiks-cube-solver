#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include <vector>
#include "../Model/RubiksCube.h"

using namespace std;

// We include 'H' here just so we can easily swap this with BFSSolver in main.cpp
// without having to change our template arguments!
template<typename T, typename H>
class DFSSolver {
private:
    vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    // The recursive workhorse function
    bool dfs(int depth) {
        if (rubiksCube.isSolved()) return true;
        if (depth > max_search_depth) return false;

        for (int i = 0; i < 18; i++) {
            auto curr_move = static_cast<RubiksCube::MOVE>(i);

            // 1. Make the move
            rubiksCube.move(curr_move);
            moves.push_back(curr_move);

            // 2. Dive deeper! If this recursive call returns true, we found the solution.
            if (dfs(depth + 1)) return true;

            // 3. Backtrack: If we hit the depth limit and didn't solve it,
            // undo the move and pop it off the list so the loop can try the next one.
            moves.pop_back();
            rubiksCube.invert(curr_move);
        }
        return false;
    }

public:
    T rubiksCube;

    // We default the search depth to 8 moves to prevent infinite diving
    // Use an initializer list (the colon syntax) instead of '=' assignment
    DFSSolver(T _rubiksCube, int _max_search_depth = 8) 
        : rubiksCube(_rubiksCube), max_search_depth(_max_search_depth) {}

    vector<RubiksCube::MOVE> solve() {
        dfs(1);
        return moves;
    }
};

#endif // DFSSOLVER_H