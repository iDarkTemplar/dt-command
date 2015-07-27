# - Try to find DtCommand library
# Once done this will define
#  DT_CMD_FOUND - System has DtCommand
#  DT_CMD_INCLUDE_DIRS - The DtCommand include directories
#  DT_CMD_LIBRARIES - The libraries needed to use DtCommand

find_path(DT_CMD_INCLUDE_DIR dt-command.h )

find_library(DT_CMD_LIBRARY NAMES dt-command libdt-command )

set(DT_CMD_LIBRARIES ${DT_CMD_LIBRARY} )
set(DT_CMD_INCLUDE_DIRS ${DT_CMD_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set DT_CMD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(DtCommand  DEFAULT_MSG
                                  DT_CMD_LIBRARY DT_CMD_INCLUDE_DIR)

mark_as_advanced(DT_CMD_INCLUDE_DIR DT_CMD_LIBRARY )
