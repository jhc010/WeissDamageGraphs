#pragma once
#include "nana/gui.hpp"
#include "nana/gui/widgets/label.hpp"


class PopupUI {	
	nana::form * m_popup;
	nana::label * m_message;
public:
	PopupUI(std::string& message, nana::form * parent) {
		m_popup = new nana::form(nana::API::make_center(420, 200));
		m_popup->div("<><vfit=200 message><>");
		m_message = new nana::label(*m_popup, message);
		(*m_popup)["message"] << *m_message;
		m_popup->collocate();
		m_popup->show();
		parent->enabled(false);
		m_popup->wait_for_this();
		parent->enabled(true);
	}

	~PopupUI(){
		delete m_popup;
		delete m_message;
	}
};