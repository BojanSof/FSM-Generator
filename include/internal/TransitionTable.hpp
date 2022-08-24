#ifndef CFSM_TRANSITION_TABLE_HPP
#define CFSM_TRANSITION_TABLE_HPP

#include <tuple>
#include <optional>
#include <type_traits>

#include "EventBase.hpp"

namespace Fsm
{
  /**
   * @brief The transition table that contains and implements
   * the logic of transitioning between the states of the FSM
   * 
   * @tparam FsmT The user FSM type
   * @tparam StateT The type used for storing the states
   * @tparam Transitions List of transitions for the FSM
   */
  template <typename FsmT, typename StateT, typename... Transitions>
  class TransitionTable
  {
    public:
      /**
       * @brief Make the transition for the FSM based on the current
       * state and the occured event
       * 
       * @tparam EventT The type of the event
       * @param fsm Reference to the FSM object
       * @param currentState The current state
       * @param event The event that occured
       * @return std::optional<StateT> If the transition is possible returns
       * the new state, otherwise the output has no value
       */
      template <typename EventT>
      static std::optional<StateT> makeTransition(FsmT &fsm, const StateT currentState, const EventT &event)
      {
        static constexpr std::tuple<Transitions...> transitionsTuple{Transitions()...};
        return getNextState(fsm, transitionsTuple, currentState, event);
      }

    private:
      /**
       * @brief Helper function that iterates through the tuple
       * elements and searches for the transition that contains
       * the current state and event. It also calls the action
       * function for the found transition, if it exists.
       * 
       * @param fsm Reference to the FSM object
       * @param tup Tuple that contains the transitions
       * @param currentState The current state of the FSM
       * @param event The event that occured
       * @return  If the transition is possible returns
       * the new state, otherwise the output has no value
       */
      template <std::size_t I = 0, typename EventT, typename... Ts>
      static std::optional<StateT> getNextState(FsmT &fsm, std::tuple<Ts...> tup, const StateT &currentState, const EventT &event)
      {
        if constexpr (I == sizeof...(Ts)) return {};
        else
        {
          using TransitionType = typename std::tuple_element_t<I, decltype(tup)>;
          if (TransitionType::stateFrom == currentState 
              && std::is_same_v<typename TransitionType::EventType, EventT>)
          {
            (fsm.*TransitionType::action)(static_cast<const typename TransitionType::EventType&>(static_cast<const EventBase&>(event)));
            return TransitionType::stateTo;
          }
          else
            return getNextState<I + 1>(fsm, tup, currentState, event);
        }
      }
    public:
      static constexpr std::size_t tableSize_ = sizeof...(Transitions);  ///< the number of transitions in the table
  };
}

#endif // CFSM_TRANSITION_TABLE_HPP