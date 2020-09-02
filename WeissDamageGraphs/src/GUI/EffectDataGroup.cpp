#include "EffectDataGroup.h"
using namespace nana;

EffectDataGroup::EffectDataGroup(group& parent, std::vector<std::string>& inputs) {
	dataGroup = new group(parent, "DataGroup");
	parent["data"] << *dataGroup;
	dataGroup->caption_background_mode(group::background_mode::none);

	dataGroup->div("<margin=[0,5] <data gap=10 margin=[5,5,0,0]><button weight=50>>");
	for (int i = 0; i < inputs.size(); i++) {
		std::shared_ptr<label> newLabel(new label(*dataGroup, inputs[i], true));
		(*dataGroup)["data"] << *newLabel;
		// TODO: Figure out how to change background color of textbox
		labels.push_back(newLabel);
	}

	removeButton = new button(*dataGroup, true);
	removeButton->caption("remove");
	(*dataGroup)["button"] << *removeButton;
	removeButton->events().click([this, &parent]
	{
		removed = true;
		delete dataGroup;
	});

	// ADD YOUR STR MAPPING TO ENUM HERE
	effectToEnum = {
		{"BURN", Effect::BURN},
		{"CANCEL_BURN", Effect::CANCEL_BURN},
		{"MICHIRU", Effect::MICHIRU},
		{"CLOCK_KICK", Effect::CLOCK_KICK},
		{"KIRITO_ASUNA", Effect::KIRITO_ASUNA},
	};

	parent.collocate();
}

std::shared_ptr<Effect> EffectDataGroup::getEffect(EffectBuilder& builder) {
	uint32_t effEnum = effectToEnum[labels[0]->caption()];

	std::vector<int> args;
	for (int i = 1; i < labels.size(); i++) {
		int arg;
		std::string argString = labels[i]->caption();
		size_t numIndex = argString.find_first_of("0123456789");
		if (numIndex > argString.length()) {
			continue;
		}
		arg = std::stoi(argString.substr(numIndex, argString.length()));
		args.push_back(arg);
	}
	return builder.buildEffect(effEnum, args);
}

EffectDataGroup::~EffectDataGroup() {
		delete removeButton;
		if (!removed) {
			delete dataGroup;
		}
}