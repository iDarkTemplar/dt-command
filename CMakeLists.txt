cmake_minimum_required( VERSION 3.16.0 )

project(dt-command
	VERSION 2.0.0
	LANGUAGES C)

include(CMakePackageConfigHelpers)

# installation directory configuration
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)")
set(EXEC_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH "Installation prefix for executables and object code libraries" FORCE)
set(BIN_INSTALL_DIR ${EXEC_INSTALL_PREFIX}/bin CACHE PATH "Installation prefix for user executables" FORCE)
set(SBIN_INSTALL_DIR ${EXEC_INSTALL_PREFIX}/sbin CACHE PATH "Installation prefix for user executables" FORCE)
set(LIB_INSTALL_DIR ${EXEC_INSTALL_PREFIX}/lib${LIB_SUFFIX} CACHE PATH  "Installation prefix for object code libraries" FORCE)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Installation prefix for C header files" FORCE)
set(DATA_PREFIX "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "Prefix prepended to data install directories" FORCE)
set(CMAKEPACKAGE_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/DtCommand" CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where ${PROJECT_NAME}Config.cmake is installed")

option(ENABLE_LIBVERSION "enable libraries versioning" ON)

message(STATUS "System: ${CMAKE_SYSTEM_NAME}" )

# don't USE -O3 with GCC, it causes less precise calculations
if (CMAKE_COMPILER_IS_GNUCC)
	set (CMAKE_C_FLAGS_RELEASE "-O2 -pipe -march=native -Wall -Wextra -Wno-unused-result -DNDEBUG")
	set (CMAKE_C_FLAGS_DEBUG "-O0 -pipe -march=native -Wall -Wextra -Wno-unused-result -g -ggdb")
endif (CMAKE_COMPILER_IS_GNUCC)

# clang compiler options
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	set (CLANG_WARNINGS "-Weverything -Wno-missing-prototypes -Wno-padded -Wno-sign-conversion -Wno-conversion -Wno-disabled-macro-expansion -Wno-cast-align" )
	set (CMAKE_C_FLAGS_RELEASE "-O3 -pipe ${CLANG_WARNINGS} -DNDEBUG")
	set (CMAKE_C_FLAGS_DEBUG "-O0 -pipe ${CLANG_WARNINGS} -g -ggdb")
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set ( DT_CMD_LIBRARY_SOURCES dt-command.c )
set ( DT_CMD_LIBRARY_HEADERS dt-command.h )

add_library( dt-command SHARED ${DT_CMD_LIBRARY_SOURCES} ${DT_CMD_LIBRARY_HEADERS} )
if (ENABLE_LIBVERSION)
	set_target_properties( dt-command PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} )
endif (ENABLE_LIBVERSION)
target_link_libraries( dt-command )

ENABLE_TESTING()

set (TEST_SOURCES_commands tests/commands_test.c tests/dt_tests.h )
set (TEST_LIBS_commands dt-command )

set (ALL_TESTS commands)

foreach (CURRENT_TEST ${ALL_TESTS})
	add_executable( ${CURRENT_TEST}_test ${TEST_SOURCES_${CURRENT_TEST}})
	target_link_libraries( ${CURRENT_TEST}_test ${TEST_LIBS_${CURRENT_TEST}} )
	add_test( ${CURRENT_TEST}_test ${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_TEST}_test )
endforeach (CURRENT_TEST)

# installation config
install(TARGETS dt-command EXPORT DtCommandTargets LIBRARY DESTINATION ${LIB_INSTALL_DIR})
install(FILES "dt-command.h" DESTINATION "${INCLUDE_INSTALL_DIR}")
install(EXPORT DtCommandTargets DESTINATION ${CMAKEPACKAGE_INSTALL_DIR})
set(EXPORT_TARGETS dt-command CACHE INTERNAL "export targets")

configure_package_config_file(cmake/DtCommandConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/DtCommandConfig.cmake
	INSTALL_DESTINATION ${CMAKEPACKAGE_INSTALL_DIR}
	PATH_VARS INCLUDE_INSTALL_DIR)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/DtCommandConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DtCommandConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/DtCommandConfigVersion.cmake
	DESTINATION ${CMAKEPACKAGE_INSTALL_DIR} )
