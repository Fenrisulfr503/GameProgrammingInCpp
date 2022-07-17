cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project( GAMEPROGRAMMINGCPP )



add_executable( 
    GAMEPROGRAMMINGCPP 
    source/main.cpp 
    source/game.cpp
    source/actor.cpp
    source/component.cpp
    source/image_manager.cpp
    source/sprite_component.cpp
    )

target_link_directories(
    GAMEPROGRAMMINGCPP  
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2/lib/x64/
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2_ttf/lib/x64/
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2_image/lib/x64/
    )

target_include_directories(
    GAMEPROGRAMMINGCPP
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2/include
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2_ttf/include
    ${PROJECT_SOURCE_DIR}/third-party-library/SDL2_image/include
)

target_link_libraries(
    GAMEPROGRAMMINGCPP
    PUBLIC
    SDL2main SDL2 SDL2test SDL2_ttf SDL2_image
)