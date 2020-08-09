cmake_minimum_required(VERSION 3.0.0)
project(Rpg VERSION 0.1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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



#set(SFML_DIR "/Users/witek/Projects/sfml/Frameworks/SFML.framework/Resources/CMake")
#find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

add_executable(Rpg main.cpp Engine/Collider.cpp Engine/Input.cpp
        Engine/CollisionSystem.cpp Engine/PhysicsSystem.cpp Engine/RenderSystem.cpp Engine/ScriptManager.cpp
        Engine/TextRenderingSystem.cpp Engine/EntitySystem/Component.cpp Engine/EntitySystem/Entity.cpp Engine/EntitySystem/EventDispatcher.cpp
        Engine/EntitySystem/System.cpp
        Engine/Vector2.h Components/SpriteComponent.h Engine/AssetManager.cpp Engine/AssetManager.h)

set_property(TARGET Rpg PROPERTY CXX_STANDARD 17)
target_compile_definitions(Rpg PUBLIC SFML_STATIC)
message("${CONAN_LIBS}")
target_link_libraries(Rpg "${CONAN_LIBS}")

