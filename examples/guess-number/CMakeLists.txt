cmake_minimum_required (VERSION 3.18)

add_executable(guess-number)
target_compile_options(guess-number PUBLIC -Wall -Wextra -pedantic)
target_sources(guess-number
  PRIVATE
    game.cpp
)
target_link_libraries(guess-number PRIVATE cfsm-generator)