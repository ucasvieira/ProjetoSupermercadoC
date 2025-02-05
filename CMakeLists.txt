cmake_minimum_required(VERSION 3.30)
project(Teste C)

set(CMAKE_C_STANDARD 23)

add_executable(Teste login.c main.c gondolas.c pdv.c
        admin.c USUARIOS.DAT GONDOLAS.DAT)
