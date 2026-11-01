
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(abgabe4 ${SOURCES})

target_include_directories(abgabe4 PUBLIC include)
