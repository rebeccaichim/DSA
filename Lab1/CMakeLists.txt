cmake_minimum_required(VERSION 3.24)
project(SortedMap)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortedMap App.cpp SortedMap.h SortedMap.cpp SMIterator.h SMIterator.cpp ExtendedTest.h ExtendedTest.cpp ShortTest.h ShortTest.cpp)
