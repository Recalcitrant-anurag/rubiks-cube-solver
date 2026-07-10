#include "RubiksCube.h"
/*returning the first letter for a given color*/
char RubiksCube::getColorLetter(COLOR color){
    switch(color){
        case COLOR::BLUE:
            return 'B';
        case COLOR::WHITE:
            return 'W';
        case COLOR::GREEN:
            return 'G';
        case COLOR::YELLOW:
            return 'Y';
        case COLOR::ORANGE:
            return 'O';
        case COLOR::RED:
            return 'R';
    }
}
/*to get the move name in a string format*/
string RubiksCube::getMove(MOVE mov){
    switch(mov){
        case MOVE::L:
            return "L";
        case MOVE::LPRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::U:
            return "U";
        case MOVE::UPRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::F:
            return "F";
        case MOVE::FPRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::R:
            return "R";
        case MOVE::RPRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::B:
            return "B";
        case MOVE::BPRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
        case MOVE::D:
            return "D";
        case MOVE::DPRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
    }
}
void RubiksCube::print() const{
    cout<<"Rubik's Cube \n\n";
    for(int row=0;row<3;row++){
        for(int col=0;col<7;col++)cout<<" ";
        for(int col=0;col<=2;col++){
            cout<<getColorLetter(getColor(FACE::UP,row,col))<<" ";
        }
        cout<<'\n';
    }
}
RubiksCube& RubiksCube::move(MOVE mov){
    switch(mov){
        case MOVE::L:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::LPRIME:
            return this->lprime();
        case MOVE::R:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::RPRIME:
            return this->rprime();
        case MOVE::U:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::UPRIME:
            return this->uprime();
        case MOVE::F:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::FPRIME:
            return this->fprime();
        case MOVE::B:
            return this->b();
        case MOVE::B2:
            return this->b2();
        case MOVE::BPRIME:
            return this->bprime();
        case MOVE::D:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::DPRIME:
            return this->dprime();
    }
}
RubiksCube& RubiksCube::invert(MOVE mov){
    switch(mov){
        case MOVE::L:
            return this->l2();
        case MOVE::L2:
            return this->l();
        case MOVE::LPRIME:
            return this->lprime();
        case MOVE::R:
            return this->r2();
        case MOVE::R2:
            return this->r();
        case MOVE::RPRIME:
            return this->rprime();
        case MOVE::U:
            return this->u2();
        case MOVE::U2:
            return this->u();
        case MOVE::UPRIME:
            return this->uprime();
        case MOVE::F:
            return this->f2();
        case MOVE::F2:
            return this->f();
        case MOVE::FPRIME:
            return this->fprime();
        case MOVE::B:
            return this->b2();
        case MOVE::B2:
            return this->b();
        case MOVE::BPRIME:
            return this->bprime();
        case MOVE::D:
            return this->d2();
        case MOVE::D2:
            return this->d();
        case MOVE::DPRIME:
            return this->dprime();
    }
}
vector<RubiksCube::MOVE> RubiksCube::randomShuffleCube(unsigned times){
    vector<MOVE>moves_performed;
    srand(time(0));
    for(unsigned i=0;i<times;i++){
        unsigned mov=rand()%18;
        moves_performed.emplace_back(static_cast<MOVE>(mov));
        this->move(static_cast<MOVE>(mov));
    }
    return moves_performed;
}