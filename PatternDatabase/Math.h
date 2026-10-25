#ifndef MATH_H
#define MATH_H
/*When the IDA* algorithm pauses to ask for a heuristic estimate, it does this:

It calculates the Permutation (4) and Orientation (150).

It calculates the Final Index (8898).

It instantly looks up that exact slot in the array: int estimate = database[8898];

The array returns the number stored there (e.g., 6 moves).
*/
#include <cstdint>
#include <vector>

using namespace std;
class Math {
public:
    // Precomputed factorials from 0! to 7!
    static constexpr uint32_t factorial[8] = {1, 1, 2, 6, 24, 120, 720, 5040};

    // Precomputed powers of 3 from 3^0 to 3^6
    static constexpr uint32_t power_of_3[7] = {1, 3, 9, 27, 81, 243, 729};

    // 1. BASE-3 CONVERSION (For Corner Twists)
    // Takes an array of 8 corner orientations (0, 1, or 2) and returns an integer from 0 to 2186
    static uint32_t getCornerOrientation(const vector<uint8_t>& orientation) {
        uint32_t rank = 0;
        // We only loop through the first 7 corners. The 8th is mathematically forced.
        for (int i = 0; i < 7; i++) {
            rank += orientation[i] * power_of_3[6 - i];
        }
        return rank;
    }

    // 2. LEHMER CODE CONVERSION (For Corner Positions)
    // Takes an array of 8 corner positions (0 to 7) and returns an integer from 0 to 40319
    static uint32_t getCornerPermutation(const vector<uint8_t>& permutation) {
        uint32_t rank = 0;
        for (int i = 0; i < 7; i++) {
            uint32_t count = 0;
            // Count how many pieces to the right are strictly smaller than the current piece
            for (int j = i + 1; j < 8; j++) {
                if (permutation[j] < permutation[i]) {
                    count++;
                }
            }
            // Multiply that count by the factorial of the remaining slots
            rank += count * factorial[7 - i];
        }
        return rank;
    }
};

#endif // MATH_H