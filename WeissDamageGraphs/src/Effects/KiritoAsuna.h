#include "Effect.h"
// PROTOTYPE KIROTOASUNA, CHANGE FOR MORE FLEXIBILITY (?)
class KiritoAsuna : public Effect {
	int millAmount; /**< Amount to mill */
	int burnAmount; /**< Amount to burn for cxs milled */
  public:
	  KiritoAsuna(int millAmount, int burnAmount) :
		millAmount(millAmount)
	    , burnAmount(burnAmount)
	  {}

    int process(GameState& gameState){
      int burns = 0;
      std::vector<int>& ownDeck = gameState.getOwnDeck();
      for (int i = 0; i < millAmount; i++){
        if (ownDeck.back() == Effect::CLIMAX){
          burns++;
        }
        ownDeck.pop_back();
      }

      int totalDmg = 0;
      for (int i = 0; i < burns; i++){
        Burn kiritoAsuna(burnAmount);
        totalDmg += kiritoAsuna.process(gameState);
      }
      return totalDmg;
    }

	std::string toString() const {
		std::stringstream ret;
		ret << "KiritoAsuna mill " << millAmount;
		ret << ", burn " << burnAmount;
		return ret.str();
	}
};