cmake_minimum_required (VERSION 3.18)

project (
  cfsm-generator
	VERSION 0.1 
  DESCRIPTION "Compile-time FSM generator"
	LANGUAGES C CXX ASM)

option(FSM_GENERATOR_BUILD_EXAMPLES "Build examples" ON)

add_library(cfsm-generator INTERFACE)
target_compile_features(cfsm-generator INTERFACE cxx_std_17)
target_include_directories(cfsm-generator INTERFACE
  include
)
target_sources(cfsm-generator
  INTERFACE
    "include/FsmGenerator/FsmGenerator.hpp"
    "include/FsmGenerator/Event.hpp"
    "include/FsmGenerator/States.hpp"
    "include/FsmGenerator/internal/TransitionTable.hpp"
    "include/FsmGenerator/internal/Transition.hpp"
)

if(FSM_GENERATOR_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(FSM_GENERATOR_BUILD_EXAMPLES)
