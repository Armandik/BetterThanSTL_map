project(BetterThanSTL-Map)

# CMake 3.* necessario per Qt
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# ottengo tutti i sorgenti
file(GLOB my_sources *.h *.cpp *.qrc *.ui)

# attivo funzionalita' specifiche di CMake per Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# aggiungo eseguibile
add_executable(BetterThanSTL-Map ${my_sources})