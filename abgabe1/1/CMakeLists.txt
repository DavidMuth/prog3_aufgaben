
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)

add_executable(bin ${SOURCES})

target_include_directories(bin PUBLIC include)
