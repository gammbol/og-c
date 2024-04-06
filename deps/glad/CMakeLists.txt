cmake_minimum_required(VERSION 3.25)

project(glad)

add_library(glad src/glad.c)

target_include_directories(glad PRIVATE include)
