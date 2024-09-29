cmake_minimum_required(VERSION 3.30)

project(Lox LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    src/Runner.cpp
    src/Util.cpp
    src/Scanner.cpp
    src/Token.cpp
)

set(HEADERS
    src/Runner.h
    src/Util.h
    src/Scanner.h
    src/TokenType.h
    src/Token.h
)

add_executable(Lox ${SOURCES} ${HEADERS})

target_include_directories(Lox PRIVATE src)
target_include_directories(Lox PRIVATE external)