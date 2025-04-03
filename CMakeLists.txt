cmake_minimum_required(VERSION 3.16)

project(ShooterGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/source)

# Add resources (for visualization purposes only)
set(RESOURCE_FILES
    resources/data.txt
    resources/fonts/OpenSans-Regular.ttf
    resources/images/default.png
)
source_group("Resources" FILES ${RESOURCE_FILES})

add_executable(
    ${PROJECT_NAME}
    main.cpp
    source/Game.h source/Game.cpp

    # ENUMS
    source/enums/GameState.h source/enums/GameState.cpp

    # STATES
    source/states/Menu.h source/states/Menu.cpp
    source/states/Play.h source/states/Play.cpp

    # OBJECTS
    source/Player.h source/Player.cpp
    source/EnemySpawner.h source/EnemySpawner.cpp
    source/Enemy.h source/Enemy.cpp

    # SFML SimpleGUI
    source/SimpleGUI/common.hpp
    source/SimpleGUI/SguiObject.cpp source/SimpleGUI/SguiObject.hpp
    source/SimpleGUI/Button.cpp source/SimpleGUI/Button.hpp
    source/SimpleGUI/CheckBox.cpp source/SimpleGUI/CheckBox.hpp
    source/SimpleGUI/GroupBox.cpp source/SimpleGUI/GroupBox.hpp
    source/SimpleGUI/ImageBox.cpp source/SimpleGUI/ImageBox.hpp
    source/SimpleGUI/Label.cpp source/SimpleGUI/Label.hpp
    source/SimpleGUI/RadioButton.cpp source/SimpleGUI/RadioButton.hpp
    source/SimpleGUI/Switch.cpp source/SimpleGUI/Switch.hpp
    source/SimpleGUI/TabControl.cpp source/SimpleGUI/TabControl.hpp

    ${RESOURCE_FILES} # allows to copy resources within compilation
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
