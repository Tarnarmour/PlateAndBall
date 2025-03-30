cmake_minimum_required(VERSION 3.15)

project(PlateAndBall)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


## ***** Fetch Content Stuff *****
# Include FetchContent module
include(FetchContent)

# Fetch SFML
FetchContent_Declare(
  sfml
  URL "https://github.com/SFML/SFML/archive/3.0.0.zip"
)

# Fetch Dear ImGui
FetchContent_Declare(
  imgui
  URL "https://github.com/ocornut/imgui/archive/v1.91.8.zip"
)

# Fetch ImGui-SFML binding
FetchContent_Declare(
  imgui-sfml
  URL "https://github.com/SFML/imgui-sfml/archive/v3.0.zip"
)

# Fetch ImPlot
FetchContent_Declare(
  implot
  URL "https://github.com/epezent/implot/archive/refs/tags/v0.16.zip"
)

# Fetch GLFW for OpenGL
FetchContent_Declare(
	glfw
	URL "https://github.com/glfw/glfw/archive/refs/tags/3.4.zip"
)

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" OFF)
option(SFML_BUILD_EXAMPLES "Build SFML examples" OFF)
option(SFML_BUILD_DOCS "Build SFML documentation" OFF)

FetchContent_MakeAvailable(imgui-sfml)

# ImPlot
FetchContent_MakeAvailable(implot)

add_library(implot STATIC
  ${implot_SOURCE_DIR}/implot.cpp
  ${implot_SOURCE_DIR}/implot_items.cpp)

target_include_directories(implot PUBLIC
  ${implot_SOURCE_DIR}
  ${imgui_SOURCE_DIR}
)

# GLFW
FetchContent_MakeAvailable(glfw)


## ***** Linking ******

# Get all the source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Add executable
add_executable(PlateAndBall PlateAndBall.cpp ${PROJECT_SOURCES} "glad/src/glad.c")

# Link libraries
target_link_libraries(PlateAndBall PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
  ImGui-SFML::ImGui-SFML
  implot
  glfw
)


# Include directories
target_include_directories(PlateAndBall PRIVATE ${imgui_SOURCE_DIR} ${implot_SOURCE_DIR} src glad/include/)


# Suppress specific warnings
if (MSVC)
  target_compile_options(PlateAndBall PRIVATE /wd4267 /wd4244 /wd4996 /wd4305 /wd4018)
endif()

