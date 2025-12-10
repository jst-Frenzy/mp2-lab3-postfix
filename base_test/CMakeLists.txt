set(target postfix_test)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../base"
    "${CMAKE_CURRENT_SOURCE_DIR}/../gtest"
)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../base/TPostfix.cpp" "../base/TStack.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)