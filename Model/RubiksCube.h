//
// Created by Anurag Anand on 08-07-2026.
//

#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include <bits/stdc++.h>
using namespace std;
class RubiksCube {
    public:
    enum class FACE {
        UP,LEFT,FRONT,RIGHT,BACK,DOWN
    };
    enum class COLOR {
        WHITE,GREEN,RED,BLUE,ORANGE,YELLOW
    };
    enum class MOVE {
        U,UPRIME,U2,
        L,LPRIME,L2,
        F,FPRIME,F2,
        R,RPRIME,R2,
        B,BPRIME,B2,
        D,DPRIME,D2,
    };
    /*
        getColor function returns the color of the face with (row,col)
        if Rubik's cube face is pointing at me then the row numbering starts from
        top to bottom and the col numbering starts from left to right with them being
        0-indexed
     */
    virtual COLOR getColor(FACE face,unsigned row,unsigned col) const=0;
    /*
     * Returns the first letter of the given color
     * Eg: for COLOR::WHITE it returns 'W'
     */
    static char getColorLetter(COLOR color);
    /*
     * Returns true if the Rubik's Cube is solved
     */
    virtual bool isSolved() const=0;
    /*
     * Returns the move in string format
     */
    static string getMove(MOVE mov);
    /*
     * Print the Rubik Cube in Planar format.
     *
     * The cube is laid out as follows.
     *
     * The sides:
     *    U
     *  L F R B
     *    D
     *
     * Color wise:
     *
     *          W W W
     *          W W W
     *          W W W
     *
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *
     *          Y Y Y
     *          Y Y Y
     *          Y Y Y
     *
     * Row and Column Numberings:
     * rx -> row numbering
     * cx -> column numbering
     * bx -> both row and column numbering
     *
     *             b0 c1 c2
     *             r1  .  .
     *             r2  .  .
     *
     *  b0 c1 c2   b0 c1 c2   b0 c1 c2   b0 c1 c2
     *  r1  .  .   r1  .  .   r1  .  .   r1  .  .
     *  r2  .  .   r2  .  .   r2  .  .   r2  .  .
     *
     *             b0 c1 c2
     *             r1  .  .
     *             r2  .  .
     *
     */
    void print()const;
    /*randomly shuffle the cube given no. of times and return the moves made*/
    vector<MOVE>randomShuffleCube(unsigned times);
    /*to perform a particular move on a cube */
    RubiksCube& move(MOVE mov);
    /*to invert a move */
    RubiksCube& invert(MOVE mov);
    /*making function for all the moves possible for a rubik cube */
    virtual RubiksCube& f()=0;
    virtual RubiksCube& f2()=0;
    virtual RubiksCube& fprime()=0;

    virtual RubiksCube& l()=0;
    virtual RubiksCube& l2()=0;
    virtual RubiksCube& lprime()=0;

    virtual RubiksCube& u()=0;
    virtual RubiksCube& u2()=0;
    virtual RubiksCube& uprime()=0;

    virtual RubiksCube& r()=0;
    virtual RubiksCube& r2()=0;
    virtual RubiksCube& rprime()=0;

    virtual RubiksCube& b()=0;
    virtual RubiksCube& b2()=0;
    virtual RubiksCube& bprime()=0;

    virtual RubiksCube& d()=0;
    virtual RubiksCube& d2()=0;
    virtual RubiksCube& dprime()=0;
};


#endif //RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H