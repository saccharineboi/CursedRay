cmake_minimum_required(VERSION 3.10)
project(cursedray)

# C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

list(APPEND CMAKE_CXX_FLAGS "-Wall \
                             -Wextra \
                             -Werror \
                             -Og \
                             -g \
                             -flto \
                             -Wfloat-equal \
                             -Wundef \
                             -Wshadow \
                             -Wconversion \
                             -march=native \
                             -Winit-self \
                             -Wdisabled-optimization \
                             -Wcast-align \
                             -Wlogical-op \
                             -Woverloaded-virtual \
                             -Wredundant-decls \
                             -Wsign-promo \
                             -Wstrict-null-sentinel \
                             -pedantic \
                             -pedantic-errors \
                             -Wmissing-noreturn \
                             -Wpacked \
                             -Wpointer-arith \
                             -Wwrite-strings \
                             -Winvalid-pch \
                             -Wmissing-include-dirs")

# add source files
set(SOURCE_FILES    ${CMAKE_SOURCE_DIR}/src/main.cpp
                    ${CMAKE_SOURCE_DIR}/src/Sphere.cpp
                    ${CMAKE_SOURCE_DIR}/src/Camera.cpp
                    ${CMAKE_SOURCE_DIR}/src/Scene.cpp
                    ${CMAKE_SOURCE_DIR}/src/Framebuffer.cpp
                    ${CMAKE_SOURCE_DIR}/src/NCDevice.cpp
                    ${CMAKE_SOURCE_DIR}/src/Material.cpp)

# add header files
set(HEADER_FILES    ${CMAKE_SOURCE_DIR}/include/Ray.hpp
                    ${CMAKE_SOURCE_DIR}/include/Hit.hpp
                    ${CMAKE_SOURCE_DIR}/include/Sphere.hpp
                    ${CMAKE_SOURCE_DIR}/include/Random.hpp
                    ${CMAKE_SOURCE_DIR}/include/Camera.hpp
                    ${CMAKE_SOURCE_DIR}/include/Scene.hpp
                    ${CMAKE_SOURCE_DIR}/include/Framebuffer.hpp
                    ${CMAKE_SOURCE_DIR}/include/NCDevice.hpp
                    ${CMAKE_SOURCE_DIR}/include/Material.hpp)

# include directories
include_directories (
    "${CMAKE_SOURCE_DIR}/include"
)

# colored_cube
set(LIBS ${LIBS} notcurses notcurses-core m pthread)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})
