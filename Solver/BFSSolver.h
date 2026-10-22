#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "../Model/RubiksCube.h"

using namespace std;

template<typename T, typename H>
class BFSSolver {
private:
    T rubiksCube;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, RubiksCube::MOVE, H> move_done;

    T bfs() {
        queue<T> q;
        q.push(rubiksCube);
        move_done[rubiksCube] = RubiksCube::MOVE::U;

        while (!q.empty()) {
            T node = q.front();
            q.pop();

            if (node.isSolved()) {
                return node;
            }

            for (int i = 0; i < 18; i++) {
                auto curr_move = static_cast<RubiksCube::MOVE>(i);
                
                T new_node = node;
                new_node.move(curr_move);

                if (move_done.find(new_node) == move_done.end()) {
                    move_done[new_node] = curr_move;
                    q.push(new_node);
                }
            }
        }
        return rubiksCube; 
    }

public:
    explicit BFSSolver(T _rubiksCube) : rubiksCube(_rubiksCube) {}

    vector<RubiksCube::MOVE> solve() {
        T solved_cube = bfs();
        T curr_cube = solved_cube;
        
        while (!(curr_cube == rubiksCube)) {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif // BFSSOLVER_H