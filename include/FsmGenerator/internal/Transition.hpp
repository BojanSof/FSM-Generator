#ifndef FSM_TRANSITION_HPP
#define FSM_TRANSITION_HPP

namespace Fsm
{
  /**
   * @brief Structure representing single
   * row of the transitions look-up table.
   * 
   * @tparam T Type of the state machine
   * @tparam StateT State type
   * @tparam EventT Event type
   * @tparam StateFrom Current state of the FSM
   * @tparam StateTo The state to transition to
   * @tparam (*Action)(const EventT& e) Action to
   * take during the transition
   */
  template <
    typename T
    , typename StateT
    , typename EventT
    , StateT StateFrom
    , StateT StateTo
    , void (T::*Action)(const EventT& e) >
  struct Transition
  {
    using EventType = EventT;
    using StateType = StateT;
    static constexpr StateT stateFrom = StateFrom;
    static constexpr StateT stateTo = StateTo;
    static constexpr auto action = Action;
  };
}

#endif //FSM_TRANSITION_HPP