#ifndef CFSM_STATES_HPP
#define CFSM_STATES_HPP

namespace Fsm
{
  /**
   * @brief Base type that contains the 
   * states of the FSM
   * 
   * @tparam FsmT User FSM type
   */
  template<typename FsmT>
  struct States
  {
    enum class State
    {
      InvalidState
    };
  };
}

#endif //CFSM_STATES_HPP