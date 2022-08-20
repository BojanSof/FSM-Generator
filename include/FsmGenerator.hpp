#ifndef CFSM_GEN_HPP
#define CFSM_GEN_HPP

#include "Event.hpp"

#include "internal/TransitionTable.hpp"
#include "internal/Transition.hpp"

namespace Fsm
{
  template<typename FsmT>
  struct States
  {
    enum class State
    {
      InvalidState
    };
  };

  template<typename FsmT>
  class FsmGenerator
  {
    protected:
      using StateT = typename States<FsmT>::State;

      FsmGenerator(const StateT& initialState)
        : currentState_(initialState)
      {
      }
      
      template <typename EventT>
      void processEvent(const EventT& e)
      {
        typedef typename FsmT::Table Table;
        auto newState = Table::makeTransition(static_cast<FsmT&>(*this), currentState_, e);
        currentState_ = (newState.has_value()) ? newState.value() : StateT::InvalidState;
      }
      
      void setState(const StateT& state)
      {
        currentState_ = state;
      }

      StateT getCurrentState() const
      {
        return currentState_;
      }
    template<
      typename EventT
      , StateT StateFrom
      , StateT StateTo
      , void (FsmT::*Action)(const EventT& e) >
    struct Transition
      : Fsm::Transition<FsmT, StateT, EventT, StateFrom, StateTo, Action>
    {
    };

    template<typename... Transitions>
    class TransitionTable
      : public Fsm::TransitionTable<FsmT, StateT, Transitions...>
    {
    };

    private:
      StateT currentState_;
  };
}

#endif //CFSM_GEN_HPP