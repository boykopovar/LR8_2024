cmake_minimum_required(VERSION 3.10)

project(LR8)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-fsanitize=address")


add_executable(LR8 ${SOURCES}
        Lab_8.cpp
        global_utils.cpp
        global_utils.h
        Task_1/src/Task_1.cpp
        Task_1/include/task_1.h
        Task_1/src/init_products.cpp
        Task_1/include/init_products.h
        Task_1/src/utils_products.cpp
        Task_1/include/utils_products.h
        Task_1/src/tools_products.cpp
        Task_1/include/tools_products.h
        Task_1/src/file_utils.cpp
        Task_1/include/file_utils.h

        Task_2/src/Task_2.cpp
        Task_2/src/file_utils.cpp
        Task_2/src/init_tickets.cpp
        Task_2/src/tools_tickets.cpp
        Task_2/src/utils_tickets.cpp)
