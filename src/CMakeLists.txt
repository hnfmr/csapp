add_library(csapp cs.h cs.c)

add_executable(ch2 ch2.c)
target_link_libraries(ch2 csapp)

