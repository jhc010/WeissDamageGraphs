#include "Pattern.h"
#include "Result.h"

class Simulator {
public:
  Simulator();

  std::vector<Result> simulate(int samples);
  void setOppDeck(int cx, int noncx);
  void setOwnDeck(int zero, int one, int two, int three, int cx);
  void addPattern(Pattern newPattern);
  void removePattern(int index);
  void addTarget(int target);
  void addRefresh(std::vector<int>& refresh);

private:
  const int DEFAULT_0 = 16;
  const int DEFAULT_1 = 12;
  const int DEFAULT_2 = 3;
  const int DEFAULT_3 = 11;
  const int DEFAULT_CX = 8;

  std::vector<Pattern> m_patterns;
  std::vector<int> m_deck;
  std::vector<int> m_refresh;
  std::vector<int> m_ownDeck;

  int m_targetDamage = 0;
  Result testSample(int index);
};