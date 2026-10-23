cmake_minimum_required(VERSION 4.1)
project(rubiks_cube_solver)

set(CMAKE_CXX_STANDARD 14)

include_directories(Model)

add_executable(rubiks_cube_solver
        Model/RubiksCube.cpp
        Model/RubiksCube.h
        Model/RubiksCube3dArray.h
        Model/RubiksCube1dArray.h
        Model/RubiksCubeBitboard.h
        Solver/BFSSolver.h
        main.cpp
        Solver/DFSSolver.h
        Solver/IDDFSSolver.h
        Solver/IDAstarSolver.h
        Solver/PatternDatabase.h
)
