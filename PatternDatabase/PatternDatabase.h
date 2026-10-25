#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template<typename T>
class PatternDatabase {
protected:
    vector<uint8_t> database;  // The massive 1D array (Our 88MB RAM allocation)
    size_t size;               // How many states it holds (e.g., 88,179,840)
    string filepath;           // Where to save the file on your hard drive

    // Pure virtual function: Every specific database (like Corners or Edges)
    // MUST define its own way to calculate the Index using the Math.h file.
    virtual uint32_t getDatabaseIndex(const T& cube) const = 0;

public:
    // Constructor allocates the array and fills it with 255 (representing "unsolved/infinity")
    PatternDatabase(size_t _size, string _filepath) : size(_size), filepath(_filepath) {
        database.assign(size, 255);
    }

    // This is the EXACT function your IDAstarSolver calls to get the estimate!
    int getEstimate(const T& cube) const {
        return database[getDatabaseIndex(cube)];
    }

    // Used by our generator script to write new move counts into the array
    bool setNumMoves(const T& cube, uint8_t numMoves) {
        uint32_t index = getDatabaseIndex(cube);
        if (database[index] > numMoves) {
            database[index] = numMoves;
            return true;
        }
        return false;
    }

    // Instantly loads the 88MB file from your hard drive into the array
    bool fromFile() {
        ifstream file(filepath, ios::binary);
        if (!file.is_open()) return false;
        file.read(reinterpret_cast<char*>(database.data()), size);
        file.close();
        return true;
    }

    // Dumps the fully generated array from RAM straight onto your hard drive
    bool toFile() const {
        ofstream file(filepath, ios::binary);
        if (!file.is_open()) return false;
        file.write(reinterpret_cast<const char*>(database.data()), size);
        file.close();
        return true;
    }
};

#endif // PATTERNDATABASE_H