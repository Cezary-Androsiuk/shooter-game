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

    # /SUBSYSTEM:CONSOLE
    WIN32

    ${RESOURCE_FILES} # add resources to QtCreator

    main.cpp
    source/Game.h source/Game.cpp

    # UTILS
    source/utils/RectEdges.h source/utils/RectEdges.cpp
    source/utils/Constants.h source/utils/Constants.cpp
    source/utils/Random.h source/utils/Random.cpp
    source/utils/json.hpp

    # ENUMS
    source/enums/GameState.h source/enums/GameState.cpp

    # ENVIRONMENT
    source/environment/Obstacle.h source/environment/Obstacle.cpp
    source/environment/Map.h source/environment/Map.cpp

    # STATES
    source/states/StateManager.h source/states/StateManager.cpp
    source/states/State.h source/states/State.cpp
    source/states/Menu.h source/states/Menu.cpp
    source/states/Play.h source/states/Play.cpp

    # OBJECTS
    ## ENTITIES
    source/objects/entities/Player.h source/objects/entities/Player.cpp
    source/objects/entities/Enemy.h source/objects/entities/Enemy.cpp
    source/objects/entities/Ghost.h source/objects/entities/Ghost.cpp
    source/objects/entities/Zombie.h source/objects/entities/Zombie.cpp
    source/objects/entities/Skeleton.h source/objects/entities/Skeleton.cpp

    # MECHANICS
    source/mechanics/DeltaTime.h source/mechanics/DeltaTime.cpp
    ## SPAWNERS
    source/mechanics/spawners/EnemySpawner.h source/mechanics/spawners/EnemySpawner.cpp

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
    source/utils/Data.h source/utils/Data.cpp


)

file(GLOB RESOURCE_FILES_LIST "${CMAKE_SOURCE_DIR}/resources/*")

add_custom_target(resources_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
    DEPENDS ${RESOURCE_FILES_LIST}
    COMMENT "Copying resources to build directory"
)

add_dependencies(${PROJECT_NAME} resources_copy)

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


# if (WIN32)
#     target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE)
# endif()
