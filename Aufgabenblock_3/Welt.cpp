// file:	Welt.cpp
// author:	Marvin Klimke
// date:	27.09.2016

#include "Welt.h"

#include "SimuClient.h"

#include "Fahrrad.h"
#include "Kreuzung.h"
#include "PKW.h"


Welt::Welt()
{
}

Welt::~Welt()
{
}

void Welt::vEinlesen(istream& in)
{
	while (!in.eof()) // Zeilen zu lesen
	{
		string sKey = "";
		in >> sKey;
		
		if (sKey == "KREUZUNG")
		{
			Kreuzung* cross = new Kreuzung();

			// Daten einlesen
			in >> *cross;

			p_pKreuzungen.push_back(cross);
		}
		else if (sKey == "STRASSE")
		{
			string sNameQ, sNameZ;
			string sNameW1, sNameW2;
			int iLaenge, iLimit, iUeberholverbot;
			Weg::Begrenzung eLimit;
			bool bUeberholverbot;

			// Daten einlesen
			in >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> iLaenge >> iLimit >> iUeberholverbot;

			switch (iLimit)
			{
			case 1: eLimit = Weg::Innerorts; break;
			case 2: eLimit = Weg::Landstrasse; break;
			case 3: eLimit = Weg::Autobahn; break;
			default: throw string("Begrenzung nicht eindeutig."); break;
			}

			switch (iUeberholverbot)
			{
			case 0: bUeberholverbot = false; break;
			case 1: bUeberholverbot = true;  break;
			default: throw string("Ueberholverbot nicht eindeutig."); break;
			}

			// Kreuzungen ausfindig machen
			Kreuzung* pQuell = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameQ));
			Kreuzung* pZiel = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameZ));

			if (pQuell == nullptr || pZiel == nullptr)
			{
				throw string("Die Kreuzungen k�nnen nicht verbunden werden.");
			}

			// Kreuzungen durch Stra�e verbinden
			pQuell->vVerbinde(pZiel, sNameW1, sNameW2, iLaenge, static_cast<Weg::Begrenzung>(eLimit), bUeberholverbot);
		}
		else if (sKey == "PKW")
		{
			PKW* car = new PKW();
			string sNameS;
			double dStartzeitpunkt;

			// Daten einlesen
			in >> *car >> sNameS >> dStartzeitpunkt;

			// Startkreuzung ausfindig machen
			Kreuzung* pStart = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameS));

			if (pStart == nullptr)
			{
				throw string("Der PKW kann nicht angenommen werden.");
			}

			// PKW durch Kreuzung annehmen
			pStart->vAnnahme(car, dStartzeitpunkt);
		}
		else if (sKey == "FAHRRAD")
		{
			Fahrrad* bike = new Fahrrad();
			string sNameS;
			double dStartzeitpunkt;

			// Daten einlesen
			in >> *bike >> sNameS >> dStartzeitpunkt;

			// Startkreuzung ausfindig machen
			Kreuzung* pStart = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameS));

			if (pStart == nullptr)
			{
				throw string("Das Fahrrad kann nicht angenommen werden.");
			}

			// Fahrrad durch Kreuzung annehmen
			pStart->vAnnahme(bike, dStartzeitpunkt);
		}
		else
		{
			throw string("Unbekannter Typ gelesen.");
		}
	}
}

void Welt::vEinlesenMitGrafik(istream & in)
{
	while (!in.eof()) // Zeilen zu lesen
	{
		string sKey = "";
		in >> sKey;

		if (sKey == "KREUZUNG")
		{
			Kreuzung* cross = new Kreuzung();
			int coordX, coordY;

			// Daten einlesen
			in >> *cross >> coordX >> coordY;

			bZeichneKreuzung(coordX, coordY);
			p_pKreuzungen.push_back(cross);
		}
		else if (sKey == "STRASSE")
		{
			string sNameQ, sNameZ;
			string sNameW1, sNameW2;
			int iLaenge, iLimit, iUeberholverbot, numPoints;
			Weg::Begrenzung eLimit;
			bool bUeberholverbot;

			// Daten einlesen
			in >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> iLaenge >> iLimit >> iUeberholverbot >> numPoints;

			switch (iLimit)
			{
			case 1: eLimit = Weg::Innerorts; break;
			case 2: eLimit = Weg::Landstrasse; break;
			case 3: eLimit = Weg::Autobahn; break;
			default: throw string("Begrenzung nicht eindeutig."); break;
			}

			switch (iUeberholverbot)
			{
			case 0: bUeberholverbot = false; break;
			case 1: bUeberholverbot = true;  break;
			default: throw string("Ueberholverbot nicht eindeutig."); break;
			}

			// Kreuzungen ausfindig machen
			Kreuzung* pQuell = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameQ));
			Kreuzung* pZiel = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameZ));

			if (pQuell == nullptr || pZiel == nullptr)
			{
				throw string("Die Kreuzungen k�nnen nicht verbunden werden.");
			}

			int *iCoords = new int[2 * numPoints]; // Array mit dynamischer Gr��e

			for (int i = 0; i < numPoints; i++)
			{
				in >> iCoords[2 * i] >> iCoords[2 * i + 1];
			}

			bZeichneStrasse(sNameW1, sNameW2, iLaenge, numPoints, iCoords);

			delete iCoords;

			// Kreuzungen durch Stra�e verbinden
			pQuell->vVerbinde(pZiel, sNameW1, sNameW2, iLaenge, static_cast<Weg::Begrenzung>(eLimit), bUeberholverbot);
		}
		else if (sKey == "PKW")
		{
			PKW* car = new PKW();
			string sNameS;
			double dStartzeitpunkt;

			// Daten einlesen
			in >> *car >> sNameS >> dStartzeitpunkt;

			// Startkreuzung ausfindig machen
			Kreuzung* pStart = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameS));

			if (pStart == nullptr)
			{
				throw string("Der PKW kann nicht angenommen werden.");
			}

			// PKW durch Kreuzung annehmen
			pStart->vAnnahme(car, dStartzeitpunkt);
		}
		else if (sKey == "FAHRRAD")
		{
			Fahrrad* bike = new Fahrrad();
			string sNameS;
			double dStartzeitpunkt;

			// Daten einlesen
			in >> *bike >> sNameS >> dStartzeitpunkt;

			// Startkreuzung ausfindig machen
			Kreuzung* pStart = dynamic_cast<Kreuzung*> (AktivesVO::ptObjekt(sNameS));

			if (pStart == nullptr)
			{
				throw string("Das Fahrrad kann nicht angenommen werden.");
			}

			// Fahrrad durch Kreuzung annehmen
			pStart->vAnnahme(bike, dStartzeitpunkt);
		}
		else
		{
			throw string("Unbekannter Typ gelesen.");
		}
	}
}

void Welt::vSimulation()
{
	for (auto it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); ++it)
	{
		(*it)->vAbfertigung();
	}
}

void Welt::vZeichnen()
{
	for (auto it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); ++it)
	{
		(*it)->vZeichnen();
	}
}

ostream& Welt::ostreamAusgabe(ostream& out) const
{
	for (auto it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); ++it)
	{
		out << **it << endl;
	}
	return out;
}

ostream& operator << (ostream& out, const Welt& w)
{
	return w.ostreamAusgabe(out);
}
