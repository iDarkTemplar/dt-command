# - Try to find DtCommand library
# Once done this will define
#  DTCOMMAND_FOUND - System has DtCommand
#  DTCOMMAND_INCLUDE_DIRS - The DtCommand include directories
#  DTCOMMAND_LIBRARIES - The libraries needed to use DtCommand

find_path(DTCOMMAND_INCLUDE_DIR dt-command.h)

find_library(DTCOMMAND_LIBRARY NAMES dt-command libdt-command)

set(DTCOMMAND_LIBRARIES ${DTCOMMAND_LIBRARY})
set(DTCOMMAND_INCLUDE_DIRS ${DTCOMMAND_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set DTCOMMAND_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(DtCommand DEFAULT_MSG
                                  DTCOMMAND_LIBRARY DTCOMMAND_INCLUDE_DIR)

mark_as_advanced(DTCOMMAND_INCLUDE_DIR DTCOMMAND_LIBRARY)
