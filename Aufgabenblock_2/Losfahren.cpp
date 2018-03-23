// file:	Losfahren.cpp
// author:	Marvin Klimke
// date:	12.09.2016

#include "Losfahren.h"

#include <iostream>

using namespace std;

Losfahren::Losfahren(Fahrzeug* pFahrzeug, Weg* pWeg)
	: FahrAusnahme(pFahrzeug, pWeg)
{
}

Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	cout << "Ausnahme Losfahren ist aufgetreten mit Fahrzeug und Weg:" << endl;
	cout << *p_pFahrzeug << endl << *p_pWeg << endl << endl;

	p_pWeg->vAbgabe(p_pFahrzeug);
	p_pWeg->vAnnahme(p_pFahrzeug);
}
