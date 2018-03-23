// file:	FzgParken.cpp
// author:	Marvin Klimke
// date:	09.09.2016

#include "FzgParken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

FzgParken::FzgParken(Weg* pWeg, double dStartzeitpunkt)
	: FzgVerhalten(pWeg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}


FzgParken::~FzgParken()
{
}

double FzgParken::dStrecke(Fahrzeug* pFahrzeug, double dZeit) const
{
	if (bEqual(dGlobaleZeit, p_dStartzeitpunkt) || dGlobaleZeit > p_dStartzeitpunkt)
	{
		throw Losfahren(pFahrzeug, p_pWeg); // Startzeit erreicht
	}
	else
	{
		return 0.0;
	}
}
