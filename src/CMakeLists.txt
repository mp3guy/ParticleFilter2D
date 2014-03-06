cmake_minimum_required(VERSION 2.6.0)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_definitions(-Wall)

set(CMAKE_CXX_FLAGS "-O3 -msse2 -msse3")

FILE(GLOB srcs *.cpp)
source_group("Source Files" FILES ${srcs} )

add_executable(ParticleFilter 
               ${srcs}
)

target_link_libraries(ParticleFilter
                      ${OpenCV_LIBS})

