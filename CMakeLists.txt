cmake_minimum_required(VERSION 3.16)

project(ShooterGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/source)

# Add resources (for visualization purposes only)
set(RESOURCE_FILES
    resources/initial_data.json
    resources/fonts/OpenSans-Regular.ttf
    resources/fonts/Inkfree.ttf
    resources/images/default.png
    resources/shaders/blur.frag
    resources/sprites/main_sprite_texture.png
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
    source/utils/DeltaTime.h source/utils/DeltaTime.cpp
    source/utils/RectEdges.h source/utils/RectEdges.cpp
    source/utils/Constants.h source/utils/Constants.cpp
    source/utils/Random.h source/utils/Random.cpp
    source/utils/Support.h source/utils/Support.cpp
    source/utils/json.hpp
    source/utils/InitialData.h source/utils/InitialData.cpp
    source/utils/GlobalData.h source/utils/GlobalData.cpp
    source/utils/AdvancedComputation.h source/utils/AdvancedComputation.cpp

    # ENUMS
    source/enums/GameState.h source/enums/GameState.cpp

    # ENVIRONMENT
    source/environment/Obstacle.h source/environment/Obstacle.cpp
    source/environment/Map.h source/environment/Map.cpp
    source/environment/Sound.h source/environment/Sound.cpp

    # STATES
    source/states/StateManager.h source/states/StateManager.cpp
    source/states/State.h source/states/State.cpp
    source/states/MenuState.h source/states/MenuState.cpp
    source/states/PlayState.h source/states/PlayState.cpp
    source/states/PausePlayState.h source/states/PausePlayState.cpp
    source/states/DefeatState.h source/states/DefeatState.cpp

    # OBJECTS
    source/objects/Weapon.h source/objects/Weapon.cpp
    source/objects/Bullet.h source/objects/Bullet.cpp
    source/objects/Armor.h source/objects/Armor.cpp
    ## ENTITIES
    source/objects/entities/Player.h source/objects/entities/Player.cpp
    source/objects/entities/Enemy.h source/objects/entities/Enemy.cpp
    source/objects/entities/Ghost.h source/objects/entities/Ghost.cpp
    source/objects/entities/Zombie.h source/objects/entities/Zombie.cpp
    source/objects/entities/Skeleton.h source/objects/entities/Skeleton.cpp

    # MECHANICS
    ## SPAWNERS
    source/mechanics/spawners/EnemySpawner.h source/mechanics/spawners/EnemySpawner.cpp

    # VIEWS
    source/views/StartMenuView.h source/views/StartMenuView.cpp
    source/views/ShopView.h source/views/ShopView.cpp

    # ANIMATIONS
    source/animations/Animation.h source/animations/Animation.cpp
    source/animations/GotDamageAnimation.h source/animations/GotDamageAnimation.cpp

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
    sfml-audio
)


# if (WIN32)
#     target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE)
# endif()
