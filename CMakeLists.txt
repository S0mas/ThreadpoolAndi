cmake_minimum_required (VERSION 3.8)

project ("QLgrep")

# Add source to this project's executable.
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")
add_executable (QLgrep ${SOURCES} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET QLgrep PROPERTY CXX_STANDARD 20)
endif()
