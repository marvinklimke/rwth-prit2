// file:	Weg.h
// author:	Marvin Klimke
// date:	07.09.2016

#pragma once

#include <string>

#include "AktivesVO.h"

#include "LazyListe.h"

// Bekanntmachung der Klasse Fahrzeug.
class Fahrzeug;

// Diese Klasse bildet einen Weg, auf dem sich verschiedene Fahrzeuge befinden k�nnen, ab.
class Weg : public AktivesVO
{

public:

	// Geschwindigkeitslimit auf Wegen.
	typedef enum
	{
		Innerorts,   //  50km/h
		Landstrasse, // 100 km/h
		Autobahn     // unbegrenzt
	} Begrenzung;

	// Erstellt einen neuen Weg mit eindeutiger ID und leerem String als Namen.
	Weg();

	// Erstellt einen neuen Weg mit eindeutiger ID, einem Namen, einer L�nge und einer Geschwindigkeitsbegrenzung.
	Weg(const string sName, const double dLaenge, const Begrenzung eLimit = Autobahn);
	
	// Standard-Destruktor
	virtual ~Weg();

	// Die Abfertigungsfunktion fertigt alle Fahrzeuge auf dem Weg ab.
	virtual void vAbfertigung();

	// Diese Ausgabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual ostream& ostreamAusgabe(ostream& out) const;

	// Diese Funktion nimmt ein fahrendes Fahrzeug in die Liste seiner Fahrzeuge auf.
	void vAnnahme(Fahrzeug* pFahrzeug);

	// Diese Funktion nimmt ein parkendes Fahrzeug in die Liste seiner Fahrzeuge auf.
	void vAnnahme(Fahrzeug* pFahrzeug, const double dStartzeitpunkt);

	// Diese Funktion l�scht ein Fahrzeugzeiger aus der Liste der Fahrzeuge.
	void vAbgabe(Fahrzeug* pFahrzeug);

	// Getter f�r die L�nge des Weges.
	double getLaenge() const;

	// Getter f�r Geschwindigkeitslimit.
	Begrenzung getLimit() const;

private:

	// L�nge des Weges in Kilometern.
	double p_dLaenge;

	// Auflistung aller Fahrzeuge auf diesem Weg.
	LazyListe<Fahrzeug*> p_pFahrzeuge;

	// Geschwindigkeitsbegrenzung auf diesem Weg.
	Begrenzung p_eLimit;

};
