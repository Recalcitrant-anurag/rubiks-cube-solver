#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

template<typename T>
class DummyHeuristic {
public:
    // A real heuristic will read from a 44MB file.
    // This dummy just returns 0 so IDA* temporarily acts like IDDFS.
    int getEstimate(T cube) {
        return 0;
    }
};

#endif // PATTERNDATABASE_H