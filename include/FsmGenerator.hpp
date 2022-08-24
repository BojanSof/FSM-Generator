#ifndef CFSM_GEN_HPP
#define CFSM_GEN_HPP

#include "Event.hpp"
#include "States.hpp"

#include "internal/TransitionTable.hpp"
#include "internal/Transition.hpp"

namespace Fsm
{
  /**
   * @brief Compile-time FSM generator
   * 
   * @tparam FsmT User FSM type
   */
  template<typename FsmT>
  class FsmGenerator
  {
    protected:
      using StateT = typename States<FsmT>::State;

      /**
       * @brief Construct a new Fsm Generator object
       * 
       * @param initialState The initial state for the FSM
       */
      FsmGenerator(const StateT& initialState)
        : currentState_(initialState)
      {
      }
      
      /**
       * @brief Process event and change the
       * state of the FSM
       * 
       * @tparam EventT The type of the event
       * @param e The event
       */
      template <typename EventT>
      void processEvent(const EventT& e)
      {
        using Table = typename FsmT::Table;
        auto newState = Table::makeTransition(static_cast<FsmT&>(*this), currentState_, e);
        currentState_ = (newState.has_value()) ? newState.value() : StateT::InvalidState;
      }
      
      /**
       * @brief Set the current FSM state
       * 
       * @param state The state to be set
       */
      void setState(const StateT& state)
      {
        currentState_ = state;
      }

      /**
       * @brief Get the current FSM state
       * 
       * @return StateT The current state
       */
      StateT getCurrentState() const
      {
        return currentState_;
      }
    
    /**
     * @brief Single row of the transition table
     * 
     * @tparam EventT The type of the event that needs to occur
     * for the FSM to change state
     * @tparam StateFrom The curent state the FSM needs to be
     * @tparam StateTo The state to which the FSM should transition
     * @tparam (FsmT::*Action)(const EventT& e) Pointer to member function
     * that needs to be called during the transition. It gets the event
     * for the transition as parameter.
     */
    template<
      typename EventT
      , StateT StateFrom
      , StateT StateTo
      , void (FsmT::*Action)(const EventT& e) >
    struct Transition
      : Fsm::Transition<FsmT, StateT, EventT, StateFrom, StateTo, Action>
    {
    };

    /**
     * @brief Table containing the transitions of the FSM
     * 
     * @tparam Transitions List of transitions
     */
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