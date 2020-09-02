#pragma once
#include "../Attack.h"
#include "EffectDataGroup.h"
#include "EffectEntryGroup.h"
#include "PopupUI.h"
#include "RemovableDescriptionUI.h"

class AttackUI {
	bool removed = false;
	nana::form * attackForm;
	nana::group *preAtkEffects, *postAtkEffects, *attackOptions, *attackValues;
	
    //attackValues
    nana::label *soul, *level;
	nana::textbox *soulBox, *levelBox;

	nana::button * addAttackButton;

	std::unique_ptr<EffectEntryGroup> preAttackEffs;
	std::unique_ptr<EffectEntryGroup> postAttackEffs;

	std::shared_ptr<std::vector<Attack>>& m_savedAttacks;
	std::vector<RemovableDescriptionUI *> * m_savedAttacksUI;

    nana::group& m_attackGroup;

	int stringToInt(std::string &str, std::stringstream &errorStream, const char * label);
	bool createAttack();
public:
	AttackUI(nana::form& parent
		, std::shared_ptr<std::vector<Attack>>& savedAttacks
		, std::vector<RemovableDescriptionUI *> * savedAttacksUI
		, nana::group& attackGroup);
	void showForm() { attackForm->show(); }
	~AttackUI();
};