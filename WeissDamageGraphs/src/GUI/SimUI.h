#include "AttackUI.h"
#include "../Simulator.h"
#include "../Plotter.h"

/**
 * UI class for the main form that holds the sim
 */
class SimUI {
	nana::form * simForm;
    nana::group *simOptions, *oppDeckUI, *attackList, *plotList, *plotName;

    // oppDeckUI
	nana::label *cxLabel, *noncxLabel;
	nana::textbox *cxTextbox, *noncxTextbox;

    // plotName
	nana::label * plotNameLabel;
	nana::textbox * plotNameBox;

	nana::button *createAttack, *makePlot, *executePlots;

	std::unique_ptr<Plotter> plotter;
	std::unique_ptr<Simulator> sim;
	std::unique_ptr<AttackUI> attackUI;
	std::shared_ptr<std::vector<Attack>> savedAttacks;
	std::shared_ptr<std::vector<Pattern>> savedPatterns;
	std::vector<RemovableDescriptionUI *> * savedAttacksUI;
	std::vector<RemovableDescriptionUI *> * savedPatternsUI;

	int stringToInt(std::string &str, std::stringstream &errorStream, const char * label);
	void createPattern();
public:
	SimUI();
	~SimUI();
};