cmake_minimum_required (VERSION 3.18)

project (
  cfsm-generator
	VERSION 0.1 
  DESCRIPTION "Compile-time FSM generator"
	LANGUAGES C CXX ASM)

set(CMAKE_CONFIG_DIR "${CMAKE_SOURCE_DIR}/cmake")

add_library(cfsm-generator INTERFACE)
target_compile_features(cfsm-generator INTERFACE cxx_std_17)
target_include_directories(cfsm-generator INTERFACE
  include
)
target_sources(cfsm-generator
  INTERFACE
    "FsmGenerator.hpp"
    "Transition.hpp"
    "TransitionTable.hpp"
    "Event.hpp"
)

add_subdirectory(examples)