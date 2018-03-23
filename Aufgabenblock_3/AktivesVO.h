// file:	AktivesVO.h
// author:	Marvin Klimke
// date:	07.09.2016

#pragma once

#include <map>
#include <string>

using namespace std;

// Die AktivesVO-Klasse bildet ein aktives Verkehrsobjekt abstrakt ab.
class AktivesVO
{

public:

	// Erstellt ein neues Verkehrsobjekt mit eindeutiger ID und leerem String als Namen.
	AktivesVO();

	// Kopier-Konstruktor. Erstellt ein neues Verkehrsobjekt nach Vorlage der rhs.
	AktivesVO(const AktivesVO& rhs);

	// Erstellt ein neues Verkehrsobjekt mit eindeutiger ID und einem Namen.
	AktivesVO(const string sName);

	// Standard-Destruktor
	virtual ~AktivesVO();

	// Die Ausgabefunktion gibt die Daten des Verkehrsobjektes auf cout aus.
	virtual void vAusgabe() const;

	// Diese Ausgabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual ostream& ostreamAusgabe(ostream& out) const;

	// Diese Eingabefunktion bildet die Basis f�r die �berladung des Stream-Operators.
	virtual istream& istreamEingabe(istream& in);

	// Die Abfertigungsfunktion ist vollst�ndig virtuell und muss von den Subklassen �berschrieben werden.
	virtual void vAbfertigung() = 0;

	// Getter f�r den Namen des Verkehrsobjektes.
	string getName() const;

	// Diese Operator�berladung erm�glicht das direkte Zuweisen eines Verkehrsobjektes (assign).
	AktivesVO& operator = (const AktivesVO& rhs);

	// Diese Funktion liefert den Zeiger auf das Verkehrsobjekt mit dem Namen des Parameters.
	static AktivesVO* ptObjekt(string sName);

	// Diese Funktion l�scht alle Eintr�ge aus der STL-map, um eine neue Ausf�hrung zu erm�glichen.
	static void vClearMap();

protected:

	// Eindeutige ID des Verkehrsobjektes.
	int p_iID;

	// Name des Verkehrsobjektes.
	string p_sName;

	// Zeitpunkt der letzten Abfertigung.
	double p_dZeit;

private:

	// Aktuell h�chste vergebene ID eines Verkehrsobjektes.
	static int p_iMaxID;

	// Diese STL-map enth�lt Zeiger auf alle Verkehrsobjekte mit Namensindex.
	static map<string, AktivesVO*> VOMap;

	// Initialisiert alle Membervariablen auf 0 bzw. "" und vergibt eindeutige IDs.
	void vInitialisierung();

	// Legt den this-Zeiger in der map aller Verkehrsobjekte ab.
	void vRegister();

};

// Die Operator�berladung von << erlaubt die Ausgabe von Verkehrsobjekten �ber beliebige Streams.
ostream& operator << (ostream& out, const AktivesVO& vo);

// Die Operator�berladung von >> erlaubt das Einlesen von Verkehrsobjekten �ber beliebige Streams.
istream& operator >> (istream& in, AktivesVO& vo);
