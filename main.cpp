#include <iostream>
#include <vector>
#include "Model/RubiksCubeBitboard.h"
#include "Solver/IDAstarSolver.h"
#include "Solver/PatternDatabase.h"

using namespace std;

int main() {
    RubiksCubeBitboard cube;

    cout << "Scrambling the cube with 7 moves..." << endl;
    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);

    cout << "Scramble sequence: ";
    for (auto move : shuffle_moves) {
        cout << cube.getMove(move) << " ";
    }
    cout << "\n\nScrambled Cube State:" << endl;
    cube.print();

    // Initialize our placeholder heuristic
    DummyHeuristic<RubiksCubeBitboard> dummy_heuristic;

    cout << "\nStarting IDA* Solver (Max Depth: 8)..." << endl;

    // Pass the cube, the dummy heuristic, and a max depth of 8
    IDAstarSolver<RubiksCubeBitboard, HashBitboard, DummyHeuristic<RubiksCubeBitboard>> idaStarSolver(cube, dummy_heuristic, 8);

    vector<RubiksCube::MOVE> solution = idaStarSolver.solve();

    if (solution.empty()) {
        cout << "\n[!] No solution found within limit." << endl;
    } else {
        cout << "\nSolution found! Sequence to solve: ";
        for (auto move : solution) {
            cout << cube.getMove(move) << " ";
        }
        cout << endl;
    }

    return 0;
}