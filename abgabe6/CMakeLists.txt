
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)
add_executable(abgabe6 ${SOURCES})

target_include_directories(abgabe6 PUBLIC include)