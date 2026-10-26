
file(GLOB SOURCES CONFIGURE_DEPENDS src/**.cpp)
add_executable(abgabe4 ${SOURCES})
target_compile_options(abgabe4 PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_include_directories(abgabe4 PUBLIC include)