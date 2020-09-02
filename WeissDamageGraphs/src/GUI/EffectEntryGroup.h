#pragma once
#include "EffectDataGroup.h"
#include "PopupUI.h"
#include "nana/gui.hpp"
#include "nana/gui/widgets/textbox.hpp"
#include "nana/gui/widgets/group.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/combox.hpp"
#include "nana/gui/widgets/label.hpp"
#include <iostream>
#include <vector>
#include <memory>

/**
 * UI class for an effect entry nana group
 */
class EffectEntryGroup{
	nana::form * m_attackForm;
	nana::group * effectEntry;

	nana::label * comboxLabel;
	nana::combox * effectCombox;
	
	nana::label * tb1Label;
	nana::textbox * tb1;

	nana::label * tb2Label;
	nana::textbox * tb2;

    nana::button * addButton;
	std::string lastEffect;

	std::vector<EffectDataGroup*> dataList;
	std::vector<std::string> inputList;
public:
	EffectEntryGroup(nana::group& parent, nana::form * attackForm);
	std::vector<std::shared_ptr<Effect>> getEffects();
	~EffectEntryGroup();
};