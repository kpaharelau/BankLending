cmake_minimum_required(VERSION 3.10)
project(BankLending)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(BankLending
        Functions.cpp
        Header.h
        Main.cpp
        Menu.cpp CreditType.cpp CreditType.h Client.cpp Client.h Credit.cpp Credit.h)
