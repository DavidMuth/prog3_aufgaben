
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(abgabe2 ${SOURCES})

target_include_directories(abgabe2 PUBLIC include)
