#ifndef CFSM_GEN_HPP
#define CFSM_GEN_HPP

#include "Event.hpp"
#include "Transition.hpp"
#include "TransitionTable.hpp"

namespace Fsm
{
  template<typename Fsm>
  class FsmGenerator
  {
    public:
      template <typename EventT>
      void processEvent(const EventT& e)
      {
        typedef typename Fsm::Table Table;
        currentState_ = Table::makeTransition(currentState_, e);
      }
      
      typedef typename Fsm::State StateType;
      void setState(const StateType& state)
      {
        currentState_ = state;
      }
    private:
      StateType currentState_;
  };
}

#endif //CFSM_GEN_HPP