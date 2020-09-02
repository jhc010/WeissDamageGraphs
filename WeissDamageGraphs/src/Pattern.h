#include <deque>
#include <memory>
#include "Attack.h"

/**
 * Class that holds a set of attacks and settings to process them with
 */
class Pattern {
  bool m_flexibleAttacks; /**< bool that determines if attack order can be rearranged mid-processing */
  bool m_soulTriggers; /**< bool that determines if soul triggers are registered */
  std::deque<Attack> m_currentAttacks; /**< deque of attacks to be processed */
  std::deque<Attack> m_originalAttacks; /**< deque of all the attacks in the Pattern, including processed attacks */

  /**
   * Reorders attacks in the Pattern by putting attacks without side
   * attack possibilities in front
   */
  void reorderAttacks(); 

public:
  /** Default constructor */
  Pattern();
  /** Copy constructor */
  Pattern(const Pattern& other);
  /** Destructor */
  ~Pattern();

  /**
   * Called to process all the attacks in the Pattern
   * @param ownDeck The player's deckstate
   * @param deck The opponent's deckstate
   * @param refresh The deckstate the opponent will refresh to
   * @param target The target damage to achieve (May cause side-attacks & change certain effects)
   * @return the damage dealt by processing all the Attacks in the Pattern
   */
  int process(std::vector<int>& ownDeck
      , std::vector<int>& deck
      , std::vector<int>& refresh
      , int target);
  /**
   * Enables soul triggers for the Pattern (m_soulTriggers = true)
   */
  void enableSoulTriggers();
  /**
   * Locks attack order for the Pattern (m_flexibleAttacks = false)
   */
  void lockAttackOrder();
  /**
   * Resets the deque of queued Attacks to the original set of Attacks
   */
  void reset();
  /**
   * Add a new Attack to the Pattern
   * @param toAdd the Attack added to the Pattern
   */
  void addAttack(Attack toAdd);
};
