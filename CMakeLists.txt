cmake_minimum_required(VERSION 3.31)

project(flightkeys)

add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_sources(${PROJECT_NAME}
PUBLIC
    main.cpp
)