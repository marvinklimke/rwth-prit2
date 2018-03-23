// file:	Streckenende.cpp
// author:	Marvin Klimke
// date:	12.09.2016

#include "Streckenende.h"
#include "Kreuzung.h"

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
	Kreuzung* pKreuzung = p_pWeg->getZielkreuzung();
	p_pWeg->vAbgabe(p_pFahrzeug);
	
	if (pKreuzung != nullptr)
	{
		Weg* pNeuerWeg = pKreuzung->ptZufaelligerWeg(p_pWeg);
		pKreuzung->vTanken(p_pFahrzeug);
		pNeuerWeg->vAnnahme(p_pFahrzeug);
		
		cout << "ZEIT     : " << dGlobaleZeit << endl
			 << "KREUZUNG : " << pKreuzung->getName() << " " << pKreuzung->getTankstelle() << endl
			 << "WECHSEL  : " << p_pWeg->getName() << " => " << pNeuerWeg->getName() << endl
			 << "FAHRZEUG : " << *p_pFahrzeug << endl;
	}
	else
	{
		cout << "Streckenende ohne Zielkreuzung erreicht! Fahrzeug wird nicht umgesetzt." << endl;
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
