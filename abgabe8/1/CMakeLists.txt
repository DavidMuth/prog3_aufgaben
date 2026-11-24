
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe8-1 ${SOURCES})

target_include_directories(aufgabe8-1 PUBLIC include)
