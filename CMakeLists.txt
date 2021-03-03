project(BetterThanSTL-Map)

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

file(GLOB my_sources *.h *.cpp *.ui)

add_executable(BetterThanSTL-Map ${my_sources})