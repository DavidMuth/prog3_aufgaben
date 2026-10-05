
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe1-2 ${SOURCES})

target_include_directories(aufgabe1-2 PUBLIC include)
