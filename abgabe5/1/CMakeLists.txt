
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe5-1 ${SOURCES})

target_include_directories(aufgabe5-1 PUBLIC include)
