#ifndef CFSM_TRANSITION_TABLE_HPP
#define CFSM_TRANSITION_TABLE_HPP

#include <tuple>
#include <optional>

namespace Fsm
{
  template <typename FsmT, typename StateT, typename... Transitions>
  class TransitionTable
  {
    public:
      template <typename EventT>
      static std::optional<StateT> makeTransition(FsmT &fsm, const StateT currentState, const EventT &event)
      {
        static constexpr std::tuple<Transitions...> transitionsTuple{Transitions()...};
        return getNextState(fsm, transitionsTuple, currentState, event);
      }

    private:
      template <std::size_t I = 0, typename EventT, typename... Ts>
      static std::optional<StateT> getNextState(FsmT &fsm, std::tuple<Ts...> tup, const StateT &currentState, const EventT &event)
      {
        if constexpr (I == sizeof...(Ts)) return {};
        else
        {
          typedef typename std::tuple_element<I, decltype(tup)>::type TransitionType;
          if (TransitionType::stateFrom == currentState 
              && TransitionType::EventType::id() == EventT::id())
          {
            (fsm.*TransitionType::action)(static_cast<const typename TransitionType::EventType&>(static_cast<const EventBase&>(event)));
            return TransitionType::stateTo;
          }
          else
            return getNextState<I + 1>(fsm, tup, currentState, event);
        }
      }
    public:
      static constexpr std::size_t tableSize_ = sizeof...(Transitions);
  };
}

#endif // CFSM_TRANSITION_TABLE_HPP