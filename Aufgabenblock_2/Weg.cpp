// file:	Weg.cpp
// author:	Marvin Klimke
// date:	07.09.2016

#include <iomanip>

#include "Weg.h"
#include "Fahrzeug.h"
#include "FahrAusnahme.h"


Weg::Weg()
	: AktivesVO()
{
}

Weg::Weg(const string sName, const double dLaenge, const Begrenzung eLimit)
	: AktivesVO(sName), p_dLaenge(dLaenge), p_eLimit(eLimit)
{
}

Weg::~Weg()
{
}

void Weg::vAbfertigung()
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it)
	{
		try
		{
			(*it)->vAbfertigung();
		}
		catch (FahrAusnahme& e)
		{
			e.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();
	p_dZeit = dGlobaleZeit;
}

ostream& Weg::ostreamAusgabe(ostream& out) const
{
	AktivesVO::ostreamAusgabe(out) << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(12) << p_dLaenge // L�nge rechtsb�ndig
		<< resetiosflags(ios::right) << " ( ";

	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it)
	{
		out << (*it)->getName() << " ";
	}
	out << ")";
	return out;
}

void Weg::vAnnahme(Fahrzeug* pFahrzeug)
{
	pFahrzeug->vNeueStrecke(this);
	p_pFahrzeuge.push_back(pFahrzeug);
}

void Weg::vAnnahme(Fahrzeug* pFahrzeug, const double dStartzeitpunkt)
{
	pFahrzeug->vNeueStrecke(this, dStartzeitpunkt);
	p_pFahrzeuge.push_front(pFahrzeug);
}

void Weg::vAbgabe(Fahrzeug* pFahrzeug)
{
	auto it = find(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), pFahrzeug);
	
	if (it != p_pFahrzeuge.end()) // gefunden ?
	{
		p_pFahrzeuge.erase(it);
	}
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

Weg::Begrenzung Weg::getLimit() const
{
	return p_eLimit;
}
