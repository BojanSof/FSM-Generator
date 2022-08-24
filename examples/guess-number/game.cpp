#include <iostream>
#include <random>

#include <FsmGenerator.hpp>

using namespace Fsm;

class GuessNumberFsm;

template<>
struct Fsm::States<GuessNumberFsm>
{
  enum class State
  {
    InvalidState,
    WaitForInput,
    CheckInput,
    End
  };
};

class GuessNumberFsm
  : public FsmGenerator<GuessNumberFsm>
{
  public:
    using State = typename States<GuessNumberFsm>::State;

    GuessNumberFsm() : FsmGenerator(State::CheckInput), running(true)
    {
      std::mt19937 rng(std::random_device{}());
      auto dist = std::uniform_int_distribution<unsigned int>(1, 100);
      num = dist(rng);
    }

    void run()
    {
      std::cout << "Welcome to Guess the number." << std::endl;
      while(running)
      {
        processEvent(RetryEvent{});
        InputEvent in;
        in.number = input;
        processEvent(in);
        if(!running) processEvent(EndEvent{});
      }
    }
  private:
    unsigned int num, input;
    bool running;
  private:
    friend class FsmGenerator<GuessNumberFsm>;

    struct InputEvent : public Event
    {
      unsigned int number;
    };
    struct RetryEvent : public Event {};
    struct EndEvent : public Event {};

    void doWaitForInputCheckInput(const InputEvent& e)
    {
      if(e.number != num)
      {
        std::cout << ((e.number < num) ? "Low, enter higher number." : "High, enter lower number.") << std::endl;
      }
      else
      {
        running = false;
      }
    }

    void doCheckInputWaitForInput(const RetryEvent& e)
    {
      (void)e;
      std::cout << "Enter number between 1 and 100: ";
      std::cin >> input;
    }

    void doCheckInputStop(const EndEvent& e)
    {
      (void)e;
      std::cout << "Congrats! Bye." << std::endl;
    }

    using Table = TransitionTable<
      Transition<InputEvent, State::WaitForInput, State::CheckInput, &GuessNumberFsm::doWaitForInputCheckInput>
      , Transition<RetryEvent, State::CheckInput, State::WaitForInput, &GuessNumberFsm::doCheckInputWaitForInput>
      , Transition<EndEvent, State::CheckInput, State::End, &GuessNumberFsm::doCheckInputStop>
    >;
};

int main()
{
  GuessNumberFsm guessNumber;
  guessNumber.run();
}