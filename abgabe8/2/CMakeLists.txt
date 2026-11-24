
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe8-2 ${SOURCES})

target_include_directories(aufgabe8-2 PUBLIC include)
