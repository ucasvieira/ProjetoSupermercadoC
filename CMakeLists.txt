cmake_minimum_required(VERSION 3.30)
project(Teste C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(ProjetoSupermercadoC login.c main.c gondolas.c pdv.c
        admin.c)
