#ifndef CFSM_EVENT_HPP
#define CFSM_EVENT_HPP

#include <cstddef>

namespace Fsm
{
  struct EventBase
  {
    static std::size_t next()
    {
      static std::size_t counter = 0;
      return counter++;
    }
  };

  template <typename DerivedEventT>
  struct Event : public EventBase
  {
    static std::size_t id() const
    {
      static std::size_t id = EventBase::next();
      return id;
    }
  };
}

#endif //CFSM_EVENT_HPP