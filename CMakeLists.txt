cmake_minimum_required(VERSION 3.27)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

add_executable(TI_301_PJT
        main.c
        adjacency.c
        cell.c
        list.c
        utils.c
        mermaid.c
        markov.c
        stack.c
        tarjan.c
)