cmake_minimum_required(VERSION 3.16)
project(Prakt_2020 C)

set(CMAKE_C_STANDARD 11)

add_executable(Prakt_2020 main_28.c odu_28.c odu_28.h funk_28.c funk_28.h)

include_directories(Prakt_2020 f:/ClionProjects/EmbeddedPython3/include/)
#link_libraries(Prakt_2020 SHARED f:/ClionProjects/EmbeddedPython3/lib/python34.dll)