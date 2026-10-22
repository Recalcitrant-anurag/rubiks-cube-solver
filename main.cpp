//
// Created by Anurag Anand on 22-10-2026.
//
#include <iostream>
#include <vector>
#include "Model/RubiksCubeBitboard.h"
#include "Solver/BFSSolver.h"

using namespace std;

int main() {
    // 1. Initialize a solved Bitboard cube
    RubiksCubeBitboard cube;

    cout << "Initial Solved Cube:" << endl;
    cube.print();

    // 2. Scramble the cube with 5 random moves
    // Note: Keep this under 6-7 moves for BFS testing, as BFS memory usage grows exponentially.
    cout << "\nScrambling the cube with 5 moves..." << endl;
    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(2);

    cout << "Scramble sequence generated: ";
    for (auto move : shuffle_moves) {
        cout << cube.getMove(move) << " ";
    }
    cout << "\n\nScrambled Cube State:" << endl;
    cube.print();

    // 3. Initialize the BFS Solver with the Bitboard template and Hash struct
    cout << "\nStarting BFS Solver..." << endl;
    BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);

    // 4. Solve the cube
    vector<RubiksCube::MOVE> solution = bfsSolver.solve();

    // 5. Print the optimal solution sequence
    cout << "\nSolution found! Optimal sequence to solve: ";
    for (auto move : solution) {
        cout << cube.getMove(move) << " ";
    }
    cout << endl;

    return 0;
}