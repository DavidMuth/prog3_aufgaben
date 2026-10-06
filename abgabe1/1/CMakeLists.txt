
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe1-1 ${SOURCES})

target_include_directories(aufgabe1-1 PUBLIC include)
