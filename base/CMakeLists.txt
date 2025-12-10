file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(postfix ${srcs} ${hdrs})