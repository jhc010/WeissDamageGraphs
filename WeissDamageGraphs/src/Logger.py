import matplotlib as mpl
mpl.use('WXAgg')
import matplotlib.pyplot as plt
import numpy as np

def GraphDamage(damageTuple, probabilityTuple):
	damage = np.array(damageTuple)
	probability = np.array(probabilityTuple)

	plt.plot(damage, probability)
	plt.xlabel('Damage dealt')
	plt.ylabel('Probability to occur')
	plt.show()
	return

def GraphDeckstate(damageTuple, deckTuple):
	damage = np.array(damageTuple)
	deckstate = np.array(deckTuple)

	plt.plot(damage, deckstate)
	plt.xlabel('Damage dealt')
	plt.ylabel('Own compression: 1 in x')
	plt.show()
	return