// file:	Fahrzeug.cpp
// author:	Marvin Klimke
// date:	26.08.2016

#include <iomanip>
#include <iostream>

#include "Fahrzeug.h"
#include "FzgFahren.h"
#include "FzgParken.h"
#include "Weg.h"
#include "SimuClient.h"

using namespace std;


Fahrzeug::Fahrzeug()
	: AktivesVO()
{
	vInitialisierung();
}

Fahrzeug::Fahrzeug(const Fahrzeug& rhs)
	: AktivesVO(rhs)
{
	vInitialisierung(); // Zun�chst alles mit null initialisieren
	p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit; // Max. Geschwindigkeit �bernehmen
	p_pVerhalten = rhs.p_pVerhalten; // Zeige auf Verhalten von rhs
	/* Weitere Informationen zum Kopierkonstruktor: Siehe Ende von Datei Fahrzeug.h */
}

Fahrzeug::Fahrzeug(const string sName)
	: AktivesVO(sName)
{
	vInitialisierung();
}

Fahrzeug::Fahrzeug(const string sName, const double dMaxGeschwindigkeit)
	: AktivesVO(sName)
{
	vInitialisierung();
	p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;
}

Fahrzeug::~Fahrzeug()
{
	delete p_pVerhalten;
}

void Fahrzeug::vInitialisierung()
{
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dGesamtZeit = 0;
	p_dAbschnittStrecke = 0;
	p_pVerhalten = nullptr;
}

void Fahrzeug::vAusgabe() const
{
	AktivesVO::vAusgabe();
	cout << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) // rechtsb�ndig
		<< setw(12) << p_dGesamtStrecke << " "
		<< setw(12) << p_dAbschnittStrecke << " "
		<< setw(8) << p_dMaxGeschwindigkeit << " "
		<< setw(8) << dGeschwindigkeit();
}

ostream& Fahrzeug::ostreamAusgabe(ostream& out) const
{
	AktivesVO::ostreamAusgabe(out) << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) // rechtsb�ndig
		<< setw(12) << p_dGesamtStrecke << " "
		<< setw(12) << p_dAbschnittStrecke << " "
		<< setw(8) << p_dMaxGeschwindigkeit << " "
		<< setw(8) << dGeschwindigkeit();
	return out;
}

void Fahrzeug::vAbfertigung()
{
	if (!bEqual(dGlobaleZeit, p_dZeit)) // Abbruch, wenn das Fahrzeug bereits abgefertigt wurde
	{
		double delta_t = dGlobaleZeit - p_dZeit;

		p_dGesamtZeit += delta_t;
		p_dZeit = dGlobaleZeit;

		double dStrecke = p_pVerhalten->dStrecke(this, delta_t);

		p_dAbschnittStrecke += dStrecke;
		p_dGesamtStrecke += dStrecke;
	}
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg* pWeg)
{
	delete p_pVerhalten; // Speicherlecks vermeiden

	p_pVerhalten = new FzgFahren(pWeg);
	p_dAbschnittStrecke = 0;
}

void Fahrzeug::vNeueStrecke(Weg* pWeg, const double dStartzeitpunkt)
{
	delete p_pVerhalten; // Speicherlecks vermeiden

	p_pVerhalten = new FzgParken(pWeg, dStartzeitpunkt);
	p_dAbschnittStrecke = 0;
}

void Fahrzeug::vZeichnen(Weg* pWeg) const
{
	double dRelPos = p_dAbschnittStrecke / pWeg->getLaenge();

	if (dRelPos < 0) dRelPos = 0;
	if (dRelPos > 1) dRelPos = 1;

	bZeichneFahrrad(p_sName, pWeg->getName(), dRelPos, dGeschwindigkeit());
}

Fahrzeug& Fahrzeug::operator = (const Fahrzeug& rhs)
{
	AktivesVO::operator=(rhs); // Superklasse vergibt eindeutige ID
	vInitialisierung(); // Zun�chst alles mit null initialisieren
	p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit; // Max. Geschwindigkeit �bernehmen
	p_pVerhalten = rhs.p_pVerhalten; // Zeige auf Verhalten von rhs
	return *this;
	/* Weitere Informationen zum Assignment-Operator: Siehe Ende von Datei Fahrzeug.h */
}

bool Fahrzeug::operator < (const Fahrzeug& rhs) const
{
	return (this->p_dGesamtStrecke < rhs.p_dGesamtStrecke);
}

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vHeaderAusgabe()
{
	cout << "ID Name      :  GesStrecke   AbsStrecke   MaxKmh   AktKmh  : GesVerbrauch  Tankinhalt " << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
