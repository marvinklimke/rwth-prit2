// file:	Weg.cpp
// author:	Marvin Klimke
// date:	07.09.2016

#include <iomanip>

#include "Weg.h"
#include "Fahrzeug.h"
#include "FahrAusnahme.h"


Weg::Weg()
	: AktivesVO(), p_dLaenge(0), p_eLimit(Autobahn), p_bUeberholverbot(true), p_pRuckweg(nullptr), p_pZielkreuzung(nullptr)
{
}

Weg::Weg(const string sName, const double dLaenge, const Begrenzung eLimit, const bool bUeberholverbot)
	: AktivesVO(sName), p_dLaenge(dLaenge), p_eLimit(eLimit), p_bUeberholverbot(bUeberholverbot), p_pRuckweg(nullptr), p_pZielkreuzung(nullptr)
{
}

Weg::~Weg()
{
}

void Weg::vAbfertigung()
{
	p_pFahrzeuge.vAktualisieren();
	p_dVirtuelleSchranke = p_dLaenge;

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
		out << (*it)->getName() << " "; // Fahrzeuge mit Namen benennen
	}
	out << ")";

	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it)
	{
		out << endl << **it; // Fahrzeuge ausf�hrlich ausgeben
	}

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

void Weg::vZeichnen() const
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it)
	{
		(*it)->vZeichnen(this);
	}
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

double Weg::getMaxGeschwindigkeit() const
{
	switch (p_eLimit)
	{
	case Innerorts: return 50;
	case Landstrasse: return 100;
	case Autobahn:
	default: return numeric_limits<double>::max();
	}
}

double Weg::getVirtuelleSchranke() const
{
	if (p_bUeberholverbot)
	{
		return p_dVirtuelleSchranke;
	}
	return p_dLaenge;
}

void Weg::setVirtuelleSchranke(double dVirtuelleSchranke)
{
	p_dVirtuelleSchranke = dVirtuelleSchranke;
}

Weg* Weg::getRuckweg() const
{
	return p_pRuckweg;
}

void Weg::setRuckweg(Weg* pRuckweg)
{
	p_pRuckweg = pRuckweg;
}

Kreuzung* Weg::getZielkreuzung() const
{
	return p_pZielkreuzung;
}

void Weg::setZielkreuzung(Kreuzung* pZielkreuzung)
{
	p_pZielkreuzung = pZielkreuzung;
}
