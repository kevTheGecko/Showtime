cmake_minimum_required(VERSION 3.16)

project(Showtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Showtime
    ShowtimeMain.cpp
    Movie.cpp
    MovieManager.cpp
    HighestRatedSelect.cpp
    NewestMovieSelect.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

target_link_libraries(Showtime PRIVATE Qt6::Widgets)

target_include_directories(Showtime PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

