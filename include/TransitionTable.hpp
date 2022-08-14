#ifndef CFSM_TRANSITION_TABLE_HPP
#define CFSM_TRANSITION_TABLE_HPP

namespace Fsm
{
  template <typename StateT, typename... Transitions>
  class TransitionTable
  {
    public:
      template <typename EventT>
      static StateT makeTransition(const StateT &currentState, const EventT& event)
      {
        // find the transition
        // do linear search? on transitions pack
        // variadic templates, fold expressions...
        // call action for the transition type
        // return next state, from the transition type
      }
  };
}

#endif //CFSM_TRANSITION_TABLE_HPP