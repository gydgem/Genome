cmake_minimum_required(VERSION 3.28)
project(Genome)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genome main.cpp
        gene.h
        genome.h
        genome_common.h)
