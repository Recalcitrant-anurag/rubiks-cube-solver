#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H

#include <vector>
#include <iostream> // Added for progress printing
#include "../Model/RubiksCube.h"
#include "DFSSolver.h"

using namespace std;

template<typename T, typename H>
class IDDFSSolver {
private:
    T rubiksCube;
    int max_search_depth;

public:
    IDDFSSolver(T _rubiksCube, int _max_search_depth = 7) 
        : rubiksCube(_rubiksCube), max_search_depth(_max_search_depth) {}

    vector<RubiksCube::MOVE> solve() {
        for (int i = 1; i <= max_search_depth; i++) {
            // Visual feedback to watch the layers deepen
            cout << "  -> Searching depth " << i << "..." << endl;
            
            DFSSolver<T, H> dfsSolver(rubiksCube, i);
            vector<RubiksCube::MOVE> moves = dfsSolver.solve();
            
            if (!moves.empty()) {
                return moves;
            }
        }
        return vector<RubiksCube::MOVE>(); 
    }
};

#endif // IDDFSSOLVER_H