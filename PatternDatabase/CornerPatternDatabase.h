#ifndef CORNER_PATTERN_DATABASE_H
#define CORNER_PATTERN_DATABASE_H

#include "../Model/RubiksCubeBitboard.h"
#include "PatternDatabase.h"
#include "Math.h"

using namespace std;

class CornerPatternDatabase : public PatternDatabase<RubiksCubeBitboard> {
public:
    // When created, immediately tell the base class the exact size and what to name the file
    CornerPatternDatabase() : PatternDatabase(88179840, "corner_database.bin") {}

    // Fulfilling the "= 0" contract from the base class
    uint32_t getDatabaseIndex(const RubiksCubeBitboard& cube) const override {

        // 1. Extract the corners from the 64-bit integer
        vector<uint8_t> corner_positions = cube.getCornerPositions();
        vector<uint8_t> corner_orientations = cube.getCornerOrientations();

        // 2. Use our Math.h to get the Lehmer code and Base-3 index
        uint32_t perm = Math::getCornerPermutation(corner_positions);
        uint32_t orient = Math::getCornerOrientation(corner_orientations);

        // 3. Combine them to map perfectly into the 88 million slot array
        return (perm * 2187) + orient;
    }
};

#endif // CORNER_PATTERN_DATABASE_H