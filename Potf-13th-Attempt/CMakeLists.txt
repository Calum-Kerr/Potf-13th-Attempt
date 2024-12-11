cmake_minimum_required(VERSION 3.10)
project(Potf-13th-Attempt)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define the executable
add_executable(Potf-13th-Attempt
    Main.cpp
    GameWorld.cpp
    MainMenu.cpp
    PauseMenu.cpp
    Player.cpp
    SettingsMenu.cpp
)

# Include directories
target_include_directories(Potf-13th-Attempt PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Potf-13th-Attempt sfml-graphics sfml-window sfml-system)

# Specify asset directory
set(ASSET_DIR ${CMAKE_BINARY_DIR}/../assets)

# Copy assets to ../assets folder during the build process
add_custom_command(TARGET Potf-13th-Attempt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/160x160\ background\ tilemap.png ${ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Basic\ Tilemap.png ${ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CloisterBlack.ttf ${ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Player*.png ${ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sfml-*.dll ${ASSET_DIR}
)