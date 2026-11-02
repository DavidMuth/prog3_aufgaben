
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)
add_executable(abgabe5 ${SOURCES})

target_include_directories(abgabe5 PUBLIC include)