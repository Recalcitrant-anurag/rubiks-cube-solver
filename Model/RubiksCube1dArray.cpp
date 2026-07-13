//
// Created by Anurag Anand on 12-07-2026.
//
#include "RubiksCube.h"
class RubiksCube1dArray : public RubiksCube{
    private:
    int getIndex(int face,int row,int col) const{
        return (face*9)+(row*3)+col;
    }
    void rotateface(int face){
        char temp[9]{};
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                temp[getIndex(0, row, col)] = cube[getIndex(face, 2 - col, row)];
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                cube[getIndex(face, row, col)] = temp[getIndex(0, row, col)];
            }
        }
    }
    public:
    char cube[54]{};
    RubiksCube1dArray(){
        for(int face=0;face<6;face++){
            for(int row=0;row<3;row++){
                for(int col=0;col<3;col++){
                    cube[getIndex(face,row,col)]=getColorLetter(static_cast<COLOR>(face));
                }
            }
        }
    }
    COLOR getColor(FACE face, unsigned row, unsigned col) const override
    {
        char color = cube[getIndex((int)face,(int)row,(int)col)];
        switch (color)
        {
        case 'B':
            return COLOR::BLUE;
        case 'R':
            return COLOR::RED;
        case 'W':
            return COLOR::WHITE;
        case 'G':
            return COLOR::GREEN;
        case 'Y':
            return COLOR::YELLOW;
        case 'O':
            return COLOR::ORANGE;
        }
        return COLOR::WHITE;
    }
    bool isSolved() const override{
        for(int face=0;face<6;face++){
            for(int row=0;row<3;row++){
                for(int col=0;col<3;col++){
                    if(cube[getIndex(face,row,col)]!=getColorLetter(COLOR(face)))return false;
                }
            }
        }
        return true;
    }
    RubiksCube &u() override
    {
        this->rotateface(0);
        // to rotate the up face
        char temp[3]{};
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(1,0,i)];
        for (int face = 1; face <= 3; face++)
        {
            for (int col = 0; col < 3; col++)
            {
                cube[getIndex(face,0,col)] = cube[getIndex(face + 1,0,col)];
            }
        }
        for (int col = 0; col < 3; col++)
        {
            cube[getIndex(4,0,col)] = temp[col];
        }
        return *this;
    }
    RubiksCube &u2() override
    {
        this->u();
        this->u();
        return *this;
    }
    RubiksCube &uprime() override
    {
        this->u();
        this->u();
        this->u();
        return *this;
    }
    RubiksCube &l() override
    {
        // back rows gets inverted
        this->rotateface(1);
        char temp[3]{};
        for (int row = 0; row <= 2; row++)
            temp[row] = cube[getIndex(0,row,0)];
        // UP gets BACK (Note: BACK uses column 2 and inverted rows!)
        for (int row = 0; row <= 2; row++)
        {
            cube[getIndex(0,row,0)] = cube[getIndex(4,2 - row,2)];
        }
        // BACK gets DOWN (Note: BACK uses column 2 and inverted rows!)
        for (int row = 0; row <= 2; row++)
        {
            cube[getIndex(4,2 - row,2)] = cube[getIndex(5,row,0)];
        }
        for (int row = 0; row <= 2; row++)
        {
            cube[getIndex(5,row,0)] = cube[getIndex(2,row,0)];
        }
        for (int row = 0; row <= 2; row++)
        {
            cube[getIndex(2,row,0)] = temp[row];
        }
        return *this;
    }
    RubiksCube &l2() override
    {
        this->l();
        this->l();
        return *this;
    }
    RubiksCube &lprime() override
    {
        this->l();
        this->l();
        this->l();
        return *this;
    }
    RubiksCube &r() override
    {
        this->rotateface(3);
        char temp[3]{};
        for (int row = 0; row <= 2; row++)
            temp[row] = cube[getIndex(0,row,2)];
        for (int row = 0; row <= 2; row++)
            cube[getIndex(0,row,2)] = cube[getIndex(2,row,2)];
        for (int row = 0; row <= 2; row++)
            cube[getIndex(2,row,2)] = cube[getIndex(5,row,2)];
        // DOWN gets BACK (Note: BACK uses column 0 and inverted rows!)
        for (int row = 0; row <= 2; row++)
            cube[getIndex(5,row,2)] = cube[getIndex(4,2 - row,0)];
        for (int row = 0; row <= 2; row++)
            cube[getIndex(4,2 - row,0)] = temp[row];
        return *this;
    }
    RubiksCube &r2() override
    {
        this->r();
        this->r();
        return *this;
    }
    RubiksCube &rprime() override
    {
        this->r();
        this->r();
        this->r();
        return *this;
    }
    RubiksCube &f() override
    {
        this->rotateface(2);
        char temp[3]{};
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0,2,2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0,2,2 - i)] = cube[getIndex(1,i,2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1,i,2)] = cube[getIndex(5,0,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5,0,i)] = cube[getIndex(3,2 - i,0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3,2 - i,0)] = temp[i];
        return *this;
    }
    RubiksCube &f2() override
    {
        this->f();
        this->f();
        return *this;
    }
    RubiksCube &fprime() override
    {
        this->f();
        this->f();
        this->f();
        return *this;
    }
    RubiksCube &b() override
    {
        this->rotateface(4);
        char temp[3]{};
        for (int i = 0; i < 3; i++)
            temp[i] = cube[getIndex(0,0,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(0,0,i)] = cube[getIndex(3,i,2)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3,i,2)] = cube[getIndex(5,2,2 - i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(5,2,i)] = cube[getIndex(1,i,0)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1,2 - i,0)] = temp[i];
        return *this;
    }
    RubiksCube &b2() override
    {
        this->b();
        this->b();
        return *this;
    }
    RubiksCube &bprime() override
    {
        this->b();
        this->b();
        this->b();
        return *this;
    }
    RubiksCube &d() override
    {
        this->rotateface(5);
        char temp[3] = {};
        for (int i = 0; i <3;i++)
            temp[i] = cube[getIndex(2,2,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(2,2,i)] = cube[getIndex(1,2,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(1,2,i)] = cube[getIndex(4,2,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(4,2,i)] = cube[getIndex(3,2,i)];
        for (int i = 0; i < 3; i++)
            cube[getIndex(3,2,i)] = temp[i];

        return *this;
    }
    RubiksCube &d2() override
    {
        this->d();
        this->d();
        return *this;
    }
    RubiksCube &dprime() override
    {
        this->d();
        this->d();
        this->d();
        return *this;
    }
};