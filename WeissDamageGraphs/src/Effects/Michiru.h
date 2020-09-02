#include "Effect.h"
class Michiru : public Effect {
	int millAmount; /**< Amount to mill */
public:
	Michiru(int millAmount) :
		millAmount(millAmount)
	{}

	int process(GameState& gameState) {
		int burn = 0;
		int refreshPoint = 0;
		std::vector<int>& deck = gameState.getDeck();
		for (int i = 0; i < millAmount; i++) {
			if (deck.front() == Effect::CLIMAX) {
				burn++;
			}
			deck.erase(deck.begin());
			refreshPoint += refreshCheck(deck, gameState.getRefresh());
		}

		Burn michiru(burn);
		int damage = michiru.process(gameState) + refreshPoint;
		return damage;
	}

	std::string toString() const {
		std::stringstream ret;
		ret << "Michiru mill " << millAmount;
		return ret.str();
	}
};