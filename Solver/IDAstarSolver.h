#ifndef IDASTARSOLVER_H
#define IDASTARSOLVER_H

#include <vector>
#include <iostream>
#include "../Model/RubiksCube.h"

using namespace std;

// We add a 'Heuristic' template so we can plug in our Pattern Database
template<typename T, typename H, typename Heuristic>
class IDAstarSolver {
private:
    T rubiksCube;
    int max_search_depth;
    Heuristic heuristic;
    vector<RubiksCube::MOVE> moves;

    bool ida_star(int limit, int depth, T current_cube) {
        if (current_cube.isSolved()) return true;

        // A* Magic: current depth (moves made) + estimate (minimum moves remaining)
        int estimate = heuristic.getEstimate(current_cube);

        // If the total projected path is longer than our limit, prune it instantly!
        if (depth + estimate > limit) return false;

        for (int i = 0; i < 18; i++) {
            // Pruning optimization: don't turn the same face twice
            if (!moves.empty() && (static_cast<int>(moves.back()) / 3 == i / 3)) {
                continue;
            }

            auto curr_move = static_cast<RubiksCube::MOVE>(i);
            T next_cube = current_cube;
            next_cube.move(curr_move);
            moves.push_back(curr_move);

            // Dive deeper
            if (ida_star(limit, depth + 1, next_cube)) return true;

            // Backtrack
            moves.pop_back();
        }
        return false;
    }

public:
    IDAstarSolver(T _rubiksCube, Heuristic _heuristic, int _max_search_depth = 20)
        : rubiksCube(_rubiksCube), heuristic(_heuristic), max_search_depth(_max_search_depth) {}

    vector<RubiksCube::MOVE> solve() {
        // Start the search limit at the heuristic's absolute minimum estimate
        int initial_estimate = heuristic.getEstimate(rubiksCube);

        for (int limit = initial_estimate; limit <= max_search_depth; limit++) {
            cout << "  -> IDA* Searching with limit " << limit << "..." << endl;

            if (ida_star(limit, 0, rubiksCube)) {
                return moves;
            }
        }
        return moves;
    }
};

#endif // IDASTARSOLVER_H