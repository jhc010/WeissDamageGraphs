#include "Plotter.h"
#include <iostream>
#include <vector>

Plotter::Plotter() {
	m_showCummulative = true;
	m_showDeckstate = false;
	Py_Initialize();
	// Load matplotlib
	pName = PyString_FromString("Logger");
	if (!pName) {
		std::cout << "Creating name failed" << std::endl;
		PyErr_Print();
		std::cin.get();
		return;
	}
	pModule = PyImport_Import(pName);
	if (!pModule) {
		std::cout << "Get Module failed" << std::endl;
		PyErr_Print();
		std::cin.get();
		return;
	}
	pDict = PyModule_GetDict(pModule);
	if (!pDict) {
		std::cout << "Get dictionary failed" << std::endl;
		PyErr_Print();
		std::cin.get();
		return;
	}
}

Plotter::~Plotter() {
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();
}

void Plotter::addPlot(std::vector<Result>& results, int numSamples) {
	//TODO: Allow one Plotter to handle multiple plots, also modify results to not have to pass vector
	this->results = results;
	//retrieveDmg
	for (int i = 0; i < results.size(); i++) {
		if (results[i].getOccurances() > 0) {
			damageVec.push_back(i);
		}
	}
	//retrieveP
	for (int i = 0; i < results.size(); i++) {
		if (results[i].getOccurances() > 0) {
			double probability = ((double)(results[i].getOccurances()) / (double)numSamples) * 100;
			probVec.push_back(probability);
		}
	}
	//retrieveCummulative
	float cummulativeProbability = 0;
	for (int i = 0; i < results.size(); i++) {
		if (results[i].getOccurances() > 0) {
			cummulativeProbability += ((float)results[i].getOccurances() / (float)numSamples) * 100;
			probCummulativeVec.push_back(cummulativeProbability);
		}
	}
	//retrieveCompression
	for (int i = 0; i < results.size(); i++) {
		if (results[i].getOccurances() > 0) {
			double avgCxInDeck = (double)(results[i].getCxInDeck()) / (double)numSamples;
			double avgNonCxInDeck = (double)(results[i].getNonCxInDeck()) / (double)numSamples;
			compressionVec.push_back((avgCxInDeck + avgNonCxInDeck) / avgCxInDeck);
		}
	}

	// cummulative stuff
	if (!m_showCummulative) {
		for (int i = 0; i < results.size(); i++) {
			if (results[i].getOccurances() > 0) {
				double probability = ((double)(results[i].getOccurances()) / (double)numSamples) * 100;
				std::cout << i << ": " << probability << "%";
				if (m_showDeckstate) {
					double avgCxInDeck = (double)(results[i].getCxInDeck()) / (double)numSamples;
					double avgNonCxInDeck = (double)(results[i].getNonCxInDeck()) / (double)numSamples;
					if (avgCxInDeck != 0) {
						std::cout << "\t\t Compression: 1 in " << (avgCxInDeck + avgNonCxInDeck) / avgCxInDeck;
					}
				}
				std::cout << std::endl;
			}
		}
	}
	else {
		double cummulativeProbability = 0;
		for (size_t i = results.size() - 1; i > 0; i--) {
			if (results[i].getOccurances() > 0) {
				cummulativeProbability += ((double)results[i].getOccurances() / (double)numSamples) * 100;
				std::cout << i << ": " << cummulativeProbability << "%" << std::endl;
			}
		}
	}
}

void Plotter::plot() {	
	PyObject *pFunc, *pValue;
	pFunc = PyDict_GetItemString(pDict, "GraphDamage");
	if (!pFunc) {
		std::cout << "Get function GraphDamage failed" << std::endl;
		PyErr_Print();
		std::cin.get();
		return;
	}

	if (PyCallable_Check(pFunc))
	{
		std::cout << "Callable check success";
		PyObject_CallObject(pFunc, NULL);
	}
	else
	{
		std::cout << "Callable check failed";
		PyErr_Print();
		std::cin.get();
		return;
	}

	PyObject* dmgTuple = PyTuple_New(damageVec.size());
	PyObject* probTuple = PyTuple_New(probVec.size());

	for (int i = 0; i < damageVec.size(); i++) {
		pValue = PyInt_FromLong((long)damageVec[i]);
		PyTuple_SetItem(dmgTuple, i, pValue);
	}

	if (!m_showCummulative) {
		for (int i = 0; i < probVec.size(); i++) {
			pValue = PyFloat_FromDouble(probVec[i]);
			PyTuple_SetItem(probTuple, i, pValue);
		}
	}
	else {
		for (int i = 0; i < probCummulativeVec.size(); i++) {
			pValue = PyFloat_FromDouble(probCummulativeVec[i]);
			PyTuple_SetItem(probTuple, i, pValue);
		}
	}

	PyObject* pData = PyTuple_New(2);
	PyTuple_SetItem(pData, 0, dmgTuple);
	PyTuple_SetItem(pData, 1, probTuple);

	pValue = PyObject_CallObject(pFunc, pData);
	if (pData != NULL)
	{
		Py_DECREF(pData);
	}

	if (m_showDeckstate) {
		plotDeckstate();
	}
}

void Plotter::plotDeckstate() {
	PyObject *pFunc, *pValue;
	PyObject* dmgTuple = PyTuple_New(damageVec.size());
	PyObject* deckTuple = PyTuple_New(probVec.size());

	pFunc = PyDict_GetItemString(pDict, "GraphDeckstate");
	if (!pFunc) {
		std::cout << "Get function GraphDeckstate failed" << std::endl;
		PyErr_Print();
		std::cin.get();
		return;
	}

	for (int i = 0; i < damageVec.size(); i++) {
		pValue = PyFloat_FromDouble(damageVec[i]);
		PyTuple_SetItem(dmgTuple, i, pValue);
	}
	for (int i = 0; i < compressionVec.size(); i++) {
		pValue = PyFloat_FromDouble(compressionVec[i]);
		PyTuple_SetItem(deckTuple, i, pValue);
	}

	PyObject* pData = PyTuple_New(2);
	PyTuple_SetItem(pData, 0, dmgTuple);
	PyTuple_SetItem(pData, 1, deckTuple);
	pValue = PyObject_CallObject(pFunc, pData);
	if (pData != NULL)
	{
		Py_DECREF(pData);
	}
}