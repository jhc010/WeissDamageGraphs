#pragma once
#include "../Effects/Effect.h"
#include "../Effects/EffectBuilder.h"
#include "nana/gui.hpp"
#include "nana/gui/widgets/label.hpp"
#include "nana/gui/widgets/group.hpp"
#include "nana/gui/widgets/button.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * UI class for an effect data nana group
 */
class EffectDataGroup {
	bool removed = false;
	nana::group * dataGroup;
    nana::button * removeButton;
	std::vector<std::shared_ptr<nana::label>> labels;
	std::unordered_map<std::string, uint32_t> effectToEnum;
public:
	EffectDataGroup(nana::group& parent, std::vector<std::string>& inputs);
	bool isRemoved() { return removed; };
	std::shared_ptr<Effect> getEffect(EffectBuilder& builder);
	~EffectDataGroup();
};