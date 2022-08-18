#include "FsmGenerator.hpp"
#include <iostream>
#include <random>

using namespace Fsm;

class GuessNumberFsm
  : public FsmGenerator<GuessNumberFsm>
{
  public:
    bool running = true;
    GuessNumberFsm()
    {
      std::mt19937 rng(std::random_device{}());
      auto dist = std::uniform_int_distribution<unsigned int>(1, 100);
      num = dist(rng);
    }

    void run()
    {
      std::cout << "Welcome to Guess the number. Enter number between 1 and 100. You have 10 tries" << std::endl;
      setState(State::CheckInput);
      processEvent(RetryEvent{});
    }
  private:
    unsigned int num;
  private:
    friend class FsmGenerator<GuessNumberFsm>;
    enum class State
    {
      WaitForInput,
      CheckInput,
      End
    };

    struct InputEvent
      : public Event<InputEvent>
    {
      unsigned int number;
    };

    struct RetryEvent
      : public Event<RetryEvent>
    {};

    struct EndEvent
      : public Event<EndEvent>
    {
    };

    void doWaitForInputCheckInput(const InputEvent& e)
    {
      if(e.number == num) processEvent(EndEvent{});
      else processEvent(RetryEvent{});
    }

    void doCheckInputWaitForInput(const RetryEvent& e)
    {
      InputEvent in;
      std::cout << "Enter number between 1 and 100: ";
      std::cin >> in.number;
      processEvent(in);
    }

    void doCheckInputStop(const EndEvent& e)
    {
      std::cout << "Congrats! Bye." << std::endl;
    }

    typedef TransitionTable<
      State
      , Transition<State, InputEvent, State::WaitForInput, State::CheckInput, doWaitForInputCheckInput>
      , Transition<State, RetryEvent, State::CheckInput, State::WaitForInput, doCheckInputWaitForInput>
      , Transition<State, EndEvent, State::CheckInput, State::End, doCheckInputStop>
    > Table;
};

int main()
{
  GuessNumberFsm guessNumber;
  guessNumber.run();
}