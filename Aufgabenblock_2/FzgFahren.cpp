// file:	FzgFahren.cpp
// author:	Marvin Klimke
// date:	09.09.2016

#include <algorithm>

#include "FzgFahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"


FzgFahren::FzgFahren(Weg* pWeg)
	: FzgVerhalten(pWeg)
{
}

FzgFahren::~FzgFahren()
{
}

double FzgFahren::dStrecke(Fahrzeug* pFahrzeug, double dZeit) const
{
	// Strecke bis der Weg endet
	double dStreckeWegende = p_pWeg->getLaenge() - pFahrzeug->getAbschnittStrecke();

	// Strecke die das Fahrzeug mit normaler Geschwindigkeit zur�cklegen w�rde
	double dStreckeGeschwindigkeit = pFahrzeug->dGeschwindigkeit() * dZeit;

	if (bEqual(dStreckeWegende, 0.0))
	{
		throw Streckenende(pFahrzeug, p_pWeg); // Streckenende erreicht
	}

	// Der kleinere Wert ist ma�gebend
	return min<double>(dStreckeWegende, dStreckeGeschwindigkeit);
}