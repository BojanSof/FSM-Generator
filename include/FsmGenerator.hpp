#ifndef CFSM_GEN_HPP
#define CFSM_GEN_HPP

namespace Fsm
{
  template<typename Fsm>
  class FsmGenerator
  {
    public:
      template <typename EventT>
      void processEvent(const EventT& e)
      {
        typedef typename Fsm::TransitionTable TransitionTable;
        currentState_ = TransitionTable::makeTransition(currentState_, e);
      }
    private:
      typedef typename Fsm::StateT StateType;
      StateType currentState_;
  };
}

#endif //CFSM_GEN_HPP