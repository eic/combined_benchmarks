cmake_minimum_required(VERSION 3.16)

project(combined_benchmarks VERSION 0.0.0)

# Make C++17 a default
if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
endif()

# Enable -fPIC for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Install to the top directory by default
if( ${CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT} )
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH "Install in top directory by default" FORCE)
endif()

# Add CMake additional functionality:
include(cmake/print_functions.cmake)                        # Helpers to print fancy headers, file names, etc
include(cmake/print_subdirectory_tree.cmake)                # Prints processed subdirectories
list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)   # Find Find<Modules>.cmake


# ------------------------------------------------------------------
print_grand_header("    B U I L D   E I C R E C O N   P A R T S    ")
# ------------------------------------------------------------------



# Print what we had built
print_header("CMake processed subdirectories:")
print_subdirectory_tree()
message(STATUS "\n-------------------------------")

add_executable(track_fitting_rec_single_tracks
        executables/track_fitting_rec_single_tracks.cc
        reconstruction_benchmarks/benchmarks/track_fitting/scripts/rec_single_tracks.cxx
        )

# include logging by default
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(EDM4HEP REQUIRED)
find_package(EDM4EIC REQUIRED)
find_package(podio REQUIRED)
find_package(DD4hep REQUIRED)
set(fmt_INCLUDE_DIR ${fmt_DIR}/../../../include)

# include ROOT by default
find_package(ROOT REQUIRED)

# Define plugin
target_include_directories(track_fitting_rec_single_tracks
        SYSTEM PUBLIC
            ${podio_INCLUDE_DIR}
            ${EDM4HEP_INCLUDE_DIR}
            ${EDM4EIC_INCLUDE_DIR}
            ${ROOT_INCLUDE_DIRS}
            ${fmt_INCLUDE_DIR}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/executables
            ${CMAKE_SOURCE_DIR}/common_bench/include
        )

message(STATUS "{ROOT_LIBRARIES} ${ROOT_LIBRARIES}")

#set_target_properties(track_fitting_rec_single_tracks PROPERTIES PREFIX "" OUTPUT_NAME "${_name}" SUFFIX ".so")
target_link_libraries(track_fitting_rec_single_tracks spdlog::spdlog EDM4HEP::edm4hep DD4hep::DDCore EDM4EIC::edm4eic ROOT::Core ${ROOT_LIBRARIES})

# Install plugin
install(TARGETS track_fitting_rec_single_tracks)

# Install all cmake helpers
#include(CMakePackageConfigHelpers)
#configure_package_config_file(cmake/EICreconConfig.cmake.in cmake/EICreconConfig.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/EICrecon)
#install(FILES ${CMAKE_BINARY_DIR}/cmake/EICreconConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/EICrecon)  # why is this needed?
#file(GLOB EICRECON_CMAKE_FILES cmake/*.cmake)
#install(FILES ${EICRECON_CMAKE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/EICrecon)

