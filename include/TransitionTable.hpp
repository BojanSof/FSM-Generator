#ifndef CFSM_TRANSITION_TABLE_HPP
#define CFSM_TRANSITION_TABLE_HPP

#include <tuple>
#include <optional>

namespace Fsm
{
  template <typename StateT, typename... Transitions>
  class TransitionTable
  {
    public:
      template <typename EventT>
      static std::optional<StateT> makeTransition(const StateT currentState, const EventT &event)
      {
        static constexpr std::tuple<Transitions...> transitionsTuple{Transitions()...};
        return getNextState(transitionsTuple, currentState, event);
      }

    private:
      template <std::size_t I = 0, typename EventT, typename... Ts>
      static std::optional<StateT> getNextState(std::tuple<Ts...> tup, const StateT &currentState, const EventT &event)
      {
        if constexpr (I == sizeof...(Ts)) return {};
        else
        {
          if (std::tuple_element<I, decltype(tup)>::type::stateFrom == currentState 
              && std::tuple_element<I, decltype(tup)>::type::EventType::id() == EventT::id())
          {
            std::tuple_element<I, decltype(tup)>::type::action(event);
            return std::tuple_element<I, decltype(tup)>::type::stateTo;
          }
          else
            return getNextState<I + 1>(tup, currentState, event);
        }
      }
    public:
      static constexpr std::size_t tableSize_ = sizeof...(Transitions);
  };
}

#endif // CFSM_TRANSITION_TABLE_HPP