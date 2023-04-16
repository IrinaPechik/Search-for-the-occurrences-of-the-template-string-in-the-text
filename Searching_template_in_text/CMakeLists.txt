cmake_minimum_required(VERSION 3.21)
project(CHT_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(CHT_2 main.cpp algorithms/CharByCharAlgorithm.cpp algorithms/KMP.cpp algorithms/KMPRefinedFaces.cpp functions/Generation.cpp architecture/Pattern.cpp functions/BustingPatterns.cpp algorithms/RabinKarp.cpp)
