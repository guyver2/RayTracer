cmake_minimum_required (VERSION 2.6)
project (Ray)

set ( CMAKE_CXX_FLAGS "-std=c++11 -fopenmp -O3" )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})



file(GLOB RAY_SRC
     "main.cpp"
     "camera.cpp"
     "plane.cpp"
     "scene.cpp"
     "light.cpp"
)


find_package( OpenCV REQUIRED )

add_executable(Ray ${RAY_SRC})
target_link_libraries (Ray ${OpenCV_LIBS})
