// file:	Fahrzeug.cpp
// author:	Marvin Klimke
// date:	26.08.2016

#include "Fahrzeug.h"

#include <iomanip>
#include <iostream>

using namespace std;

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug()
{
	vInitialisierung();

	// cout << "Fahrzeug #" << p_iID << " ohne Namen wurde erstellt." << endl;
}

Fahrzeug::Fahrzeug(const Fahrzeug& rhs)
{
	vInitialisierung(); // Zun�chst alles mit null initialisieren, neue ID vergeben
	p_sName = rhs.p_sName + " (K)";	// Namen ebenfalls �bernehmen, aber als Kopie markieren
	p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit; // Max. Geschwindigkeit �bernehmen
	/* Weitere Informationen zum Kopierkonstruktor: Siehe Ende von Datei Fahrzeug.h */
}

Fahrzeug::Fahrzeug(const string sName)
{
	vInitialisierung();
	p_sName = sName;

	// cout << "Fahrzeug #" << p_iID << " mit Namen " << p_sName << " wurde erstellt." << endl;
}

Fahrzeug::Fahrzeug(const string sName, const double dMaxGeschwindigkeit)
{
	vInitialisierung();
	p_sName = sName;
	p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;

	// cout << "Fahrzeug #" << p_iID << " mit Namen " << p_sName << " und max. Geschwindigkeit " << p_dMaxGeschwindigkeit << " wurde erstellt." << endl;
}

Fahrzeug::~Fahrzeug()
{
	// cout << "Fahrzeug #" << p_iID << " mit Namen " << p_sName << " wurde gel\224scht." << endl;
}

void Fahrzeug::vInitialisierung()
{
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dGesamtZeit = 0;
	p_dZeit = 0;
}

void Fahrzeug::vAusgabe() const
{
	cout << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << p_iID << " " // ID rechtsb�ndig
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(10) << p_sName << ": " // Name linksb�ndig
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_dMaxGeschwindigkeit << " " // Max. Geschwindigkeit rechtsb�ndig
		<< setw(10) << dGeschwindigkeit() << " " // aktuelle Geschwindigkeit rechtsb�ndig
		<< setw(12) << p_dGesamtStrecke; // Gesamtstrecke rechtsb�ndig
}

ostream& Fahrzeug::ostreamAusgabe(ostream& out) const
{
	out << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << p_iID << " " // ID rechtsb�ndig
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(10) << p_sName << ": " // Name linksb�ndig
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_dMaxGeschwindigkeit << " " // Max. Geschwindigkeit rechtsb�ndig
		<< setw(10) << dGeschwindigkeit() << " " // aktuelle Geschwindigkeit rechtsb�ndig
		<< setw(12) << p_dGesamtStrecke; // Gesamtstrecke rechtsb�ndig
	return out;
}

void Fahrzeug::vAbfertigung()
{
	if (!bEqual(dGlobaleZeit, p_dZeit)) // Abbruch, wenn das Fahrzeug bereits abgefertigt wurde
	{
		double delta_t = dGlobaleZeit - p_dZeit;

		p_dGesamtZeit += delta_t;
		p_dZeit = dGlobaleZeit;

		p_dGesamtStrecke += delta_t * dGeschwindigkeit();
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

Fahrzeug& Fahrzeug::operator = (const Fahrzeug& rhs)
{
	vInitialisierung(); // Zun�chst alles mit null initialisieren, neue ID vergeben
	p_sName = rhs.p_sName + " (K)";	// Namen ebenfalls �bernehmen, aber als Kopie markieren
	p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit; // Max. Geschwindigkeit �bernehmen
	return *this;
	/* Weitere Informationen zum Assignment-Operator: Siehe Ende von Datei Fahrzeug.h */
}

bool Fahrzeug::operator < (const Fahrzeug& rhs) const
{
	return (this->p_dGesamtStrecke < rhs.p_dGesamtStrecke);
}

void Fahrzeug::vHeaderAusgabe()
{
	cout << "ID Name      : MaxKmh     AktKmh    GesStrecke    GesVerbrauch  Tankinhalt" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

ostream& operator << (ostream& out, const Fahrzeug& fzg)
{
	return fzg.ostreamAusgabe(out);
}