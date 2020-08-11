cmake_minimum_required(VERSION 3.0.0)
set(TARGET_NAME Skeleton)
project(${TARGET_NAME} VERSION 0.1.0)

#if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
#                  "${CMAKE_BINARY_DIR}/conan.cmake")
#endif()

#include(${CMAKE_BINARY_DIR}/conan.cmake)

#conan_cmake_run(CONANFILE conanfile.txt  # or relative build/conanfile.txt
#                BASIC_SETUP CMAKE_TARGETS
#                BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${TARGET_NAME} main.cpp Engine/Collider.cpp Engine/Input.cpp
        Engine/CollisionSystem.cpp Engine/PhysicsSystem.cpp Engine/RenderSystem.cpp Engine/ScriptManager.cpp
        Engine/TextRenderingSystem.cpp Engine/EntitySystem/Component.cpp Engine/EntitySystem/Entity.cpp
        Engine/EntitySystem/EventDispatcher.cpp Engine/EntitySystem/System.cpp
        Engine/Vector2.h Engine/Components/SpriteComponent.h Engine/AssetManager.cpp Engine/AssetManager.h
        Engine/AnimationSystem.cpp Engine/AnimationSystem.h Engine/EntitySystem/Time.cpp
        Engine/Components/AnimationComponent.h Engine/Components/SpriteComponent.cpp
        Engine/Components/AnimationComponent.cpp Engine/Components/TransformComponent.h
        Engine/Components/VelocityComponent.h Engine/Components/TextComponent.h Engine/Components/CollisionComponent.h
        Engine/Components/PhysicsComponent.h Engine/Engine.cpp Engine/Engine.h)

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 17)
target_compile_definitions(${TARGET_NAME} PUBLIC SFML_STATIC)
target_link_libraries(${TARGET_NAME} "${CONAN_LIBS}")

