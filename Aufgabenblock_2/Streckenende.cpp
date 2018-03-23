// file:	Streckenende.cpp
// author:	Marvin Klimke
// date:	12.09.2016

#include "Streckenende.h"

#include <iostream>

using namespace std;

Streckenende::Streckenende(Fahrzeug* pFahrzeug, Weg* pWeg)
	: FahrAusnahme(pFahrzeug, pWeg)
{
}

Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	cout << "Ausnahme Streckenende ist aufgetreten mit Fahrzeug und Weg:" << endl;
	cout << *p_pFahrzeug << endl << *p_pWeg << endl << endl;

	p_pWeg->vAbgabe(p_pFahrzeug);
}
