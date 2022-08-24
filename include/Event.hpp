#ifndef CFSM_EVENT_HPP
#define CFSM_EVENT_HPP

#include <cstddef>

#include "internal/EventBase.hpp"

namespace Fsm
{
  /**
   * @brief Base class for all user events.
   * 
   * @tparam DerivedEventT The type of the derived event
   */
  template <typename DerivedEventT>
  struct Event : public EventBase
  {
  };
}

#endif //CFSM_EVENT_HPP