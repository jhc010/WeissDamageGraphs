#pragma once
#include "Effect.h"

class Burn : public Effect {
	int m_burn; /**< Amount to burn */

  public:
    Burn(int burn){
      m_burn = burn;
    }

    int process(GameState& gameState){
        std::vector<int>& deck = gameState.getDeck();
        std::vector<int>& refresh = gameState.getRefresh();
        int refreshPoint = 0;
        int damage = 0;
        // Loop top cards on deck based on soul
        for (int i = 0; i < m_burn; i++) {
          int top = deck.back();
          deck.pop_back();
          // Break and set dmg to 0 on CX and add to potential damage if not CX
          if (top == e_CardType::CLIMAX) {
            // Damage cancelled
            damage = 0;
            refreshPoint += refreshCheck(deck, refresh);
            break;
          }
          else {
            damage++;
          }
          refreshPoint += refreshCheck(deck, refresh);
        }
        return damage + refreshPoint;
    }

	std::string toString() const {
		std::stringstream ret;
		ret << "burn " << m_burn;
		return ret.str();
	}
};