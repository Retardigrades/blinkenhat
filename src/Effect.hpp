#pragma once

#include "LEDBand.hpp"
#include "Config.h"

class Effect {
public:
  Effect() = default;

  virtual void update(LEDBand &band, unsigned long time)  = 0;
  virtual void restart() = 0;
  virtual void config(const ConfigWrapper &)  = 0;
  virtual ~Effect() = default;

protected:
};
