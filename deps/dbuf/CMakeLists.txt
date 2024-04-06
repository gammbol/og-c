cmake_minimum_required(VERSION 3.25)
project(dbuf)

add_library(dbuf src/dbuf.c)

target_include_directories(dbuf PUBLIC include)
