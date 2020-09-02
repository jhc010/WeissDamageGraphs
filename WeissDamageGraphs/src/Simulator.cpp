#include "Simulator.h"
#include <algorithm>
#include <random>

Simulator::Simulator()
{
  for (int i = 0; i < DEFAULT_0; i++){
    m_ownDeck.push_back(Effect::LVL_0);
  }
  for (int i = 0; i < DEFAULT_1; i++){
    m_ownDeck.push_back(Effect::LVL_1);
  }
  for (int i = 0; i < DEFAULT_2; i++){
    m_ownDeck.push_back(Effect::LVL_2);
  }
  for (int i = 0; i < DEFAULT_3; i++){
    m_ownDeck.push_back(Effect::LVL_3);
  }
  for (int i = 0; i < DEFAULT_CX; i++){
    m_ownDeck.push_back(Effect::CLIMAX);
  }
}

void Simulator::setOppDeck(int cx, int noncx) {
	for (int i = 0; i < cx; i++) {
		m_deck.push_back(Effect::CLIMAX);
	}
	for (int i = 0; i < noncx; i++) {
		m_deck.push_back(Effect::LVL_0);
	}
}

void Simulator::addPattern(Pattern newPattern){
  m_patterns.push_back(newPattern);
}

void Simulator::removePattern(int index) {
	m_patterns.erase(m_patterns.begin() + index);
	// TODO: add error handling for OOB
}

void Simulator::setOwnDeck(int zero, int one, int two, int three, int cx){
  m_ownDeck.clear();
    for (int i = 0; i < zero; i++){
    m_ownDeck.push_back(Effect::LVL_0);
  }
  for (int i = 0; i < one; i++){
    m_ownDeck.push_back(Effect::LVL_1);
  }
  for (int i = 0; i < two; i++){
    m_ownDeck.push_back(Effect::LVL_2);
  }
  for (int i = 0; i < three; i++){
    m_ownDeck.push_back(Effect::LVL_3);
  }
  for (int i = 0; i < cx; i++){
    m_ownDeck.push_back(Effect::CLIMAX);
  }
}

std::vector<Result> Simulator::simulate(int samples){
    std::vector<Result> results(29);
	// Loop for samples
	for (int i = 0; i < samples; i++) {
    // TODO: Deal with multiple patterns besides index 0
    Result sampleResult = testSample(0);
		results[sampleResult.getDmgDealt()] += sampleResult;
	}
	return results;
}

void Simulator::addTarget(int target){
  m_targetDamage = target;
}

void Simulator::addRefresh(std::vector<int>& refresh)
{
  m_refresh.resize(refresh.size());
  copy(refresh.begin(), refresh.end(), m_refresh.begin());
}

// Test a single sample of pattern index and return damage dealt
Result Simulator::testSample(int index)
{
  // Setup deck
  std::vector<int> ownDeck;
  std::vector<int> deck;
  deck.resize(m_deck.size());
  std::copy(m_deck.begin(), m_deck.end(), deck.begin());
  std::random_shuffle(deck.begin(), deck.end());

  ownDeck.resize(m_ownDeck.size());
  std::copy(m_ownDeck.begin(), m_ownDeck.end(), ownDeck.begin());
  std::random_shuffle(ownDeck.begin(), ownDeck.end());

  // Setup refresh deck
  std::vector<int> refresh;
  if (m_refresh.size() == 0)
  {
    refresh.resize(deck.size());
    std::copy(deck.begin(), deck.end(), refresh.begin());
  }
  else 
  {
    refresh.resize(m_refresh.size());
    std::copy(m_refresh.begin(), m_refresh.end(), refresh.begin());
  }

	// Process pattern
  int dmgDealt = m_patterns[index].process(ownDeck, deck, refresh, m_targetDamage);
  if (dmgDealt > 28) {
    dmgDealt = 28;
  }
  int cxInDeck = 0;
  int nonCxInDeck = 0;
  for (int i : ownDeck){
    if (i == Effect::CLIMAX){
      cxInDeck++;
    }
    else{
      nonCxInDeck++;
    }
  }
  Result sampleResult(dmgDealt, cxInDeck, nonCxInDeck);
  return sampleResult;
}