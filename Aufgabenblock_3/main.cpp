// file:	main.cpp
// author:	Marvin Klimke
// date:	26.08.2016

#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "SimuClient.h"

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "LazyListe.h"
#include "PKW.h"
#include "Weg.h"
#include "Welt.h"


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
			if ((bEqual(dGlobaleZeit, 3.0) || dGlobaleZeit > 3.0) && !bGetankt)
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

// Aufgabenstellung 4 aus Block 2
void vAufgabe_4()
{
	PKW car("Golf", 60, 5);
	Fahrrad bike("Cube", 24);
	Weg road("Ahornstr", 50, Weg::Innerorts);

	road.vAnnahme(&car);
	road.vAnnahme(&bike, 1.0);

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 2; dGlobaleZeit += 0.1)
	{
		road.vAbfertigung();
		cout << car << endl << bike << endl << road << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
}

// Aufgabenstellung 5 aus Block 2
void vAufgabe_5()
{
	Weg hin("B229-West", 500, Weg::Landstrasse);
	Weg ruck("B229-Ost", 500, Weg::Landstrasse);

	PKW car1("Tesla", 120, 4);
	PKW car2("BMW", 160, 8);
	Fahrrad bike1("Stevens", 26);
	Fahrrad bike2("Haibike", 24);

	hin.vAnnahme(&car1);
	hin.vAnnahme(&bike2, 1.4);
	ruck.vAnnahme(&car2, 3.0);
	ruck.vAnnahme(&bike1);

	if (!bInitialisiereGrafik(800, 600))
	{
		cerr << "Fehler beim Starten des Simulationsservers." << endl;
	}

	int iCoords[] = { 100, 200, 700, 400 };
	bZeichneStrasse(hin.getName(), ruck.getName(), 500, 2, iCoords);

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.25)
	{
		hin.vAbfertigung();
		ruck.vAbfertigung();

		vSetzeZeit(dGlobaleZeit);

		car1.vZeichnen(&hin);
		car2.vZeichnen(&ruck);
		bike1.vZeichnen(&ruck);
		bike2.vZeichnen(&hin);

		cout << car1 << endl << car2 << endl << bike1 << endl << bike2 << endl << hin << endl << ruck << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		vSleep(500);
	}

	vBeendeGrafik();
}

// Aufgabenstellung 6 aus Block 2
void vAufgabe_6()
{
	Weg hin("B229-West", 500, Weg::Landstrasse);
	Weg ruck("B229-Ost", 500, Weg::Landstrasse);

	PKW car1("Tesla", 120, 4);
	PKW car2("BMW", 160, 8);
	Fahrrad bike1("Stevens", 26);
	Fahrrad bike2("Haibike", 24);

	hin.vAnnahme(&car1);
	hin.vAnnahme(&bike2, 1.4);
	ruck.vAnnahme(&car2, 1.2);
	ruck.vAnnahme(&bike1);

	if (!bInitialisiereGrafik(800, 600))
	{
		cerr << "Fehler beim Starten des Simulationsservers." << endl;
	}

	int iCoords[] = { 100, 200, 700, 400 };
	bZeichneStrasse(hin.getName(), ruck.getName(), 500, 2, iCoords);

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.25)
	{
		hin.vAbfertigung();
		ruck.vAbfertigung();

		vSetzeZeit(dGlobaleZeit);

		car1.vZeichnen(&hin);
		car2.vZeichnen(&ruck);
		bike1.vZeichnen(&ruck);
		bike2.vZeichnen(&hin);

		cout << car1 << endl << car2 << endl << bike1 << endl << bike2 << endl << hin << endl << ruck << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		vSleep(500);
	}

	vBeendeGrafik();
}

// Ausgabefunktion f�r LazyListe
void vAusgabeLazyListe(LazyListe<int>& tListe)
{
	for (auto it = tListe.begin(); it != tListe.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl << endl;
}

// Aufgabenstellung 6a aus Block 2
void vAufgabe_6a()
{
	LazyListe<int> Liste;

	for (int i = 0; i < 10; i++)
	{
		Liste.push_back(rand() % 10 + 1);
	}
	Liste.vAktualisieren();

	cout << "Erste Ausgabe (komplett):" << endl;
	vAusgabeLazyListe(Liste);

	cout << "Entferne alle Zahlen groesser 5." << endl << endl;
	for (auto it = Liste.begin(); it != Liste.end(); ++it)
	{
		if (*it > 5)
		{
			Liste.erase(it);
		}
	}

	cout << "Zweite Ausgabe (ohne Aktualisierung):" << endl;
	vAusgabeLazyListe(Liste);

	cout << "Aktualiere die Liste." << endl << endl;
	Liste.vAktualisieren();

	cout << "Dritte Ausgabe (nach Aktualisierung):" << endl;
	vAusgabeLazyListe(Liste);

	cout << "F\201ge 8 am Anfang und 12 am Ende ein." << endl << endl;
	Liste.push_front(8);
	Liste.push_back(12);
	Liste.vAktualisieren();

	cout << "Vierte Ausgabe (mit neuen Zahlen am Anfang/Ende):" << endl;
	vAusgabeLazyListe(Liste);
}

// Aufgabenstellung 7 aus Block 3
void vAufgabe_7()
{
	Weg road1("Allee-W", 120, Weg::Innerorts);
	Weg road2("Allee-O", 120, Weg::Innerorts);

	PKW car("Golf", 120, 7, 12);
	Fahrrad bike("Stevens", 24);
	Fahrrad velo("Cube", 26);

	road1.vAnnahme(&bike, 0.5);
	road1.vAnnahme(&car, 1.6);
	
	if (!bInitialisiereGrafik(800, 600))
	{
		cerr << "Fehler beim Starten des Simulationsservers." << endl;
	}

	int iCoords[] = { 100, 300, 700, 300 };
	bZeichneStrasse(road1.getName(), road2.getName(), 120, 2, iCoords);

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.1)
	{
		if (bEqual(dGlobaleZeit, 3))
		{
			road1.vAnnahme(&velo, dGlobaleZeit);
		}

		road1.vAbfertigung();

		vSetzeZeit(dGlobaleZeit);

		car.vZeichnen(&road1);
		bike.vZeichnen(&road1);
		velo.vZeichnen(&road1);

		cout << car << endl << bike << endl << velo << endl << road1 << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		vSleep(100);
	}

	vBeendeGrafik();
}

// Aufgabenstellung 8 aus Block 3
void vAufgabe_8()
{
	Kreuzung Kr1("Kr1");
	Kreuzung Kr2("Kr2", 1000);
	Kreuzung Kr3("Kr3");
	Kreuzung Kr4("Kr4");

	PKW car1("Tesla", 120, 4);
	PKW car2("Golf", 140, 6);
	Fahrrad bike1("Stevens", 26);
	Fahrrad bike2("Haibike", 24);

	Kr1.vVerbinde(&Kr2, "W12", "W21", 40, Weg::Innerorts, true);		// Stra�e 1
	Kr2.vVerbinde(&Kr3, "W23a", "W32a", 115, Weg::Autobahn, false);		// Stra�e 2
	Kr2.vVerbinde(&Kr3, "W23b", "W32b", 40, Weg::Innerorts, true);		// Stra�e 3
	Kr2.vVerbinde(&Kr4, "W24", "W42", 55, Weg::Innerorts, true);		// Stra�e 4
	Kr3.vVerbinde(&Kr4, "W34", "W43", 85, Weg::Autobahn, false);		// Stra�e 5
	Kr4.vVerbinde(&Kr4, "W44a", "W44b", 130, Weg::Landstrasse, false);	// Stra�e 6

	Kr1.vAnnahme(&car1, 1.2);
	Kr1.vAnnahme(&car2, 2.6);
	Kr1.vAnnahme(&bike1, 0.4);
	Kr1.vAnnahme(&bike2, 1.8);

	if (!bInitialisiereGrafik(1200, 800))
	{
		cerr << "Fehler beim Starten des Simulationsservers." << endl;
	}

	int iCoords1[] = { 680,  40, 680, 300 };
	int iCoords2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int iCoords3[] = { 680, 300, 680, 570 };
	int iCoords4[] = { 680, 300, 320, 300 };
	int iCoords5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int iCoords6[] = { 320, 300, 320, 150, 200,  60,  80,  90,  70, 250, 170, 300, 320, 300 };

	bZeichneStrasse("W12",  "W21",   40, 2, iCoords1);
	bZeichneStrasse("W23a", "W32a", 115, 6, iCoords2);
	bZeichneStrasse("W23b", "W32b",  40, 2, iCoords3);
	bZeichneStrasse("W24",  "W42",   55, 2, iCoords4);
	bZeichneStrasse("W34",  "W43",   85, 5, iCoords5);
	bZeichneStrasse("W44a", "W44b", 130, 7, iCoords6);

	bZeichneKreuzung(680,  40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	Fahrzeug::vHeaderAusgabe();
	for (dGlobaleZeit = 0; dGlobaleZeit < 12; dGlobaleZeit += 0.1)
	{
		vSetzeZeit(dGlobaleZeit);

		Kr1.vAbfertigung();
		Kr2.vAbfertigung();
		Kr3.vAbfertigung();
		Kr4.vAbfertigung();

		Kr1.vZeichnen();
		Kr2.vZeichnen();
		Kr3.vZeichnen();
		Kr4.vZeichnen();
		
		cout << car1 << endl << car2 << endl << bike1 << endl << bike2 << endl << Kr1 << endl << Kr2 << endl << Kr3 << endl << Kr4 << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		vSleep(100);
	}

	vBeendeGrafik();
}

// Aufgabenstellung 9 aus Block 3
void vAufgabe_9a()
{
	ifstream fsInput("VO.dat");

	if (!fsInput)
	{
		cerr << "VO.dat konnte nicht ge�ffnet werden." << endl;
		exit(1);
	}

	PKW car;
	Fahrrad bike;
	Kreuzung cross;

	fsInput >> car >> bike >> cross;

	fsInput.close();

	Fahrzeug::vHeaderAusgabe();
	cout << car << endl << bike << endl << cross << endl << endl;
	
	try
	{
		string sName = "";
		
		cout << "Bitte geben Sie den Namen des zu suchenden Verkehrsobjektes ein: ";
		cin >> sName;
		AktivesVO* ptVO = AktivesVO::ptObjekt(sName);
		cout << "Pointer: " << ptVO << endl << *ptVO << endl;

		cout << "Bitte geben Sie den Namen des zu erstellenden Verkehrsobjektes ein: ";
		cin >> sName;
		Fahrrad velo(sName, 24);
		cout << velo << endl;
	}
	catch (string &e)
	{
		cerr << "caught: " << e << endl;
	}
}

// Aufgabenstellung 9 aus Block 3
void vAufgabe_9b()
{
	ifstream fsInput("Simu.dat");

	if (!fsInput)
	{
		cerr << "Simu.dat konnte nicht ge�ffnet werden." << endl;
		exit(1);
	}

	Welt earth;

	try
	{
		earth.vEinlesen(fsInput);
	}
	catch (string &e)
	{
		cerr << "caught: " << e << endl;
	}

	earth.vSimulation();

	Fahrzeug::vHeaderAusgabe();
	cout << earth << endl;

	fsInput.close();
}

// Aufgabenstellung 9 aus Block 3
void vAufgabe_9c()
{
	ifstream fsInput("SimuDisplay.dat");

	if (!fsInput)
	{
		cerr << "SimuDisplay.dat konnte nicht ge�ffnet werden." << endl;
		exit(1);
	}

	if (!bInitialisiereGrafik(1200, 1000))
	{
		cerr << "Der Simulationsserver konnte nicht gestartet werden." << endl;
		exit(2);
	}

	Welt earth;

	try
	{
		earth.vEinlesenMitGrafik(fsInput);
	}
	catch (string &e)
	{
		cerr << "caught: " << e << endl;
	}

	fsInput.close();

	const double dInterval = 0.05;

	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dInterval)
	{
		vSetzeZeit(dGlobaleZeit);
		
		earth.vSimulation();
		earth.vZeichnen();

		// Fahrzeug::vHeaderAusgabe();
		// cout << earth << endl << endl;

		vSleep(10);
	}

	vBeendeGrafik();
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
	aufgaben["4"] = vAufgabe_4;
	aufgaben["5"] = vAufgabe_5;
	aufgaben["6"] = vAufgabe_6;
	aufgaben["6a"] = vAufgabe_6a;
	aufgaben["7"] = vAufgabe_7;
	aufgaben["8"] = vAufgabe_8;
	aufgaben["9a"] = vAufgabe_9a;
	aufgaben["9b"] = vAufgabe_9b;
	aufgaben["9c"] = vAufgabe_9c;

	srand(42); // Konstanter Seed f�r "zuf�llige" Verhaltensmuster

	string sChoose = "";
	do
	{
		cout << "Praktikum Informatik II (WS2016) - Strassenverkehr Block 3 - Marvin Klimke" << endl;
		cout << "Bitte w\204hlen Sie das K\201rzel der Aufgabe, die Sie ausf\201hren m\224chten:" << endl;
		cout << "1  : vAufgabe_1()     !" << endl
			 << "1d : vAufgabe_1_deb() !" << endl
			 << "2  : vAufgabe_2()     !" << endl
			 << "3  : vAufgabe_3()     !" << endl
			 << "4  : vAufgabe_4()     !" << endl
			 << "5  : vAufgabe_5()     !" << endl
			 << "6  : vAufgabe_6()     !" << endl
			 << "6a : vAufgabe_6a()    !" << endl
			 << "7  : vAufgabe_7()" << endl
			 << "8  : vAufgabe_8()" << endl
			 << "9a : vAufgabe_9a() - VO.dat" << endl
			 << "9b : vAufgabe_9b() - Simu.dat" << endl
			 << "9c : vAufgabe_9c() - SimuDisplay.dat" << endl
			 << "e  : Programm beenden." << endl;

		cin >> sChoose;
		cout << endl;

		auto it = aufgaben.find(sChoose);

		if (it != aufgaben.end())
		{
			(*it->second)(); // Funktionspointer aufrufen
			AktivesVO::vClearMap();
		}
		else if (sChoose != "e")
		{
			cout << "Eingabe konnte nicht zugeordnet werden." << endl;
		}
		cout << endl;

	} while (sChoose != "e");

	return 0;
}
