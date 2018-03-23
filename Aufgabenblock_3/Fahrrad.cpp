// file:	Fahrrad.cpp
// author:	Marvin Klimke
// date:	26.08.2016

#include "Fahrrad.h"


Fahrrad::Fahrrad()
	: Fahrzeug()
{
}

Fahrrad::Fahrrad(const string sName, const double dMaxGeschwindigkeit)
	: Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

Fahrrad::~Fahrrad()
{
}

double Fahrrad::dGeschwindigkeit() const
{
	// Anzahl voller 20km-Abschnitte
	int iFull20km = (int)(p_dGesamtStrecke / 20);

	// Verringerung der Geschwindigkeit um 10% mit jedem vollen 20km-Abschnitt
	// Also 0.9 zur Potenz der vollen 20km-Abschnitte mal die Maximalgeschwindigkeit
	double dSpeed = pow(0.9, iFull20km) * p_dMaxGeschwindigkeit;

	// Mindestens 12km/h beibehalten
	if (dSpeed < 12)
		dSpeed = 12;
	
	return dSpeed;
}
