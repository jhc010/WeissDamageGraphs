#include "Attack.h"
#include "Effects/Burn.h"
#include <iostream>

Attack::Attack(int soul
    , std::vector<std::shared_ptr<Effect>> preAttackEff
    , std::vector<std::shared_ptr<Effect>> postAttackEff
    , int opposingChar) :
  m_soul(soul)
  , m_opposingChar(opposingChar)
	, m_preAttackEff(preAttackEff)
	, m_postAttackEff(postAttackEff)
{}

Attack::Attack(const Attack& other) :
  m_soul(other.m_soul)
  , m_opposingChar(other.m_opposingChar)
  , m_preAttackEff(other.m_preAttackEff)
  , m_postAttackEff(other.m_postAttackEff)
{}

int Attack::process(GameState& gameState){
  int finalDamage = 0;
  bool cancel = false;
  for (std::shared_ptr<Effect> eff : m_preAttackEff){
    int preAttackDamage = eff->process(gameState);
    // TODO: AFTER ADDING UTILITY EFFS PLS CHANGE THIS
    if (preAttackDamage == 0) {
      cancel = true;
    }
    finalDamage += preAttackDamage;
  }

  Burn attack(m_soul);
  int damage = attack.process(gameState);
  finalDamage += damage;

  for (std::shared_ptr<Effect> eff : m_postAttackEff){
    if (cancel){
      eff->setCancel();
    }
    int postAttackDamage = eff->process(gameState);
    if (postAttackDamage == 0) {
      cancel = true;
    }
    finalDamage += postAttackDamage;
  }

  return finalDamage;
}

std::string Attack::toString() const {
	std::stringstream toReturn;
	if (m_preAttackEff.size() > 0) {
		toReturn << m_preAttackEff[0]->toString();
		if (m_preAttackEff.size() > 1) {
			toReturn << " ... (";
			toReturn << (m_preAttackEff.size() - 1) << " more)";
		}
		toReturn <<"\n";
	}

	toReturn << m_soul;
	toReturn << " soul, ";
	toReturn << "facing level ";
	toReturn << m_opposingChar;

	if (m_postAttackEff.size() > 0) {
		toReturn << "\n" + m_postAttackEff[0]->toString();
		if (m_postAttackEff.size() > 1) {
			toReturn << " ... (";
			toReturn << (m_postAttackEff.size() - 1) << " more)";
		}
	}
	return toReturn.str();
}
