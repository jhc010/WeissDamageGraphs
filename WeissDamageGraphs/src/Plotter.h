#pragma once
#include "Python.h"
#include "Result.h"
#include <vector>

/**
 * Plotter class that calls functions from 
 * the Python file Logger.py to create plots with
 * matplotlib
 */
class Plotter {
	bool m_showDeckstate; /**< bool to determine if own deckstate should be plotted */
	bool m_showCummulative; /**< bool to determine if data should be plotted cummulatively */
	PyObject *pName, *pModule, *pDict; /**< Python objects used to access functions from the Logger class */
	std::vector<Result> results;
	std::vector<double> damageVec;
	std::vector<double> probVec;
	std::vector<double> probCummulativeVec;
	std::vector<double> compressionVec;
	void plotDeckstate();

public:
        /** Default constructor */
		Plotter();
        /** Destructor */
		~Plotter();
        /** 
         * Adds a new plot to the Plotter class, to be displayed when plot() is called 
         * @param results The data to be plottedd
         * @param numSamples Number of samples used for the data
         * TODO: Add ability to store multiple plots, get rid of numSamples maybe.
         */
		void addPlot(std::vector<Result>& results, int numSamples);
        /** Enables the player's deckstate to be plotted */
		void enableShowDeck() { m_showDeckstate = true; }
        /** Enables non-cummulative plotting of the data */
		void disableCummulative(){ m_showCummulative = false; }
        /** Display the plots currently added to the Plotter*/
		void plot();
};