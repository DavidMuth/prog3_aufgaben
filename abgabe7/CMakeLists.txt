
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(aufgabe7 ${SOURCES})

target_include_directories(aufgabe7 PUBLIC include)
