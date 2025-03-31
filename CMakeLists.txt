cmake_minimum_required(VERSION 3.16)

project(EduGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Add resources (for visualization purposes only)
set(RESOURCE_FILES
    resources/data.txt
)
source_group("Resources" FILES ${RESOURCE_FILES})

add_executable(
    ${PROJECT_NAME}
    main.cpp
    source/Game.h source/Game.cpp
    source/enums/GameState.h source/enums/GameState.cpp
    source/Menu.h source/Menu.cpp
    source/Princess.h source/Princess.cpp
    source/RocketSpawner.h source/RocketSpawner.cpp
    source/Rocket.h source/Rocket.cpp

    ${RESOURCE_FILES}
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
