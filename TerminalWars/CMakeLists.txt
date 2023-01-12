# CMakeList.txt : CMake project for TerminalWars, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (TerminalWars "TerminalWars.cpp" "TerminalWars.h" "Village.cpp" "Game.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TerminalWars PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
