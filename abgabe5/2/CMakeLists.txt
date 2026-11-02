
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe5-2 ${SOURCES})

target_include_directories(aufgabe5-2 PUBLIC include)
