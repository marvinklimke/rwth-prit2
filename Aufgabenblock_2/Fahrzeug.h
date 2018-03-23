// file:	Fahrzeug.h
// author:	Marvin Klimke
// date:	26.08.2016

#pragma once

#include "AktivesVO.h"
#include "FzgVerhalten.h"

extern double dGlobaleZeit;
extern bool bEqual(double x, double y);

class Weg;

// Die Fahrzeug-Klasse bildet ein generisches Fahrzeug ab.
class Fahrzeug : public AktivesVO
{

public:

	// Erstellt ein neues Fahrzeug mit eindeutiger ID und leeren String als Namen.
	Fahrzeug();

	// Kopier-Konstruktor. Erstellt ein neues Fahrzeug nach Vorlage der rhs.
	Fahrzeug(const Fahrzeug& rhs);

	// Erstellt ein neues Fahrzeug mit eindeutiger ID und einem Namen.
	Fahrzeug(const string sName);

	// Erstellt ein neues Fahrzeug mit eindeutiger ID, dem Namen und der maximalen Geschwindigkeit.
	Fahrzeug(const string sName, const double dMaxGeschwindigkeit);

	// Standard-Destruktor.
	virtual ~Fahrzeug();

	// Die Ausgabefunktion gibt fahrzeugspezifische Daten auf cout aus.
	virtual void vAusgabe() const;

	// Diese Ausgabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual ostream& ostreamAusgabe(ostream& out) const;

	// Die Abfertigungsfunktion l�sst Fahrzeuge anhand der globalen Uhr fahren.
	virtual void vAbfertigung();

	// Diese Funktion betankt ein Fahrzeug und gibt die tats�chlich getankte Menge zur�ck.
	virtual double dTanken(double dMenge = -1.0);

	// Diese Funktion gibt die aktuelle Geschwindigkeit des Fahrzeuges zur�ck.
	virtual double dGeschwindigkeit() const;

	// Diese Funktion erzeugt eine passende Instanz von FzgFahren f�r den jeweiligen Weg.
	void vNeueStrecke(Weg* pWeg);

	// Diese Funktion erzeugt eine passende Instanz von FzgParken f�r den jeweiligen Weg.
	void vNeueStrecke(Weg* pWeg, const double dStartzeitpunkt);

	// Diese Funktion zeichnet das Fahrzeug auf dem Simulationsserver.
	virtual void vZeichnen(Weg* pWeg) const;

	// Diese Operator�berladung erm�glicht das direkte Zuweisen eines Fahrzeuges (assign).
	Fahrzeug& operator = (const Fahrzeug& rhs);

	// Diese Operator�berladung erm�glicht den Vergleich zweier Fahrzeuge anhand der Gesamtfahrstrecke.
	bool operator < (const Fahrzeug& rhs) const;

	// Getter f�r die Strecke, die auf einem Wegabschnitt gefahren wurde.
	double getAbschnittStrecke() const;

	// Diese Funktion gibt einen Tabellenheader passend f�r die Ausgabefunktion aus.
	static void vHeaderAusgabe();

protected:

	// Maximale Geschwindigkeit, mit der das Fahrzeug fahren kann.
	double p_dMaxGeschwindigkeit;

	// Insgesamt vom Fahrzeug zur�ckgelegte Strecke.
	double p_dGesamtStrecke;

	// Gesamte Fahrzeit des Fahrzeugs.
	double p_dGesamtZeit;

	// Auf diesem Wegabschnitt vom Fahrzeug zur�ckgelegte Strecke.
	double p_dAbschnittStrecke;

	// Legt das Verhalten des Fahrzeuges auf einem bestimmten Weg fest.
	FzgVerhalten* p_pVerhalten;

private:

	// Initialisiert alle Membervariablen auf 0 bzw. "".
	void vInitialisierung();

};

/************************************************************************************/
/* ======== Informationen zum Kopierkonstruktor und dem Zuweisungsoperator ======== */
/* Der Kopierkonstruktor erstellt ein neues Fahrzeug mit eigenen (neuen) ID und     */
/* initialisierten Membervariablen, wovon nur der Name und die max. Geschwindigkeit */
/* vom urspr�nglichen Fahrzeug �bernommen werden. Denn die anderen Membervariablen  */
/* p_dGesamtStrecke, p_dGesamtZeit, p_dZeit sind sinnvollerweise null, da das       */
/* noch nicht abgefertigt wurde.                                                    */
/* Der Zuweisungsoperator wird �quivalent implementiert, sodass das Verhalten       */
/* unabh�ngig davon ist, ob intern der Kopierkonstruktor oder der Zuweisungsoperator*/
/* verwendet wurde. Es ist sichergestellt, dass jede ID absolut eindeutig ist.      */
/************************************************************************************/
