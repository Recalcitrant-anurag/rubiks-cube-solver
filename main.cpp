#include <iostream>
#include <vector>
#include "Model/RubiksCubeBitboard.h"
#include "Solver/DFSSolver.h"

using namespace std;

int main() {
    RubiksCubeBitboard cube;

    // 1. Scramble the cube with 6 moves
    cout << "Scrambling the cube with 6 moves..." << endl;
    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);

    cout << "Scramble sequence generated: ";
    for (auto move : shuffle_moves) {
        cout << cube.getMove(move) << " ";
    }
    cout << "\n\nScrambled Cube State:" << endl;
    cube.print();

    // 2. Initialize the DFS Solver with a maximum depth of 8 moves
    cout << "\nStarting DFS Solver..." << endl;
    DFSSolver<RubiksCubeBitboard, HashBitboard> dfsSolver(cube, 8);

    // 3. Solve the cube
    vector<RubiksCube::MOVE> solution = dfsSolver.solve();

    // 4. Print the solution sequence
    cout << "\nSolution found! Sequence to solve: ";
    for (auto move : solution) {
        cout << cube.getMove(move) << " ";
    }
    cout << endl;

    return 0;
}