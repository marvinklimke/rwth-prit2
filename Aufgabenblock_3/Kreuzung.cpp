// file:	Kreuzung.cpp
// author:	Marvin Klimke
// date:	22.09.2016

#include "Kreuzung.h"
#include "Fahrzeug.h"

#include <iomanip>

#include <stdlib.h>

Kreuzung::Kreuzung()
	: AktivesVO()
{
}

Kreuzung::Kreuzung(string sName, const double dTankstelle)
	: AktivesVO(sName), p_dTankstelle(dTankstelle)
{
}

Kreuzung::~Kreuzung()
{
}

ostream& Kreuzung::ostreamAusgabe(ostream& out) const
{
	AktivesVO::ostreamAusgabe(out) << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(12) << p_dTankstelle // Tankstelleninhalt rechtsb�ndig
		<< resetiosflags(ios::right) << " ( ";

	for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
	{
		out << (*it)->getName() << " "; // Wege mit Namen benennen
	}
	out << ")";

	for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
	{
		out << endl << **it; // Wege ausf�hrlich ausgeben
	}

	return out;
}

istream& Kreuzung::istreamEingabe(istream& in)
{
	AktivesVO::istreamEingabe(in) >> p_dTankstelle;
	return in;
}

void Kreuzung::vVerbinde(Kreuzung* pZielKreuzung, const string sNameHin, const string sNameRuck, const double dLaenge, const Weg::Begrenzung eLimit, const bool bUeberholverbot)
{
	Weg *hin  = new Weg(sNameHin,  dLaenge, eLimit, bUeberholverbot);
	Weg *ruck = new Weg(sNameRuck, dLaenge, eLimit, bUeberholverbot);

	hin->setRuckweg(ruck);
	ruck->setRuckweg(hin);

	hin->setZielkreuzung(pZielKreuzung);
	ruck->setZielkreuzung(this);

	p_pWege.push_back(hin);
	pZielKreuzung->p_pWege.push_back(ruck);
}

void Kreuzung::vTanken(Fahrzeug* pFahrzeug)
{
	if (p_dTankstelle > 0)
	{
		double dMenge = pFahrzeug->dTanken();

		p_dTankstelle -= dMenge;

		if (p_dTankstelle < 0)
		{
			p_dTankstelle = 0;
		}
	}
}

void Kreuzung::vAnnahme(Fahrzeug* pFahrzeug, double dStartzeitpunkt)
{
	vTanken(pFahrzeug);

	Weg* pFirstWeg = p_pWege.front();
	pFirstWeg->vAnnahme(pFahrzeug, dStartzeitpunkt);
}

void Kreuzung::vAbfertigung()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
	{
		(*it)->vAbfertigung();
	}
}

Weg* Kreuzung::ptZufaelligerWeg(Weg* pWeg)
{
	Weg* pNeuerWeg = nullptr;

	if (p_pWege.size() == 1)
	{
		return p_pWege.front();
	}
	
	do
	{
		int iRnd = rand() % p_pWege.size();
		int i = 0;
		
		for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
		{
			if (i++ >= iRnd)
			{
				pNeuerWeg = *it;
				break;
			}
		}

	} while (pNeuerWeg == pWeg->getRuckweg());
	
	return pNeuerWeg;
}

void Kreuzung::vZeichnen() const
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
	{
		(*it)->vZeichnen();
	}
}

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}
