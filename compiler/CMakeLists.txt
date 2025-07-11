cmake_minimum_required(VERSION 3.13.0)


set(ETH_CMAKE_DIR   "${CMAKE_CURRENT_LIST_DIR}/cmake"   CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${ETH_CMAKE_DIR})

# Set the build type, if none was specified.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
		set(DEFAULT_BUILD_TYPE "RelWithDebInfo")
	else()
		set(DEFAULT_BUILD_TYPE "Release")
	endif()
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel" FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

include(EthToolchains)

# Set cmake_policies
include(EthPolicy)
eth_policy()

# project name and version should be set after cmake_policy CMP0048
set(PROJECT_VERSION "0.78.2")
# OSX target needed in order to support std::visit
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")
project(solidity VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if (IS_BIG_ENDIAN)
	message(FATAL_ERROR "${PROJECT_NAME} currently does not support big endian systems.")
endif()

option(SOLC_LINK_STATIC "Link solc executable statically on supported platforms" OFF)
option(WITH_TESTS "Run solc tests" OFF)
option(SOLC_STATIC_STDLIBS "Link solc against static versions of libgcc and libstdc++ on supported platforms" OFF)
option(STRICT_Z3_VERSION "Use the latest version of Z3" ON)
option(PEDANTIC "Enable extra warnings and pedantic build flags. Treat all warnings as errors." ON)
option(PROFILE_OPTIMIZER_STEPS "Output performance metrics for the optimiser steps." OFF)

# Setup cccache.
include(EthCcache)

# Let's find our dependencies
include(EthDependencies)
include(fmtlib)
include(jsoncpp)
include(range-v3)
include_directories(SYSTEM ${JSONCPP_INCLUDE_DIR})

find_package(Threads)

if(NOT PEDANTIC)
  message(WARNING "-- Pedantic build flags turned off. Warnings will not make compilation fail. This is NOT recommended in development builds.")
endif()

if (PROFILE_OPTIMIZER_STEPS)
    add_definitions(-DPROFILE_OPTIMIZER_STEPS)
endif()

# Figure out what compiler and system are we using
include(EthCompilerSettings)

# Include utils
include(EthUtils)

# Create license.h from LICENSE.txt and template
# Converting to char array is required due to MSVC's string size limit.
file(READ ${PROJECT_SOURCE_DIR}/LICENSE.txt LICENSE_TEXT HEX)
string(REGEX MATCHALL ".." LICENSE_TEXT "${LICENSE_TEXT}")
string(REGEX REPLACE ";" ",\n\t0x" LICENSE_TEXT "${LICENSE_TEXT}")
set(LICENSE_TEXT "0x${LICENSE_TEXT}")

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/license.h.in" include/license.h)

include(EthOptions)
configure_project(TESTS)

add_subdirectory(libsolutil)
add_subdirectory(liblangutil)
add_subdirectory(libsolidity)
add_subdirectory(libsolc)
add_subdirectory(libstdlib)
if (WITH_TESTS)
	add_subdirectory(test2)
endif()

if (NOT EMSCRIPTEN)
	add_subdirectory(solc)
endif()
