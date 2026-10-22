#include <iostream>
#include <vector>
#include "Model/RubiksCubeBitboard.h"
#include "Solver/IDDFSSolver.h"

using namespace std;

int main() {
    RubiksCubeBitboard cube;
    
    cout << "Scrambling the cube with 7 moves..." << endl;
    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
    
    cout << "Scramble sequence generated: ";
    for (auto move : shuffle_moves) {
        cout << cube.getMove(move) << " ";
    }
    cout << "\n\nScrambled Cube State:" << endl;
    cube.print();

    // Set limit to 8 to guarantee we can find a 7-move scramble
    int max_depth = 8;
    cout << "\nStarting IDDFS Solver (Max Depth: " << max_depth << ")..." << endl;
    
    IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, max_depth);
    vector<RubiksCube::MOVE> solution = iddfsSolver.solve();

    // Safety check for empty solutions
    if (solution.empty()) {
        cout << "\n[!] No solution found. The cube requires more than " << max_depth << " moves to solve." << endl;
    } else {
        cout << "\nSolution found! Sequence to solve: ";
        for (auto move : solution) {
            cout << cube.getMove(move) << " ";
        }
        cout << endl;
    }

    return 0;
}