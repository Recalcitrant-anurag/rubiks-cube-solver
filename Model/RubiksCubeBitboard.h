//
// Created by Anurag Anand on 14-07-2026.
//
// Created by Anurag Anand on 14-07-2026.
#ifndef RUBIKS_CUBE_BITBOARD_H
#define RUBIKS_CUBE_BITBOARD_H


#include "RubiksCube.h"
class RubiksCubeBitboard : public RubiksCube {
private:
    const uint64_t ONE_8=0xFF;// F means 15 which in binary is 1111 so this is a clean way
    // of writing 1111 1111 meaning 8 bits of 1
    void rotateface(int face){
        cube[face]=(cube[face]<<16)|(cube[face]>>48);
    }
    // Helper 1: Identifies exactly which corner piece is in a specific slot using a unique color bitmask
    uint8_t getCornerIndex(uint8_t c1, uint8_t c2, uint8_t c3) const {
        uint8_t bitmask = (1 << c1) | (1 << c2) | (1 << c3);
        switch (bitmask) {
            case 19: return 0; // U-L-B (White, Green, Orange)
            case 25: return 1; // U-B-R (White, Orange, Blue)
            case 13: return 2; // U-R-F (White, Blue, Red)
            case 7:  return 3; // U-F-L (White, Red, Green)
            case 38: return 4; // D-L-F (Yellow, Green, Red)
            case 44: return 5; // D-F-R (Yellow, Red, Blue)
            case 56: return 6; // D-R-B (Yellow, Blue, Orange)
            case 50: return 7; // D-B-L (Yellow, Orange, Green)
        }
        return 0;
    }

    // Helper 2: Identifies how the corner is twisted (0, 1, or 2)
    uint8_t getCornerOrientation(uint8_t c1, uint8_t c2, uint8_t c3) const {
        if (c1 == 0 || c1 == 5) return 0; // White/Yellow is on the Top/Bottom face (Solved orientation)
        if (c2 == 0 || c2 == 5) return 1; // White/Yellow is twisted clockwise
        if (c3 == 0 || c3 == 5) return 2; // White/Yellow is twisted counter-clockwise
        return 0;
    }
public:
    uint64_t cube[6]{};
    RubiksCubeBitboard() {
        for (int face=0;face<6;face++) {
            uint64_t color=1<<face;
            cube[face]=0;
            for (int i=0;i<8;i++) {
                cube[face]|=color;
                color<<=8;
            }
        }
    }
    // for equality operator in BFSSolver
    bool operator==(const RubiksCubeBitboard &r1) const {
        for (int i = 0; i < 6; i++) {
            if (cube[i] != r1.cube[i]) return false;
        }
        return true;
    }
    COLOR getColor(FACE face,unsigned row,unsigned col) const override {
        if (row==1 && col==1)return COLOR(int(face));
        int bit_asked=0;
        if (row==0) {
            bit_asked=col;
        }else if (row==2) {
            bit_asked=6-col;
        }else {
            bit_asked=7-(col<<1);
        }
        int color=(cube[(int)face]>>(8*bit_asked)) &ONE_8;
        return COLOR(__builtin_ctz(color));
    }
    bool isSolved() const override {
        for (int face=0;face<6;face++) {
            uint64_t color=1<<face;
            uint64_t solved_face=0;
            for (int i=0;i<8;i++) {
                solved_face|=color;
                color<<=8;
            }
            if (cube[(int)face]!=solved_face)return false;
        }
        return true;
    }
    RubiksCube &u() override {
        this->rotateface(0);
        uint64_t ONE_24=ONE_8 | (ONE_8<<8) | (ONE_8<<16);
        uint64_t Zero_24=~ONE_24;
        uint64_t face_1 = cube[1] & ONE_24;
        for (int i=1;i<=3;i++) {
            cube[i] = (cube[i] & Zero_24) | (cube[i+1] & ONE_24);
        }
        cube[4] = (cube[4] & Zero_24) | face_1;
        return *this;
    }
    RubiksCube &uprime() override {
        this->u();
        this->u();
        this->u();
        return *this;
    }
    RubiksCube &u2() override {
        this->u();
        this->u();
        return *this;
    }
    RubiksCube &d() override {
        this->rotateface(5);
        uint64_t ONE_4_5_6=(ONE_8<<32)|(ONE_8<<40)|(ONE_8<<48);
        uint64_t ZERO_4_5_6=~ONE_4_5_6;
        uint64_t face_4=cube[4]&ONE_4_5_6;
        for (int i=4;i>=2;i--) {
            cube[i]=(cube[i]&ZERO_4_5_6)|(cube[i-1]&ONE_4_5_6);
        }
        cube[1]=(cube[1]&ZERO_4_5_6)|(face_4);
        return *this;
    }
    RubiksCube &dprime() override {
        this->d();
        this->d();
        this->d();
        return *this;
    }
    RubiksCube &d2() override {
        this->d();
        this->d();
        return *this;
    }
    RubiksCube &l() override {
        this->rotateface(1);
        uint64_t ONE_0_6_7=ONE_8 | (ONE_8<<48)|(ONE_8<<56);
        uint64_t ZERO_0_6_7=~ONE_0_6_7;
        uint64_t ONE_2_3_4=(ONE_8<<16) | (ONE_8<<24)|(ONE_8<<32);
        uint64_t ZERO_2_3_4=~ONE_2_3_4;
        // saving up the up face
        uint64_t face_0=cube[0]&ONE_0_6_7;
        uint64_t face_4_4_bit=cube[4]&(ONE_8<<32);
        uint64_t face_4=(((cube[4]<<32)&((ONE_8<<48)|(ONE_8<<56)))|(face_4_4_bit>>32))&(ONE_0_6_7);
        cube[0]=(cube[0]&ZERO_0_6_7)|(face_4);
        uint64_t face_5_0_bit=cube[5]&ONE_8;
        uint64_t face_5=((cube[5]>>32)&((ONE_8<<16)|(ONE_8<<24)))|(face_5_0_bit<<32);
        cube[4]=(cube[4]&ZERO_2_3_4)|(face_5);
        cube[5]=(cube[5]&ZERO_0_6_7)|(cube[2]&ONE_0_6_7);
        cube[2]=(cube[2]&ZERO_0_6_7)|(face_0);
        return *this;
    }
    RubiksCube &lprime() override {
        this->l();
        this->l();
        this->l();
        return *this;
    }
    RubiksCube &l2() override {
        this->l();
        this->l();
        return *this;
    }
    RubiksCube &r() override {
        this->rotateface(3);
        uint64_t ONE_0_6_7 = ONE_8 | (ONE_8<<48) | (ONE_8<<56);
        uint64_t ZERO_0_6_7 = ~ONE_0_6_7;
        uint64_t ONE_2_3_4 = (ONE_8<<16) | (ONE_8<<24) | (ONE_8<<32);
        uint64_t ZERO_2_3_4 = ~ONE_2_3_4;
        uint64_t face_0 = cube[0] & ONE_2_3_4;
        cube[0] = (cube[0] & ZERO_2_3_4) | (cube[2] & ONE_2_3_4);
        cube[2] = (cube[2] & ZERO_2_3_4) | (cube[5] & ONE_2_3_4);
        uint64_t face_4_0_bit = cube[4] & ONE_8;
        uint64_t face_4 = ((cube[4] >> 32) & ((ONE_8<<16) | (ONE_8<<24))) | (face_4_0_bit << 32);
        cube[5] = (cube[5] & ZERO_2_3_4) | face_4;
        uint64_t face_0_4_bit = face_0 & (ONE_8<<32);
        uint64_t face_0_mapped = ((face_0 << 32) & ((ONE_8<<48) | (ONE_8<<56))) | (face_0_4_bit >> 32);
        cube[4] = (cube[4] & ZERO_0_6_7) | face_0_mapped;
        return *this;
    }
    RubiksCube &rprime() override {
        this->r();
        this->r();
        this->r();
        return *this;
    }
    RubiksCube &r2() override {
        this->r();
        this->r();
        return *this;
    }
    RubiksCube &f() override {
        this->rotateface(2);
        uint64_t ONE_0_1_2 = ONE_8 | (ONE_8<<8) | (ONE_8<<16);
        uint64_t ZERO_0_1_2 = ~ONE_0_1_2;
        uint64_t ONE_2_3_4 = (ONE_8<<16) | (ONE_8<<24) | (ONE_8<<32);
        uint64_t ZERO_2_3_4 = ~ONE_2_3_4;
        uint64_t ONE_4_5_6 = (ONE_8<<32) | (ONE_8<<40) | (ONE_8<<48);
        uint64_t ZERO_4_5_6 = ~ONE_4_5_6;
        uint64_t ONE_0_6_7 = ONE_8 | (ONE_8<<48) | (ONE_8<<56);
        uint64_t ZERO_0_6_7 = ~ONE_0_6_7;
        uint64_t face_0 = cube[0] & ONE_4_5_6;
        uint64_t face_1_2_bit = (cube[1] & (ONE_8<<16)) << 32;
        uint64_t face_1_3_bit = (cube[1] & (ONE_8<<24)) << 16;
        uint64_t face_1_4_bit = (cube[1] & (ONE_8<<32));
        uint64_t face_1_mapped = face_1_2_bit | face_1_3_bit | face_1_4_bit;
        cube[0] = (cube[0] & ZERO_4_5_6) | face_1_mapped;
        uint64_t face_5_mapped = (cube[5] & ONE_0_1_2) << 16;
        cube[1] = (cube[1] & ZERO_2_3_4) | face_5_mapped;
        uint64_t face_3_0_bit = (cube[3] & ONE_8) << 16;
        uint64_t face_3_6_7 = (cube[3] & ((ONE_8<<48) | (ONE_8<<56))) >> 48;
        uint64_t face_3_mapped = face_3_0_bit | face_3_6_7;
        cube[5] = (cube[5] & ZERO_0_1_2) | face_3_mapped;
        uint64_t face_0_6_bit = (face_0 & (ONE_8<<48)) >> 48;
        uint64_t face_0_4_5 = (face_0 & ((ONE_8<<32) | (ONE_8<<40))) << 16;
        uint64_t face_0_mapped = face_0_6_bit | face_0_4_5;
        cube[3] = (cube[3] & ZERO_0_6_7) | face_0_mapped;
        return *this;
    }
    RubiksCube &f2() override {
        this->f();
        this->f();
        return *this;
    }
    RubiksCube &fprime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    }
    RubiksCube &b() override {
        this->rotateface(4);
        uint64_t ONE_0_1_2 = ONE_8 | (ONE_8<<8) | (ONE_8<<16);
        uint64_t ZERO_0_1_2 = ~ONE_0_1_2;
        uint64_t ONE_2_3_4 = (ONE_8<<16) | (ONE_8<<24) | (ONE_8<<32);
        uint64_t ZERO_2_3_4 = ~ONE_2_3_4;
        uint64_t ONE_4_5_6 = (ONE_8<<32) | (ONE_8<<40) | (ONE_8<<48);
        uint64_t ZERO_4_5_6 = ~ONE_4_5_6;
        uint64_t ONE_0_6_7 = ONE_8 | (ONE_8<<48) | (ONE_8<<56);
        uint64_t ZERO_0_6_7 = ~ONE_0_6_7;
        uint64_t face_0 = cube[0] & ONE_0_1_2;
        uint64_t face_3_2_bit = (cube[3] & (ONE_8<<16));
        uint64_t face_3_3_bit = (cube[3] & (ONE_8<<24)) >> 16;
        uint64_t face_3_4_bit = (cube[3] & (ONE_8<<32)) >> 32;
        uint64_t face_3_mapped = face_3_2_bit | face_3_3_bit | face_3_4_bit;
        cube[0] = (cube[0] & ZERO_0_1_2) | face_3_mapped;
        uint64_t face_5_mapped = (cube[5] & ONE_4_5_6) >> 16;
        cube[3] = (cube[3] & ZERO_2_3_4) | face_5_mapped;
        uint64_t face_1_0_bit = (cube[1] & ONE_8) << 48;
        uint64_t face_1_6_7 = (cube[1] & ((ONE_8<<48) | (ONE_8<<56))) >> 16;
        uint64_t face_1_mapped = face_1_0_bit | face_1_6_7;
        cube[5] = (cube[5] & ZERO_4_5_6) | face_1_mapped;
        uint64_t face_0_0_bit = face_0 & ONE_8;
        uint64_t face_0_1_bit = (face_0 & (ONE_8<<8)) << 48;
        uint64_t face_0_2_bit = (face_0 & (ONE_8<<16)) << 32;
        uint64_t face_0_mapped = face_0_0_bit | face_0_1_bit | face_0_2_bit;
        cube[1] = (cube[1] & ZERO_0_6_7) | face_0_mapped;
        return *this;
    }
    RubiksCube &b2() override {
        this->b();
        this->b();
        return *this;
    }
    RubiksCube &bprime() override {
        this->b();
        this->b();
        this->b();
        return *this;
    }
    // ---------------- CORNER PATTERN DATABASE EXTRACTION ----------------

    vector<uint8_t> getCornerPositions() const override {
        vector<uint8_t> ret(8);
        ret[0] = getCornerIndex((int)getColor(FACE::UP, 0, 0), (int)getColor(FACE::LEFT, 0, 0), (int)getColor(FACE::BACK, 0, 2));
        ret[1] = getCornerIndex((int)getColor(FACE::UP, 0, 2), (int)getColor(FACE::BACK, 0, 0), (int)getColor(FACE::RIGHT, 0, 2));
        ret[2] = getCornerIndex((int)getColor(FACE::UP, 2, 2), (int)getColor(FACE::RIGHT, 0, 0), (int)getColor(FACE::FRONT, 0, 2));
        ret[3] = getCornerIndex((int)getColor(FACE::UP, 2, 0), (int)getColor(FACE::FRONT, 0, 0), (int)getColor(FACE::LEFT, 0, 2));

        ret[4] = getCornerIndex((int)getColor(FACE::DOWN, 0, 0), (int)getColor(FACE::LEFT, 2, 2), (int)getColor(FACE::FRONT, 2, 0));
        ret[5] = getCornerIndex((int)getColor(FACE::DOWN, 0, 2), (int)getColor(FACE::FRONT, 2, 2), (int)getColor(FACE::RIGHT, 2, 0));
        ret[6] = getCornerIndex((int)getColor(FACE::DOWN, 2, 2), (int)getColor(FACE::RIGHT, 2, 2), (int)getColor(FACE::BACK, 2, 0));
        ret[7] = getCornerIndex((int)getColor(FACE::DOWN, 2, 0), (int)getColor(FACE::BACK, 2, 2), (int)getColor(FACE::LEFT, 2, 0));
        return ret;
    }

    vector<uint8_t> getCornerOrientations() const override {
        vector<uint8_t> ret(8);
        ret[0] = getCornerOrientation((int)getColor(FACE::UP, 0, 0), (int)getColor(FACE::LEFT, 0, 0), (int)getColor(FACE::BACK, 0, 2));
        ret[1] = getCornerOrientation((int)getColor(FACE::UP, 0, 2), (int)getColor(FACE::BACK, 0, 0), (int)getColor(FACE::RIGHT, 0, 2));
        ret[2] = getCornerOrientation((int)getColor(FACE::UP, 2, 2), (int)getColor(FACE::RIGHT, 0, 0), (int)getColor(FACE::FRONT, 0, 2));
        ret[3] = getCornerOrientation((int)getColor(FACE::UP, 2, 0), (int)getColor(FACE::FRONT, 0, 0), (int)getColor(FACE::LEFT, 0, 2));

        ret[4] = getCornerOrientation((int)getColor(FACE::DOWN, 0, 0), (int)getColor(FACE::LEFT, 2, 2), (int)getColor(FACE::FRONT, 2, 0));
        ret[5] = getCornerOrientation((int)getColor(FACE::DOWN, 0, 2), (int)getColor(FACE::FRONT, 2, 2), (int)getColor(FACE::RIGHT, 2, 0));
        ret[6] = getCornerOrientation((int)getColor(FACE::DOWN, 2, 2), (int)getColor(FACE::RIGHT, 2, 2), (int)getColor(FACE::BACK, 2, 0));
        ret[7] = getCornerOrientation((int)getColor(FACE::DOWN, 2, 0), (int)getColor(FACE::BACK, 2, 2), (int)getColor(FACE::LEFT, 2, 0));
        return ret;
    }
};
//This is the H that BFSSolver template is asking for.
//It XORs all 6 faces together to generate a single, unique memory ID for the map.
struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard &r1) const {
        uint64_t final_hash = r1.cube[0];
        for (int i = 1; i < 6; i++) {
            // Golden ratio shift prevents symmetrical hash collisions
            final_hash ^= r1.cube[i] + 0x9e3779b9 + (final_hash << 6) + (final_hash >> 2);
        }
        return final_hash;
    }
};
#endif // RUBIKS_CUBE_BITBOARD_H