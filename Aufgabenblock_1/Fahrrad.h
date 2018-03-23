// file:	Fahrrad.h
// author:	Marvin Klimke
// date:	26.08.2016

#pragma once

#include "Fahrzeug.h"

// Die Fahrrad-Klasse bildet ein manuell angetriebenes Fahrrad ab. Abgeleitet von Fahrzeug.
class Fahrrad :	public Fahrzeug
{

public:

	// Erstellt ein neues Fahrrad mit eindeutiger ID.
	Fahrrad();

	// Erstellt ein neues Fahrrad mit eindeutiger ID, dem Namen und der maximalen Geschwindigkeit.
	Fahrrad(const string sName, const double dMaxGeschwindigkeit);

	// Standard-Destruktor.
	virtual ~Fahrrad();

	// Diese Funktion bestimmt die aktuelle Geschwindigkeit auf Basis der bereits gefahrenen Strecke.
	virtual double dGeschwindigkeit() const;

};

