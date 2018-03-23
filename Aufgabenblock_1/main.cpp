// file:	main.cpp
// author:	Marvin Klimke
// date:	26.08.2016

#include <iostream>
#include <map>
#include <vector>

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "PKW.h"

// Vergleichsfunktion f�r zwei double-Werte mit Fehlertoleranz.
inline bool bEqual(double x, double y)
{
	return (fabs(x - y) < 1e-6);
}

// "Globale Uhr"
double dGlobaleZeit = 0.0;

// Aufgabenstellung 1 aus Block 1
void vAufgabe_1()
{
	Fahrzeug *fz1 = new Fahrzeug("Auto", 60);
	Fahrzeug fz2("Motorwagen", 20);
	
	string sName = "";
	cout << "Bitte geben Sie den Namen Ihres Fahrzeuges ein: ";
	cin >> sName;

	Fahrzeug *fz3 = new Fahrzeug(sName, 42.4);
	Fahrzeug fz4;

	double dInterval = 0.0;
	cout << "Bitte geben Sie das Abfertigungsinterval ein: ";
	cin >> dInterval;
	cout << endl;

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 5; dGlobaleZeit += dInterval)
	{
		fz1->vAbfertigung();
		fz2.vAbfertigung();
		fz3->vAbfertigung();
		fz4.vAbfertigung();
		cout << "GlobaleZeit = " << dGlobaleZeit << endl;
		fz1->vAusgabe(); cout << endl;
		fz2.vAusgabe(); cout << endl;
		fz3->vAusgabe(); cout << endl;
		fz4.vAusgabe(); cout << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	delete fz1;
	delete fz3;
}

// Aufgabenstellung 1 mit Debugger aus Block 1
void vAufgabe_1_deb()
{
	Fahrzeug* pFahrzeuge[4];

	pFahrzeuge[0] = new Fahrzeug("Moped", 50);
	pFahrzeuge[1] = new Fahrzeug("Tesla", 80);
	pFahrzeuge[2] = new Fahrzeug("E-Bike", 25);
	pFahrzeuge[3] = new Fahrzeug("Roller", 45);

	Fahrzeug::vHeaderAusgabe();
	for (int i = 0; i < 4; i++)
	{
		pFahrzeuge[i]->vAusgabe();
		cout << endl;
	}

	// Manipuliere den Zeiger
	pFahrzeuge[2] = 0;

	Fahrzeug::vHeaderAusgabe();
	for (int i = 0; i < 4; i++)
	{
		pFahrzeuge[i]->vAusgabe();
		cout << endl;
		delete pFahrzeuge[i];
	}
}

// Aufgabenstellung 2 aus Block 1
void vAufgabe_2()
{
	int iNumPKW = 0;
	int iNumFahrrad = 0;

	cout << "Wie viele PKWs sollen erzeugt werden? ";
	cin >> iNumPKW;
	cout << "Wie viele Fahrr\204der sollen erzeugt werden? ";
	cin >> iNumFahrrad;

	vector<Fahrzeug*> vecFahrzeuge;

	// PKWs erzeugen
	for (int i = 1; i <= iNumPKW; i++)
	{
		PKW *pkwTemp = new PKW("AUTO " + to_string(i), 60, 5);
		vecFahrzeuge.push_back(pkwTemp);
	}

	// Fahrr�der erzeugen
	for (int i = 1; i <= iNumFahrrad; i++)
	{
		Fahrrad *frdTemp = new Fahrrad("FAHRRAD " + to_string(i), 24);
		vecFahrzeuge.push_back(frdTemp);
	}

	double dInterval = 0.0;
	cout << "Bitte geben Sie das Abfertigungsinterval ein: ";
	cin >> dInterval;
	cout << endl;

	bool bGetankt = false;
	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dInterval)
	{
		// vector<Fahrzeug*>::iterator it;
		for (auto it = vecFahrzeuge.begin(); it != vecFahrzeuge.end(); it++)
		{
			if ( (bEqual(dGlobaleZeit, 3.0) || dGlobaleZeit > 3.0) && !bGetankt )
			{
				(*it)->dTanken();	// Zum Zeitpunkt 3:00 Autos nachtanken
				bGetankt = true;
			}
			
			(*it)->vAbfertigung();	// Fahrzeuge fahren lassen
			(*it)->vAusgabe();		// Fahrzeugdaten ausgeben
			cout << endl;
		}

		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	// vector<Fahrzeug*>::iterator it;
	for (auto it = vecFahrzeuge.begin(); it != vecFahrzeuge.end(); it++)
	{
		delete *it; // Dynamische Objekte l�schen
	}
}

// Aufgabenstellung 3 aus Block 1
void vAufgabe_3()
{
	PKW car("Golf", 60, 5);
	Fahrrad bike("Cube", 24);
	Fahrzeug boat("Tanker", 15);

	// Ein wenig fahren
	dGlobaleZeit += 2.5;
	car.vAbfertigung();
	bike.vAbfertigung();
	boat.vAbfertigung();

	// Alles ausgeben
	Fahrzeug::vHeaderAusgabe();
	cout << car << endl << bike << endl << boat << endl << endl;

	// Vergleichsoperator testen
	if (bike < boat)
	{
		cout << "Das Schiff ist bereits weiter gefahren." << endl << endl;
	}
	else
	{
		cout << "Das Fahrrad ist bereits weiter gefahren." << endl << endl;
	}

	// Kopiermechanismen testen
	PKW carcopy1;
	PKW carcopy2 = car;	// mit Kopierkonstruktor
	carcopy1 = car;		// mit Zuweisungsoperator

	Fahrzeug::vHeaderAusgabe();
	cout << carcopy1 << endl << carcopy2 << endl;
}

// Typedef f�r Funktionspointer auf eine Aufgabe
typedef void(*aufgabe_t)();

// Hauptprogramm
int main(void)
{
	// STL-Map mit allen Aufgaben als Funktionspointer
	map<string, aufgabe_t> aufgaben;
	aufgaben["1"] = vAufgabe_1;
	aufgaben["1d"] = vAufgabe_1_deb;
	aufgaben["2"] = vAufgabe_2;
	aufgaben["3"] = vAufgabe_3;

	string sChoose = "";
	do
	{
		cout << "Praktikum Informatik II (WS2016) - Strassenverkehr Block 1 - Marvin Klimke" << endl;
		cout << "Bitte w\204hlen Sie das K\201rzel der Aufgabe, die Sie ausf\201hren m\224chten:" << endl;
		cout << "1  : vAufgabe_1()" << endl
			 << "1d : vAufgabe_1_deb()" << endl
			 << "2  : vAufgabe_2()" << endl
			 << "3  : vAufgabe_3()" << endl
			 << "e  : Programm beenden." << endl;

		cin >> sChoose;
		cout << endl;

		auto it = aufgaben.find(sChoose);

		if (it != aufgaben.end())
		{
			(*it->second)(); // Funktionspointer aufrufen
		}
		else if(sChoose != "e")
		{
			cout << "Eingabe konnte nicht zugeordnet werden." << endl;
		}
		cout << endl;

	} while (sChoose != "e");

	return 0;
}
