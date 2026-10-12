
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)
add_executable(abgabe2 ${SOURCES})
target_compile_options(abgabe2 PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_include_directories(abgabe2 PUBLIC include)
