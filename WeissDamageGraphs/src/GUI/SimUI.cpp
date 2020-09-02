#include "SimUI.h"
using namespace nana;

SimUI::SimUI() {
	sim.reset(new Simulator());
	simForm = new form(API::make_center(1300, 700));
	simOptions = new group(*simForm, rectangle{ 20, 20, 220, 250 });
	simOptions->caption("sim options");

	oppDeckUI = new group(*simForm, rectangle{ 20, 400, 220, 90 });
	oppDeckUI->caption("oppoennt's deckstate");
	oppDeckUI->div("< margin=[10,5]<climaxes vert margin=[0,15,0,0]><nonclimaxes vert margin=[0,15,0,0]>>");
	
	cxLabel = new label(*oppDeckUI, "climaxes");
	cxTextbox = new textbox(*oppDeckUI, "");
	(*oppDeckUI)["climaxes"] << *cxLabel;
	(*oppDeckUI)["climaxes"] << *cxTextbox;
	noncxLabel = new label(*oppDeckUI, "non-climaxes");
	noncxTextbox = new textbox(*oppDeckUI, "");
	(*oppDeckUI)["nonclimaxes"] << *noncxLabel;
	(*oppDeckUI)["nonclimaxes"] << *noncxTextbox;
	oppDeckUI->collocate();

	attackList = new group(*simForm, rectangle{ 260, 20, 500, 560 });
	attackList->caption("attacks");
	attackList->div("<attack vert gap=5 margin=[5,15] arrange=[80,repeated]>");

	plotList = new group(*simForm, rectangle{ 780, 20, 500, 560 });
	plotList->caption("plots");
	plotList->div("<plot vert gap=5 margin=[5,15] arrange=[80,repeated]>");

	simOptions->add_option("flexible attack order");		// 0
	simOptions->add_option("enable soul triggers");			// 1
	simOptions->add_option("disable cummulative plot");		// 2
	simOptions->add_option("show compression");				// 3
	simOptions->radio_mode(false);

	createAttack = new button(*simForm, rectangle{ 260, 600, 150, 70 });

	plotName = new group(*simForm, rectangle{ 435, 595, 150, 70 });
	plotName->div("<vert all margin=5>");
	plotNameLabel = new label(*plotName, "plot name:");
	plotNameBox = new textbox(*plotName);
	(*plotName)["all"] << *plotNameLabel;
	(*plotName)["all"] << *plotNameBox;
	plotName->collocate();

	makePlot = new button(*simForm, rectangle{ 610, 600, 150, 70 });
	executePlots = new button(*simForm, rectangle{ 955, 600, 150, 70 });

	createAttack->caption("Create Attack");
	makePlot->caption("Make Plot");
	executePlots->caption("Run Sim");

	savedAttacks = std::shared_ptr<std::vector<Attack>>(new std::vector<Attack>());
	savedPatterns = std::shared_ptr<std::vector<Pattern>>(new std::vector<Pattern>());
	savedAttacksUI = new std::vector<RemovableDescriptionUI *>();
	savedPatternsUI = new std::vector<RemovableDescriptionUI *>();

	createAttack->events().click([this]
	{
		// TODO: add some logic to disable the sim window
		attackUI.reset(new AttackUI(*simForm, savedAttacks, savedAttacksUI, *attackList));
	});

	makePlot->events().click([this]
	{
		createPattern();
	});

	executePlots->events().click([this]
	{
        std::stringstream errorStream;
		int oppCx, oppNoncx;
		std::string cxString = cxTextbox->caption();
		std::string noncxString = noncxTextbox->caption();
		size_t cxIndex = cxString.find_first_of("0123456789");
		size_t noncxIndex = noncxString.find_first_of("0123456789");

		oppCx = stringToInt(cxString.substr(cxIndex, cxString.length()), errorStream, "opponent's cx");
		oppNoncx = stringToInt(noncxString.substr(noncxIndex, noncxString.length()), errorStream, "opponent's non cx");

		if (!errorStream.str().empty()) {
			PopupUI(errorStream.str(), simForm);
			return;
		}

		for (int i = 0; i < savedPatternsUI->size(); i++) {
			if (!savedPatternsUI->at(i)->isRemoved()) {
				if (!simOptions->option_checked(0)) {
					savedPatterns->at(i).lockAttackOrder();
				}
				if (simOptions->option_checked(1)) {
					savedPatterns->at(i).enableSoulTriggers();
				}
				sim->addPattern(savedPatterns->at(i));
			}
		}
		// TODO: add helper and accept input for options
		bool disableCummulative = simOptions->option_checked(2);
		bool showCompression = simOptions->option_checked(3);

		int numSamples = 5000;

		sim->setOppDeck(oppCx, oppNoncx);
        std::vector<Result> results = sim->simulate(numSamples); //TODO: Accept input for # samples

		if (disableCummulative) {
			plotter->disableCummulative();

		}
		plotter->addPlot(results, numSamples);
		plotter->plot();
	});

	simForm->show();
	plotter.reset(new Plotter());
}


void SimUI::createPattern() {
	Pattern newPattern;
	for (int i = 0; i < savedAttacksUI->size(); i++) {
		if (!savedAttacksUI->at(i)->isRemoved()) {
			newPattern.addAttack(savedAttacks->at(i));
		}
	}
	savedPatterns->push_back(newPattern);
	std::string plotName;
	if (plotNameBox->caption().size() == 0) {
		plotName = "unnamed";
	}
	else {
		plotName = plotNameBox->caption();
	}
	savedPatternsUI->push_back(
		new RemovableDescriptionUI(*plotList,
			std::string("PlaceholderText"),
			plotName,
			std::string("plot"))
	);

	// TODO: set flags based on inputs
	// TODO: clear inputs
	// TODO: Update GUI for plot list
}

int SimUI::stringToInt(std::string &str, std::stringstream &errorStream, const char * label) {
	int ret;
	try {
		ret = std::stoi(str);
	}
	catch (std::exception e) {
		errorStream << label << " was not filled properly.\n";
	}
	return ret;
}

SimUI::~SimUI() {
	//delete buttons
	delete createAttack;
	delete makePlot;
	delete executePlots;

	for (RemovableDescriptionUI * element : *savedAttacksUI) {
		delete element;
	}
	for (RemovableDescriptionUI * element : *savedPatternsUI) {
		delete element;
	}
	delete savedAttacksUI;
	delete savedPatternsUI;

	delete attackList;
	delete plotList;

	delete plotNameLabel;
	delete plotNameBox;
	delete plotName;

	// delete sim elements
	delete simOptions;
	delete cxLabel;
	delete cxTextbox;
	delete noncxLabel;
	delete noncxTextbox;
	delete oppDeckUI;
	delete simForm;
}