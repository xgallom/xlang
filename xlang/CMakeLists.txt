project(xlang CXX)

set(files
        src/main.cpp)

add_executable(xlang ${files})

target_link_libraries(xlang PRIVATE xlanger)

install(TARGETS xlang)
