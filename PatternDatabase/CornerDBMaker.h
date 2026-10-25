#ifndef CORNER_DB_MAKER_H
#define CORNER_DB_MAKER_H

#include "CornerPatternDatabase.h"
#include "../Model/RubiksCubeBitboard.h"
#include <queue>
#include <iostream>

using namespace std;

class CornerDBMaker {
private:
    CornerPatternDatabase cornerDB;

public:
    CornerDBMaker() {}

    bool generateDatabase() {
        cout << "Checking if database already exists..." << endl;

        // If the file already exists on your hard drive, load it and skip generation!
        if (cornerDB.fromFile()) {
            cout << "Database file found and loaded! Skipping generation." << endl;
            return true;
        }

        cout << "File not found. Starting BFS Generation (This will take a few minutes)..." << endl;

        RubiksCubeBitboard solvedCube;
        queue<RubiksCubeBitboard> q;

        // Step 1: Start with a perfectly solved cube (0 moves)
        q.push(solvedCube);
        cornerDB.setNumMoves(solvedCube, 0);

        int depth = 0;
        int nodes_at_current_depth = 1;
        int nodes_at_next_depth = 0;
        int total_nodes = 1;

        // Step 2: Run the massive BFS
        while (!q.empty()) {
            RubiksCubeBitboard node = q.front();
            q.pop();
            nodes_at_current_depth--;

            int curr_estimate = cornerDB.getEstimate(node);

            // Try all 18 possible moves
            for (int i = 0; i < 18; i++) {
                RubiksCubeBitboard nextNode = node;
                nextNode.move(static_cast<RubiksCube::MOVE>(i));

                // If setNumMoves returns true, it means this state was previously 255 (Unvisited).
                // It updates it to curr_estimate + 1, and pushes it to the queue.
                if (cornerDB.setNumMoves(nextNode, curr_estimate + 1)) {
                    q.push(nextNode);
                    nodes_at_next_depth++;
                    total_nodes++;
                }
            }

            // Print progress so we know the program hasn't frozen
            if (nodes_at_current_depth == 0) {
                cout << "Finished Depth " << depth << " | Nodes Generated: " << nodes_at_next_depth << " | Total: " << total_nodes << endl;
                depth++;
                nodes_at_current_depth = nodes_at_next_depth;
                nodes_at_next_depth = 0;
            }
        }

        // Step 3: Save the array to your hard drive
        cout << "\nGeneration complete! Writing to disk..." << endl;
        cornerDB.toFile();
        cout << "Successfully saved corner_database.bin!" << endl;
        return true;
    }
};

#endif // CORNER_DB_MAKER_H