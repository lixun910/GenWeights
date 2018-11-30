cmake_minimum_required(VERSION 2.8)

project(SocialWeightsProject)

set(DEP_LIBRARY_PATH ${CMAKE_BINARY_DIR}/INSTALL)
file(MAKE_DIRECTORY ${DEP_LIBRARY_PATH})
file(MAKE_DIRECTORY ${DEP_LIBRARY_PATH}/lib)

include(ExternalProject)

set (ANN_BUILD_CMD)
set (ANN_INSTALL_CMD)
if ( APPLE )
    set ( ANN_BUILD_CMD make macosx-g++ )
    set ( ANN_INSTALL_CMD cp lib/libANN.a ${DEP_LIBRARY_PATH}/lib/libANN.a && cp -rf include ${DEP_LIBRARY_PATH}/include )
endif()
if ( UNIX )
    set ( ANN_BUILD_CMD make linux-g++ )
endif()
if ( WIN32 )
    set ( ANN_BUILD_CMD make macosx-g++ )
endif()

ExternalProject_Add(project_ANN
        GIT_REPOSITORY "https://github.com/lixun910/ann.git"
        GIT_TAG "master"
        BUILD_IN_SOURCE 1
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND make macosx-g++
        INSTALL_COMMAND ${ANN_INSTALL_CMD}
        INSTALL_DIR ${CMAKE_BINARY_DIR}/INSTALL
        )


ExternalProject_Get_Property(project_ANN install_dir)

message(STATUS "Install ANN includes: ${install_dir}/lib/libANN.a")


add_library(ANN STATIC IMPORTED)

set_property(TARGET ANN PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libANN.a)


add_dependencies(ANN project_ANN)

add_executable(SocialWeightsProject src/Test.cpp src/DistUtils.cpp)

include_directories(${install_dir}/include)

target_link_libraries(SocialWeightsProject ANN)