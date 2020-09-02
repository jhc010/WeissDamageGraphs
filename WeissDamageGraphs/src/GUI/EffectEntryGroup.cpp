#include "EffectEntryGroup.h"
#include "../Effects/EffectBuilder.h"
using namespace nana;

std::string stringTest(std::string &str, std::stringstream &errorStream, std::string& label) {
	int ret;
	try {
		ret = std::stoi(str);
	}
	catch (std::exception e) {
		errorStream << label << " was not filled properly.\n";
	}
	return std::to_string(ret);
}

EffectEntryGroup::EffectEntryGroup(group& parent, form * attackForm) {
	m_attackForm = attackForm;
	effectEntry = new group(parent, "", true);
	parent["entry"] << *effectEntry;

	effectEntry->div("<gap=10 margin=[15,20] arrange=100\
		<dropdown max=100 vert>\
		<tb1 margin=[5,15] vert>\
		<tb2 margin=[5,15] vert>\
		<button margin=[5,0,5,15] weight=60>>");

	comboxLabel = new label(*effectEntry, "choose effect", true);
	tb1Label = new label(*effectEntry, false);
	tb2Label = new label(*effectEntry, false);

	effectCombox = new combox(*effectEntry);
	(*effectEntry)["dropdown"] << *comboxLabel;
	(*effectEntry)["tb1"] << *tb1Label;
	(*effectEntry)["tb2"] << *tb2Label;
	(*effectEntry)["dropdown"] << *effectCombox;

	effectCombox->editable(false);
	// ADD NEW EFFECT NAMES HERE
	effectCombox->push_back("BURN");
	effectCombox->push_back("CANCEL_BURN");
	effectCombox->push_back("CLOCK_KICK");
	effectCombox->push_back("MICHIRU");
	effectCombox->push_back("KIRITO_ASUNA");

	tb1 = new textbox(*effectEntry, false);
	tb2 = new textbox(*effectEntry, false);
	(*effectEntry)["tb1"] << *tb1;
	(*effectEntry)["tb2"] << *tb2;

	addButton = new button(*effectEntry, true);
	addButton->caption("Add");
	addButton->events().click([&parent, this]
	{
		std::stringstream errorStream;
		std::string input1;
		std::string input2;

		if (tb1Label->caption().size() != 0) {
			input1 = stringTest(tb1->text(), errorStream, tb1Label->caption());
		}
		if (tb2Label->caption().size() != 0) {
			input2 = stringTest(tb2->text(), errorStream, tb2Label->caption());
		}
		if (!errorStream.str().empty()) {
			PopupUI popup(errorStream.str(), m_attackForm);
			return;
		}

		tb1->caption(input1);
		tb2->caption(input2);
		inputList.push_back(effectCombox->text(effectCombox->option()));
		inputList.push_back(tb1Label->caption() + input1);
		inputList.push_back(tb2Label->caption() + input2);
		dataList.push_back(new EffectDataGroup(parent, inputList));
		inputList.clear();
	});
	addButton->enabled(false);
	(*effectEntry)["button"] << *addButton;

	effectCombox->events().selected([this](const arg_combox &ar_cbx) {
		std::string effName = ar_cbx.widget.caption();
		if (lastEffect != effName) {
			tb1->reset();
			tb2->reset();
			lastEffect = effName;
		}
			if (effName != "") {
			addButton->enabled(true);
		}
		// ADD YOUR REQUIRED LOGIC HERE // Where's my switch on strings :C
		if (effName == "BURN") {
			tb1Label->caption("Burn #: ");
			tb2Label->caption("");
			effectEntry->field_display("tb1", true);
			effectEntry->field_display("tb2", false);
		}
		else if (effName == "CANCEL_BURN") {
			tb1Label->caption("Burn #: ");
			tb2Label->caption("");
			effectEntry->field_display("tb1", true);
			effectEntry->field_display("tb2", false);
		}
		else if (effName == "MICHIRU") {
			tb1Label->caption("Mill #: ");
			tb2Label->caption("");
			effectEntry->field_display("tb1", true);
			effectEntry->field_display("tb2", false);
		}
		else if (effName == "CLOCK_KICK") {
			tb1Label->caption("");
			tb2Label->caption("");
			effectEntry->field_display("tb1", false);
			effectEntry->field_display("tb2", false);
		}
		else if (effName == "KIRITO_ASUNA") {
			tb1Label->caption("Mill #: ");
			tb2Label->caption("Burn #: ");
			effectEntry->field_display("tb1", true);
			effectEntry->field_display("tb2", true);
		}

		effectEntry->collocate();
	});

	parent.collocate();
}

std::vector<std::shared_ptr<Effect>> EffectEntryGroup::getEffects() {
	EffectBuilder builder;
	for (EffectDataGroup * dataPtr : dataList) {
		if (!dataPtr->isRemoved()) {
			dataPtr->getEffect(builder);
		}
	}
	return builder.purgeVector();
}

EffectEntryGroup::~EffectEntryGroup() {
	delete tb1Label;
	delete tb1;
	delete tb2Label;
	delete tb2;
	delete comboxLabel;
	delete addButton;
	for (int i = 0; i < dataList.size(); i++) {
		delete dataList[i];
	}
	delete effectCombox;
	delete effectEntry;
}