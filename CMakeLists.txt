cmake_minimum_required(VERSION 3.16)

project(Showtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.12.0/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_executable(Showtime
    # Source files
    src/ShowtimeMain.cpp
    src/Movie.cpp
    src/MovieManager.cpp
    src/HighestRatedSelect.cpp
    src/NewestMovieSelect.cpp
    src/mainwindow.cpp

    # Headers
    include/Movie.h
    include/MovieManager.h
    include/SelectMethod.h
    include/HighestRatedSelect.h
    include/NewestMovieSelect.h
    include/mainwindow.h

    # Qt Designer forms
    ui/mainwindow.ui
)

target_link_libraries(Showtime PRIVATE Qt6::Widgets)

target_include_directories(Showtime PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    get_filename_component(QT_BIN_DIR "${Qt6_DIR}/../../../bin" ABSOLUTE)
    add_custom_command(TARGET Showtime POST_BUILD
        COMMAND "${QT_BIN_DIR}/windeployqt.exe" --debug --no-translations
                "$<TARGET_FILE:Showtime>")
endif()