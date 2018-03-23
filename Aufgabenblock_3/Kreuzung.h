// file:	Kreuzung.h
// author:	Marvin Klimke
// date:	22.09.2016

#pragma once

#include <list>

#include "AktivesVO.h"
#include "Weg.h"


class Kreuzung : public AktivesVO
{

public:

	// Erstellt eine neue Kreuzung mit eindeutiger ID.
	Kreuzung();

	// Erstellt eine neue Kreuzung mit eindeutiger ID und einem Namen.
	Kreuzung(string sName, const double dTankstelle = 0);

	// Standard-Destruktor.
	virtual ~Kreuzung();

	// Diese Ausgabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual ostream& ostreamAusgabe(ostream& out) const;

	// Diese Eingabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual istream& istreamEingabe(istream& in);

	// Diese Methode verbindet zwei Kreuzungen unter Angabe aller relevanten Daten.
	void vVerbinde(Kreuzung* pZielKreuzung, const string sNameHin, const string sNameRuck, const double dLaenge, const Weg::Begrenzung eLimit, const bool bUeberholverbot);

	// Diese Methode tankt ein Fahrzeug voll, wenn der Inhalt der Tankstelle ausreicht.
	void vTanken(Fahrzeug* pFahrzeug);

	// Diese Methode stellt Fahrzeuge parkend auf dem ersten abgehenden Weg ab.
	void vAnnahme(Fahrzeug* pFahrzeug, double dStartzeitpunkt);

	// Diese Methode fertigt alle abgehenden Wege ab.
	void vAbfertigung();

	// Diese Methode liefert einen Zeiger auf einen zuf�lligen Weg zur�ck, der nicht der R�ckweg ist.
	Weg* ptZufaelligerWeg(Weg* pWeg);

	// Diese Methode zeichnet alle abgehenden Wege und folglich alle Fahrzeuge.
	void vZeichnen() const;

	// Getter f�r den Inhalt der Tankstelle.
	double getTankstelle() const;

private:

	// Menge in Litern, die zum Betanken der Fahrzeuge zur Verf�gung steht.
	double p_dTankstelle;

	// Liste der Zeiger der von dieser Kreuzung wegf�hrenden Wege.
	list<Weg*> p_pWege;

};

