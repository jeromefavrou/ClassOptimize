cmake_minimum_required(VERSION 3.16)

project(ClassOptimize VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GTKMM
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Executable
add_executable(ClassOptimize
    src/main.cpp
)

# Includes
target_include_directories(ClassOptimize PRIVATE
    include
    ${GTKMM_INCLUDE_DIRS}
)

# Link GTKMM
target_link_libraries(ClassOptimize PRIVATE
    ${GTKMM_LIBRARIES}
)

target_compile_options(ClassOptimize PRIVATE
    ${GTKMM_CFLAGS_OTHER}
)

# --- INSTALLATION ---

# Installer le binaire
install(TARGETS ClassOptimize
        RUNTIME DESTINATION bin)

# Installer les headers
install(DIRECTORY include/ClassOptimize
        DESTINATION include)

# Installer les ressources
install(DIRECTORY resources/
        DESTINATION share/ClassOptimize)
