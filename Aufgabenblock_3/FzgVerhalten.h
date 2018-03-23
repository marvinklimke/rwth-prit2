// file:	FzgVerhalten.h
// author:	Marvin Klimke
// date:	08.09.2016

#pragma once

#include "Weg.h"

// Diese Klasse stellt das Verhalten eines Fahrzeuges auf einem Weg dar.
class FzgVerhalten
{

public:
	
	// Erstellt eine Instanz und speichert einen Zeiger auf einen Weg.
	FzgVerhalten(Weg* pWeg);

	// Standard-Destruktor.
	virtual ~FzgVerhalten();

	// Diese Funktion berechnet die maximal m�gliche Fahrstrecke f�r das Fahrzeug auf dem jeweiligen Weg.
	virtual double dStrecke(Fahrzeug* pFahrzeug, double dZeit) const = 0;

	// Getter f�r den Weg-Zeiger.
	Weg* getWeg() const;

protected:

	// Zeiger auf eine Weg-Instanz von dem das FzgVerhalten abh�ngt.
	Weg* p_pWeg;

};

