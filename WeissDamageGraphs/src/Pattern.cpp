#include "Pattern.h"
#include <iostream>

Pattern::Pattern(){
  m_flexibleAttacks = true;
  m_soulTriggers = false;
}

Pattern::Pattern(const Pattern& other) :
	m_flexibleAttacks(other.m_flexibleAttacks)
	, m_soulTriggers(other.m_soulTriggers)
	, m_currentAttacks(other.m_currentAttacks)
	, m_originalAttacks(other.m_originalAttacks)
{}

Pattern::~Pattern() {
}

void Pattern::addAttack(Attack toAdd){
  m_originalAttacks.push_back(toAdd);
}

void Pattern::reset() {
  m_currentAttacks.clear();
  for (Attack attack : m_originalAttacks){
    m_currentAttacks.push_back(attack);
  }
}

void Pattern::enableSoulTriggers(){
  m_soulTriggers = true;
}

void Pattern::lockAttackOrder(){
  m_flexibleAttacks = false;
}

void Pattern::reorderAttacks(){
  std::deque<Attack> tmpAttacks;
  for (int i = 0; i < m_currentAttacks.size(); i++) {
    int opposingChar = m_currentAttacks[i].getOpposingChar();
    int soul = m_currentAttacks[i].getSoul();
    if (opposingChar != -1 && soul - opposingChar > 0) {
      tmpAttacks.push_back(m_currentAttacks[i]);
    }
    else {
      tmpAttacks.push_front(m_currentAttacks[i]);
    }
  }
  copy(tmpAttacks.begin(), tmpAttacks.end(), m_currentAttacks.begin());
}

int Pattern::process(std::vector<int>& ownDeck
    , std::vector<int>& deck
    , std::vector<int>& refresh
    , int target){
  reset();
  // Check for directs
  for (int i = 0; i < m_currentAttacks.size(); i++){
    if (m_currentAttacks[i].getOpposingChar() == -1) {
      int newSoul = m_currentAttacks[i].getSoul() + 1;
      m_currentAttacks[i].setSoul(newSoul);
    }
  }

  if (m_flexibleAttacks){
    reorderAttacks();
  }

  int finalDamage = 0;
  GameState gameState(m_currentAttacks, ownDeck, deck, refresh);

  // TODO: cx phase effects

  // Loop for each attack & process effs
  while (m_currentAttacks.size() > 0) {
    Attack currentAttack = m_currentAttacks.back();
    // Check for possible side attack
    if (target > 0 && currentAttack.getSideSoul() > target){
      m_currentAttacks.back().setSoul(currentAttack.getSideSoul());
    }
    else {
      m_currentAttacks.back().setSoul(currentAttack.getSoul());
    }

    // Add trigger soul if triggers enabled
    if (m_soulTriggers) {
      if (ownDeck.back() == Effect::LVL_2 || ownDeck.back() == Effect::LVL_3) {
        m_currentAttacks.back().setSoul(currentAttack.getSoul() + 1);
      }
      ownDeck.pop_back();
    }

    finalDamage += m_currentAttacks.back().process(gameState);
    m_currentAttacks.pop_back();

    if (m_flexibleAttacks){
      reorderAttacks();
    }
  }

  // TODO: encore step or later effects
	return finalDamage;
}