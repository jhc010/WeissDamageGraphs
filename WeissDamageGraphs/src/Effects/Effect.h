#pragma once
#include <vector>
#include "../GameState.h"
#include <sstream>
#include <random>
#include <algorithm>

/**
 * Abstract parent Effect class for effects to inherit from
 */
class Effect {
protected:
    /** Checks if a deck if out of cards and if it is, 
     * refreshes it
     * @param deck The deck to check for refresh
     * @param refresh The deckstate to refresh to
     */
	int refreshCheck(std::vector<int>& deck, std::vector<int>& refresh)
	{
		if (deck.size() == 0) {
			deck.resize(refresh.size());
			std::copy(refresh.begin(), refresh.end(), deck.begin());
			std::random_shuffle(deck.begin(), deck.end());
			return 1;
		}
		return 0;
	}

    bool m_cancel = false; /**< bool to determine if damage was cancelled*/
public:

    enum e_Effects {
      CANCEL_BURN,
      BURN,
      CLOCK_KICK,
      MICHIRU,
      KIRITO_ASUNA,
    };

    enum e_CardType {
      LVL_0 = 0,
      LVL_1,
      LVL_2,
      LVL_3,
      CLIMAX,
    };
    Effect(){}
    void setCancel(){
      m_cancel = true;
    }
    virtual int process(GameState& gameState) = 0;
	virtual std::string toString() const = 0;
};