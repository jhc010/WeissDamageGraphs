#include "nana/gui/widgets/group.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/combox.hpp"
#include "nana/gui/widgets/label.hpp"
#include <string>
#include <functional>

class RemovableDescriptionUI {

	nana::group * m_newGroup;
	nana::label * m_description;
	nana::button * m_removeButton;
	bool m_removed = false;

	public:
		RemovableDescriptionUI(nana::group& parent, std::string& description, std::string& name, std::string& key) {
			m_newGroup = new nana::group(parent, name, true);
			m_newGroup->div("<description margin=5><button margin=[10,10] weight=70>");
			parent[key.c_str()] << *m_newGroup;
			m_newGroup->caption_background_mode(nana::group::background_mode::none);

			m_description = new nana::label(*m_newGroup, description, true);
			(*m_newGroup)["description"] << *m_description;

			m_removeButton = new nana::button(*m_newGroup, true);
			m_removeButton->caption("remove");
			(*m_newGroup)["button"] << *m_removeButton;
			m_removeButton->events().click([this, &parent]
			{
				m_removed = true;
				delete m_removeButton;
				delete m_description;
				delete m_newGroup;
				parent.collocate();
			});

			parent.collocate();
		}

		bool isRemoved() { return m_removed; }

		~RemovableDescriptionUI() {
			if (!m_removed) {
				delete m_removeButton;
				delete m_description;
				delete m_newGroup;
			}
		}
};