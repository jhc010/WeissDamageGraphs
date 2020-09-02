#include "AttackUI.h"

using namespace nana;

AttackUI::AttackUI(form& parent, std::shared_ptr<std::vector<Attack>>& savedAttacks
	, std::vector<RemovableDescriptionUI *> * savedAttacksUI
	, group& attackGroup) :
	m_attackGroup(attackGroup)
	, m_savedAttacks(savedAttacks)
	, m_savedAttacksUI(savedAttacksUI) {
	std::vector<std::string> testStr{ "input1","input2","input3","input4" };
	attackForm = new nana::form(parent, rectangle{ 100, 30, 1100, 600 });

	preAtkEffects = new group(*attackForm, rectangle{ 20, 20, 400, 500 });
	postAtkEffects = new group(*attackForm, rectangle{ 440, 20, 400, 500 });
	attackOptions = new group(*attackForm, rectangle{ 860, 20, 220, 150 });
	attackValues = new group(*attackForm, rectangle{ 860, 190, 220, 75 });

	addAttackButton = new button(*attackForm, rectangle{ 910, 340 , 130, 50 });
	addAttackButton->typeface(nana::paint::font{ "", 15 });
	addAttackButton->caption("Add Attack");
	addAttackButton->events().click([this]{
		// TODO: Add check for having no effects/attack options and stop stoi exception
		if (!createAttack()) {
			return;
		}
		size_t index = m_savedAttacks->size() - 1;
		m_savedAttacksUI->push_back(
			new RemovableDescriptionUI(m_attackGroup, 
				m_savedAttacks->at(index).toString(), 
				std::string(""), 
				std::string("attack"))
		);
		delete attackForm;
		removed = true;
	});

	attackValues->div("<margin=5\
		<soul vert arrange=20 margin=[0,30,0,0]>\
		<level vert arrange=20 margin=[0,10,0,0]>>");

	soul = new label(*attackValues, "soul");
	level = new label(*attackValues, "opposing char lvl");
	(*attackValues)["soul"] << *soul;
	(*attackValues)["level"] << *level;

	soulBox = new textbox(*attackValues, "");
	levelBox = new textbox(*attackValues, "");
	(*attackValues)["soul"] << *soulBox;
	(*attackValues)["level"] << *levelBox;
	attackValues->collocate();

	//attackOptions->add_option("front attack");
	//attackOptions->add_option("side attack");
	//attackOptions->add_option("direct attack");

	preAtkEffects->caption(L" [pre-attack effects] ");
	postAtkEffects->caption(L" [post-attack effects] ");
	attackOptions->caption(L" [attack options] ");

	preAtkEffects->div("<all vert gap=5 margin=[5,15]\
		<entry weight=100>\
		<data vert arrange=[50,repeated]>>");
	postAtkEffects->div("<all vert gap=5 margin=[5,15]\
		<entry weight=100><data vert arrange=[50,repeated]>>");

	preAttackEffs.reset(new EffectEntryGroup(*preAtkEffects, attackForm));
	postAttackEffs.reset(new EffectEntryGroup(*postAtkEffects, attackForm));

	attackForm->show();
}

int AttackUI::stringToInt(std::string &str, std::stringstream &errorStream, const char * label) {
	int ret;
	try {
		ret = std::stoi(str);
	}
	catch (std::exception e) {
		errorStream << label << " was not filled properly.\n";
	}
	return ret;
}

bool AttackUI::createAttack() {
	std::stringstream errorStream;
	// TODO: Add input cleaning for soul & opposing char level
	int soul = stringToInt(soulBox->caption(), errorStream, "soul ");
	int level = stringToInt(levelBox->caption(), errorStream, "level ");

	if (!errorStream.str().empty()) {
		PopupUI(errorStream.str(), attackForm);
		return false;
	}

	std::vector<std::shared_ptr<Effect>> preAttack = preAttackEffs->getEffects();
	std::vector<std::shared_ptr<Effect>> postAttack = postAttackEffs->getEffects();

	Attack toAdd(soul, preAttack, postAttack, level);
	m_savedAttacks->push_back(toAdd);
	return true;
}

AttackUI::~AttackUI() {
	delete preAtkEffects;
	delete postAtkEffects;
	delete soul;
	delete level;
	delete soulBox;
	delete levelBox;
	delete attackOptions;
	delete attackValues;
	delete addAttackButton;
	if (!removed) {
		delete attackForm;
	}
}