#include "EffectBuilder.h"
#include <iostream>

EffectBuilder::EffectBuilder() {}

std::vector<std::shared_ptr<Effect>> EffectBuilder::purgeVector() {
	std::vector<std::shared_ptr<Effect>> toReturn = effectVector;
	effectVector.clear();
	return toReturn;
}

std::shared_ptr<Effect> EffectBuilder::buildEffect(uint32_t effectEnum, std::vector<int>& values) {
	auto iter = values.begin();
	switch (effectEnum) {

	case Effect::CANCEL_BURN:
		if (values.size() < 1) {
            std::cout << "EffectBuilder: Insufficient arguments to build Effect with enum " << effectEnum << std::endl;
			return std::shared_ptr<Effect>(new Burn(0));
		}
		effectVector.push_back(std::shared_ptr<Effect>(new CancelBurn(*iter)));
		break;

	case Effect::BURN:
		if (values.size() < 1) {
            std::cout << "EffectBuilder: Insufficient arguments to build Effect with enum " << effectEnum << std::endl;
			return std::shared_ptr<Effect>(new Burn(0));
		}
		effectVector.push_back(std::shared_ptr<Effect>(new Burn(*iter)));
		break;

	case Effect::CLOCK_KICK:
		if (values.size() < 0) {
            std::cout << "EffectBuilder: Insufficient arguments to build Effect with enum " << effectEnum << std::endl;
			return std::shared_ptr<Effect>(new Burn(0));
		}		
		effectVector.push_back(std::shared_ptr<Effect>(new ClockKick()));
		break;

	case Effect::KIRITO_ASUNA:
		if (values.size() < 2) {
            std::cout << "EffectBuilder: Insufficient arguments to build Effect with enum " << effectEnum << std::endl;
			return std::shared_ptr<Effect>(new Burn(0));
		}
		effectVector.push_back(std::shared_ptr<Effect>(new KiritoAsuna(*iter, *++iter)));
		break;
	case Effect::MICHIRU:
		if (values.size() < 1) {
            std::cout << "EffectBuilder: Insufficient arguments to build Effect with enum " << effectEnum << std::endl;
			return std::shared_ptr<Effect>(new Burn(0));
		}
		effectVector.push_back(std::shared_ptr<Effect>(new Michiru(*iter)));
		break;

	default:
        std::cout << "Unknown Effect type, type enum: " << effectEnum << std::endl;
		return std::shared_ptr<Effect>(new Burn(0));
		break;
	}	
	return effectVector.back();
}