cmake_minimum_required(VERSION 2.8)

project(RUSH_HOUR)

set(RUSH_HOUR_VERSION_MAJOR "1")
set(RUSH_HOUR_VERSION_MINOR "1")
set(RUSH_HOUR_VERSION_PATCH "2")
set(RUSH_HOUR_VERSION "${RUSH_HOUR_VERSION_MAJOR}.${RUSH_HOUR_VERSION_MINOR}.${RUSH_HOUR_VERSION_PATCH}")
set(CMAKE_INSTALL_PREFIX ../build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(NAME_ARCHIVE "A2_ARNEAU_BOUTET_GHIBERT.tar")

#code coverage
#set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
#code coverage

option(enable_debug "debug option" on)
ENABLE_TESTING()

if( enable_debug )
  find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
  set(CMAKE_C_FLAGS "-std=c99 -g -O0 -fprofile-arcs -ftest-coverage -Wall")
  set(CMAKE_LD_FLAGS " -fprofile-arcs -ftest-coverage")
  include(CodeCoverage)
  include(Dart)
  setup_target_for_coverage(${PROJECT_NAME}_coverage ctest coverage)
else ( enable_debug )
  set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")
endif( enable_debug )

include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_image)
include_directories(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(src)
add_subdirectory(src/test)
add_subdirectory(config)
add_subdirectory(img)

add_test(test_game_ar bin/test/test_game_ar "TEST 1")
add_test(test_game_rh bin/test/test_game1 "TEST 2")
add_test(test_piece_rh bin/test/test_piece1 "TEST 3")

if (WIN32)
add_custom_target(tar
	COMMAND	mkdir ..\\..\\Projet
	COMMAND 7z a -ttar ../../Projet/${NAME_ARCHIVE} ./ -mx0 -xr!.git 
	COMMAND 7z a ../${NAME_ARCHIVE}.gz ../../Projet/${NAME_ARCHIVE}
	COMMAND rmdir /s /q ..\\..\\Projet)
else (WIN32)
add_custom_target(tar
	#COMMAND rm ../Projet-Rush-Hour/${NAME_ARCHIVE}.gz
	COMMAND mkdir ../../Projet
	COMMAND tar --exclude="build" --exclude=".git" --exclude="*.tar.gz" -zcvf ../../Projet/${NAME_ARCHIVE}.gz ../
        COMMAND mv ../../Projet/${NAME_ARCHIVE}.gz ../
        COMMAND rmdir ../../Projet)
endif(WIN32)
