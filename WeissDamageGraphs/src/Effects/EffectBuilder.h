#pragma once
#include "Burn.h"
#include "ClockKick.h"
#include "CancelBurn.h"
#include "KiritoAsuna.h"
#include "Michiru.h"
#include <memory>

class EffectBuilder {
	std::vector<std::shared_ptr<Effect>> effectVector; /**< Vector of built effects */
public:
  EffectBuilder();
  std::vector<std::shared_ptr<Effect>> purgeVector();
  std::shared_ptr<Effect> buildEffect(uint32_t effectEnum, std::vector<int>& values);
};