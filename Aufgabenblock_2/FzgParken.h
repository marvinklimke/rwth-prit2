// file:	FzgParken.h
// author:	Marvin Klimke
// date:	09.09.2016

#pragma once

#include "FzgVerhalten.h"

// Diese Klasse stellt das Verhalten eines parkenden Fahrzeuges dar.
class FzgParken : public FzgVerhalten
{

public:

	// Erzeugt eine Instanz, speichert einen Zeiger auf einen Weg und den Startzeitpunkt.
	FzgParken(Weg* pWeg, double dStartzeitpunkt);

	// Standard-Destruktor.
	virtual ~FzgParken();

	// Diese Funktion berechnet die maximal m�gliche Fahrstrecke f�r das Fahrzeug auf dem jeweiligen Weg.
	virtual double dStrecke(Fahrzeug* pFahrzeug, double dZeit) const;

private:

	// Zeitpunkt, zu dem das pakende Fahrzeug losfahren soll.
	double p_dStartzeitpunkt;

};

