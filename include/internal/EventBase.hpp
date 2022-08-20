#ifndef CFSM_EVENT_BASE_HPP
#define CFSM_EVENT_BASE_HPP

#include <cstddef>

namespace Fsm
{
  /**
   * Base class for the events used for providing
   * the unique ID for each event, with goal of
   * eliminating the need of runtime polymorphism
   * to check event type.
   * 
   */
  struct EventBase
  {
    protected:
      static std::size_t next()
      {
        static std::size_t counter = 0;
        return counter++;
      }
  };
}

#endif //CFSM_EVENT_BASE_HPP