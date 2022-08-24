#ifndef CFSM_EVENT_BASE_HPP
#define CFSM_EVENT_BASE_HPP

#include <cstddef>

namespace Fsm
{
  /**
   * Base class for the events aiming to
   * eliminate the need of runtime polymorphism
   * to check event type. This is achived by up-casting
   * to this type and then down-casting to the specific
   * event type.
   * 
   */
  struct EventBase
  {
  };
}

#endif //CFSM_EVENT_BASE_HPP