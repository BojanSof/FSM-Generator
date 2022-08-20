cmake_minimum_required (VERSION 3.18)

project (
  cfsm-generator
	VERSION 0.1 
  DESCRIPTION "Compile-time FSM generator"
	LANGUAGES C CXX ASM)

option(BUILD_EXAMPLES "Build examples" ON)

add_library(cfsm-generator INTERFACE)
target_compile_features(cfsm-generator INTERFACE cxx_std_17)
target_include_directories(cfsm-generator INTERFACE
  include
)
target_sources(cfsm-generator
  INTERFACE
    "include/FsmGenerator.hpp"
    "include/Event.hpp"
    "include/States.hpp"
    "include/internal/TransitionTable.hpp"
    "include/internal/Transition.hpp"
    "include/internal/EventBase.hpp"
)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)