cmake_minimum_required(VERSION 3.10)
project(cursedray)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
   "-Wall"
   "-Wextra"
   "-Werror"
   "-Wundef"
   "-Wshadow"
   "-Wpointer-arith"
   "-Wcast-align"
   "-Wwrite-strings"
   "-Wswitch-enum"
   "-Wcast-qual"
   "-Wconversion"
   "-Wduplicated-cond"
   "-Wnon-virtual-dtor"
   "-Woverloaded-virtual"
   "-Wformat-nonliteral"
   "-Wformat-security"
   "-Wformat-y2k"
   "-Wformat=2"
   "-Wno-unused-parameter"
   "-Wunused"
   "-Winvalid-pch"
   "-Wlogical-op"
   "-Wmissing-declarations"
   "-Wmissing-field-initializers"
   "-Wmissing-format-attribute"
   "-Wmissing-include-dirs"
   "-Wmissing-noreturn"
   "-Wpacked"
   "-Wredundant-decls"
   "-Wstack-protector"
   "-Wstrict-null-sentinel"
   "-Wdisabled-optimization"
   "-fno-rtti"
   "-Wno-suggest-attribute=format"
   "-DGLM_ENABLE_EXPERIMENTAL"
)

set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -march=native -mtune=native -flto -DNDEBUG")

set(SOURCE_FILES    ${CMAKE_SOURCE_DIR}/src/CursedRay.cpp
                    ${CMAKE_SOURCE_DIR}/src/Sphere.cpp
                    ${CMAKE_SOURCE_DIR}/src/Camera.cpp
                    ${CMAKE_SOURCE_DIR}/src/Scene.cpp
                    ${CMAKE_SOURCE_DIR}/src/Framebuffer.cpp
                    ${CMAKE_SOURCE_DIR}/src/NCDevice.cpp
                    ${CMAKE_SOURCE_DIR}/src/Material.cpp)

set(HEADER_FILES    ${CMAKE_SOURCE_DIR}/include/Ray.hpp
                    ${CMAKE_SOURCE_DIR}/include/Hit.hpp
                    ${CMAKE_SOURCE_DIR}/include/Sphere.hpp
                    ${CMAKE_SOURCE_DIR}/include/Random.hpp
                    ${CMAKE_SOURCE_DIR}/include/Camera.hpp
                    ${CMAKE_SOURCE_DIR}/include/Scene.hpp
                    ${CMAKE_SOURCE_DIR}/include/Framebuffer.hpp
                    ${CMAKE_SOURCE_DIR}/include/NCDevice.hpp
                    ${CMAKE_SOURCE_DIR}/include/Material.hpp)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/submodules/glm"
)

set(LIBS ${LIBS} notcurses notcurses-core m pthread)
add_executable(cray ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(cray PUBLIC ${LIBS})
