
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(abgabe7 ${SOURCES})

target_include_directories(abgabe7 PUBLIC include)
