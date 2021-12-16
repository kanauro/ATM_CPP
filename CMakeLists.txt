cmake_minimum_required(VERSION 3.17)
project(Project)

set(SOURCE_FILES
        Bankomat_1.h
        Bankomat_1.cpp
        Bank_1.cpp
        Bank_1.h
        ATM_Money_2.cpp
        Operations_3.cpp
        PrintCheck_4.cpp
        test_1.cpp
        test_2.cpp
        test_3.cpp
        test_4.cpp
        
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

include_directories(GoogleTest)
add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})
