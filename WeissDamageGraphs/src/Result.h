#pragma once

/**
 * Class that represents the result of a Pattern and can be plotted
 * TODO: Move plotting functionality into this class
 */
class Result {
  int m_occurances; /**< Number of samples */
  int m_damageDealt; /**< Total damage dealt by all samples */
  int m_cxInDeck; /**< total cx in deck in all samples*/
  int m_nonCxInDeck; /**< total non-cx in deck  in all samples*/
public:
  /** Default constructor */
  Result(){
    m_damageDealt = 0;
    m_cxInDeck = 0;
    m_nonCxInDeck = 0;
    m_occurances = 0;
  }

  /** += operator for single sample only 
   * TODO: Add error output for non single sample input
   */
  Result& operator+=(const Result& input) {
    m_damageDealt += input.m_damageDealt;
    m_cxInDeck += input.m_cxInDeck;
    m_nonCxInDeck += input.m_nonCxInDeck;
    m_occurances++;
    return *this;
  }

  /** Constructor for Result, number of samples is initialized to 0 
   * @param dmgDealt Total damage dealt to initialize with
   * @param cxInDeck Total cx in deck to initialize with
   * @param nonCxInDeck Total non-cx in deck to initialize with
   */
  Result(int dmgDealt, int cxInDeck, int nonCxInDeck)
    : m_damageDealt(dmgDealt),
    m_cxInDeck(cxInDeck),
    m_nonCxInDeck(nonCxInDeck)
  {
    m_occurances = 0;
  }

  /** Getter for m_occurances */
  int getOccurances(){
    return m_occurances;
  }
  /** Getter for m_damageDealt */
  int getDmgDealt(){
    return m_damageDealt;
  }
  /** Adds to the total damage dealt
   * @param dmgDealt The amount of damage to add
   */
  void addDmgDealt(int dmgDealt){
    m_damageDealt += dmgDealt;
  }
  /** Getter for m_cxInDeck */
  int getCxInDeck(){
    return m_cxInDeck;
  }
  /** Getter for m_nonCxInDeck */
  int getNonCxInDeck(){
    return m_nonCxInDeck;
  }
};