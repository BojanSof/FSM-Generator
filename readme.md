# Compile-time FSM generator

The goal of this project is to provide easy to use C++ interface that generates Finite State Machine (FSM) code in compile-time and saving the need of rewriting boiler-plate code for projects that need multiple FSMs.

## Features

- Compile-time FSM generator
- Header-only library
- Does not use dynamic allocation
- Does not use run-time polymorphism, making it suitable for bare-metal platforms

## Requirements

- C++17 compiler
- CMake 3.18 or greater

## How to use

The FSM is basically represented as a table of transitions.
Each row of the transition table contains information about the states from and to that consist the transition, the event that needs to occur to make the transition and action function that needs to be called during the transition.
The event contains data that are specific to the transition.

To define new FSM, first define its states, by specializing the template class `Fsm::States`:
```
class MyFsm; //< forward declaration
template<>
Fsm::States<MyFsm>
{
  enum class State
  {
    InvalidState,
    Initial,
    State1,
    State2,
    State3,
    ...
  };
};
```
Please ensure that the `State` enum class contains `InvalidState` element.
Then define the FSM by inheriting from `Fsm::FsmGenerator`.
Few things are required:
1. Call the base class constructor with the initial state of the FSM
2. Define all the events for the transitions, holding event-specific data
3. Define the action functions for the transitions.
These functions should be with the following signature:
`void action(const EventType& e)`.
4. Declare the type of the transition table.
Ensure that the name of the type of the transition table is `Table`.
5. To process event `e`, call `processEvent(e)`.
```
class MyFsm : public Fsm::FsmGenerator<MyFsm>
{
  friend class FsmGenerator<GuessNumberFsm>;
  using State = typename States<GuessNumberFsm>::State;
  public:
    MyFsm() : Fsm::FsmGenerator(State::Initial)
    {
      ...
    }
    // do something to generate events and process them in the FSM
    void run()
    {
      Event1 e1;
      processEvent(e1);
      ...
      Event2 e2;
      processEvent(e2);
    }
  
  private:
    // events
    struct Event1 : public Fsm::Event<Event1>
    {
      // Event1 specific data
      ...
    };
    struct Event2 : public Fsm::Event<Event2>
    {
      // Event2 specific data
      ...
    };

    // actions
    void doInitialToState1(const Event1& e)
    {
      ...
    }

    void doState1ToState2(const Event2& e)
    {
      ...
    }

    // transition table
    using Table = TransitionTable<
      Transition<Event1, State::Initial, State::State1, &MyFsm::doInitialToState1>
      , Transition<Event2, State::State1, State::State2, &MyFsm::doState1ToState2>
    >;
};
```

## Examples

All the examples are stored in the `examples` folder.

Currently, there is a single example for the game 'Guess the number', found under `examples/guess-number`.
More examples will be added, especially ones used on bare metal platforms for communication drivers for protocols like I2C, SPI, etc.

To build the examples, ensure that the CMake cache variable `BUILD_EXAMPLES` is set to `ON`.

## Resources

1. [Boost example of compile-time FSM generator](https://www.boost.org/doc/libs/1_31_0/libs/mpl/doc/paper/html/example.html)
