#ifndef __IAPPLICATION_H__
#define __IAPPLICATION_H__

#include "Arduino.h"

namespace application {
  namespace interface {
    class IApplication;
  }
}

class application::interface::IApplication {
public:
  virtual void Setup(void) = 0;
  virtual void Loop(void) = 0;
};

#endif // __IAPPLICATION_H__
