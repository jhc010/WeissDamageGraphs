#pragma once
#include "Effects/Effect.h"

/**
 * Class that handles a character's attack
 */
class Attack : public Effect {
  private:
    int m_soul;  /**< soul value assigned to attack */
    std::vector<std::shared_ptr<Effect>> m_preAttackEff;  /**< vector of effects to process before the attack */
    std::vector<std::shared_ptr<Effect>> m_postAttackEff;  /**< vector of effects to process after the attack */
    int m_opposingChar; /**< level of the opposing character */

  public:
    /**
     * Constructor for the Attack class
     * @param soul The soul of the character attacking
     * @param preAttackEff A vector of the effects to be activated before the attack
     * @param postAttackEff A vector of the effects to be activated after the attack
     * @param opposingChar The level of the opposing character
     */
    Attack(int soul
        , std::vector<std::shared_ptr<Effect>> preAttackEff
        , std::vector<std::shared_ptr<Effect>> postAttackEff
        , int opposingChar);
    /**
     * Copy constructor for the Attack class
     * @param other The attack to copy from
     */
    Attack(const Attack& other);

    /**
     * Public method to execute the attack, returns the total damage done
     * @param gameState The current GameState
     */
    int process(GameState& gameState);

    /**
     * Getter for m_soul
     */
    int getSoul() const {
      return m_soul;
    }

    /**
     * Getter for m_preAttackEff
     */
    std::vector<std::shared_ptr<Effect>> getPreAttackEff() const {
      return m_preAttackEff;
    }

    /**
     * Getter for m_postAttackEff
     */
    std::vector<std::shared_ptr<Effect>> getPostAttackEff() const {
      return m_postAttackEff;
    }

    /**
     * Getter for m_opposingChar
     */
    int getOpposingChar() const {
      return m_opposingChar;
    }

    /**
     * Setter for m_soul
     */
    void setSoul(int newSoul) {
      m_soul = newSoul;
    }

    /**
     * Returns the side attack soul value
     */
    int getSideSoul() const{
      return m_soul - m_opposingChar;
    }

    /**
     * Outputs a string representation of the Attack
     */
	std::string toString() const;
};