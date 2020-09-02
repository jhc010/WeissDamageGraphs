#include "Effect.h"
class CancelBurn : public Effect {
    int m_burn; /**< Amount to burn on cancel */

  public:
    CancelBurn(int burn){
      m_burn = burn;
    }

    int process(GameState& gameState){
      if (m_cancel){
        Burn cancelBurn(m_burn);
        return cancelBurn.process(gameState);
      }
      return 0;
    }

	std::string toString() const  {
		std::stringstream ret;
		ret << "cancel burn " << m_burn;
		return ret.str();
	}
};