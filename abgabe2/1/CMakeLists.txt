
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe2-1 ${SOURCES})

target_include_directories(aufgabe2-1 PUBLIC include)
