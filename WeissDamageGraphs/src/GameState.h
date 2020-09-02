#pragma once
#include <memory>
#include <deque>

class Attack;

/**
 * Class representing data for the current GameState
 */
class GameState {
    std::deque<Attack>& m_attacks; /**< Deque of unprocessed Attacks*/
    std::vector<int>& m_ownDeck; /**< Player's deck */
    std::vector<int>& m_deck; /**< Oppoent's deck */
    std::vector<int>& m_refresh;  /**< Opponent's post-refresh deck */
  
public:
    /**
     * Constructor for Gamestate
     * @param attacks Deque of unprocessed Attacks
     * @param ownDeck Player's deck
     * @param deck Oppoent's deck
     * @param refresh Opponent's post-refresh deck
     */
    GameState(std::deque<Attack>& attacks, std::vector<int>& ownDeck, std::vector<int>& deck, std::vector<int>& refresh) :
      m_ownDeck(ownDeck),
      m_deck(deck),
      m_refresh(refresh),
      m_attacks(attacks)
    {}

    /**
     * Getter for m_ownDeck
     */
    std::vector<int>& getOwnDeck(){
      return m_ownDeck;
    }

    /**
     * Getter for m_deck
     */
    std::vector<int>& getDeck(){
      return m_deck;
    }

    /**
     * Getter for m_refresh
     */
    std::vector<int>& getRefresh(){
      return m_refresh;
    }
};