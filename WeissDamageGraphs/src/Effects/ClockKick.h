#include "Effect.h"
class ClockKick : public Effect {
  bool m_success;   /**< whether clock kick succeeded */

  public:
    ClockKick(){
      m_success = true;
    }

    void noReverse(){
      m_success = false;
    }

    int process(GameState& gameState){
      if (m_success) {
        return 1;
      }
      else {
        return 0;
      }
    }

	std::string toString() const {
		return std::string("clock kick");
	}
};