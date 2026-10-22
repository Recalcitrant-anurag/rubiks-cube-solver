#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include <vector>
#include "../Model/RubiksCube.h"

using namespace std;

template<typename T, typename H>
class DFSSolver {
private:
    vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    // 1. Pass the cube by value (T current_cube) so we create a fresh, clean copy every dive
    bool dfs(int depth, T current_cube) {
        if (current_cube.isSolved()) return true;
        if (depth > max_search_depth) return false;

        for (int i = 0; i < 18; i++) {
            
            // 2. PRUNING OPTIMIZATION: Don't turn the exact same face twice in a row!
            // This drops our branching factor from 18 to 15, eliminating billions of useless checks.
            if (!moves.empty() && (static_cast<int>(moves.back()) / 3 == i / 3)) {
                continue; 
            }

            auto curr_move = static_cast<RubiksCube::MOVE>(i);
            
            // 3. Copy the cube and move it forward, completely ignoring invert()
            T next_cube = current_cube;
            next_cube.move(curr_move);

            moves.push_back(curr_move);
            
            // 4. Dive deeper using the new copied cube
            if (dfs(depth + 1, next_cube)) return true;
            
            moves.pop_back();
        }
        return false;
    }

public:
    T rubiksCube;
    
    DFSSolver(T _rubiksCube, int _max_search_depth = 8) 
        : rubiksCube(_rubiksCube), max_search_depth(_max_search_depth) {}

    vector<RubiksCube::MOVE> solve() {
        // Pass the initial cube into the recursion
        dfs(1, rubiksCube); 
        return moves;
    }
};

#endif // DFSSOLVER_H