cmake_minimum_required(VERSION 3.16)

project(EduGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    src/Game.h src/Game.cpp
    src/enums/GameState.h src/enums/GameState.cpp
    src/Menu.h src/Menu.cpp
    src/Princess.h src/Princess.cpp
    src/RocketSpawner.h src/RocketSpawner.cpp
    src/Rocket.h src/Rocket.cpp
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
