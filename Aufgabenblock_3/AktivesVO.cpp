// file:	AktivesVO.cpp
// author:	Marvin Klimke
// date:	07.09.2016

#include "AktivesVO.h"

#include <iomanip>
#include <iostream>

using namespace std;

int AktivesVO::p_iMaxID = 0;

map<string, AktivesVO*> AktivesVO::VOMap;

AktivesVO::AktivesVO()
{
	vInitialisierung();
}

AktivesVO::AktivesVO(const AktivesVO& rhs)
{
	vInitialisierung();
	p_sName = rhs.p_sName + " (K)";
	vRegister();
}

AktivesVO::AktivesVO(const string sName)
{
	vInitialisierung();
	p_sName = sName;
	vRegister();
}

AktivesVO::~AktivesVO()
{
	VOMap.erase(p_sName);
}

void AktivesVO::vInitialisierung()
{
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dZeit = 0.0;
}

void AktivesVO::vRegister()
{
	if (VOMap.find(p_sName) != VOMap.end())
	{
		throw string("Das Verkehrsobjekt konnte nicht registriert werden, da bereits ein Eintrag mit diesem Namen vorhanden ist.");
	}

	VOMap[p_sName] = this;
}

void AktivesVO::vAusgabe() const
{
	cout << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << p_iID << " " // ID rechtsb�ndig
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(10) << p_sName << ": "; // Name linksb�ndig

}

ostream& AktivesVO::ostreamAusgabe(ostream& out) const
{
	out << setprecision(2) << fixed // 2 feste Nachkommastellen
		<< resetiosflags(ios::left) << setiosflags(ios::right) << setw(2) << p_iID << " " // ID rechtsb�ndig
		<< resetiosflags(ios::right) << setiosflags(ios::left) << setw(10) << p_sName << ": "; // Name linksb�ndig
	return out;
}

istream& AktivesVO::istreamEingabe(istream& in)
{
	if (p_sName != "")
	{
		throw string("Es wurde versucht in ein bereits initialisiertes Verkehrsobjekt zu Laden.");
	}

	in >> p_sName;

	vRegister();

	return in;
}

string AktivesVO::getName() const
{
	return p_sName;
}

AktivesVO& AktivesVO::operator = (const AktivesVO& rhs)
{
	vInitialisierung();
	p_sName = rhs.p_sName + " (K)";
	vRegister();
	return *this;
}

AktivesVO* AktivesVO::ptObjekt(string sName)
{
	AktivesVO* pVO = nullptr;

	auto it = VOMap.find(sName);

	if (it != VOMap.end())
	{
		pVO = it->second;
	}
	else
	{
		throw string("Das Verkehrsobjekt wurde nicht gefunden.");
	}
	
	return pVO;
}

void AktivesVO::vClearMap()
{
	VOMap.clear();
}

ostream& operator << (ostream& out, const AktivesVO& vo)
{
	return vo.ostreamAusgabe(out);
}

istream& operator >> (istream& in, AktivesVO& vo)
{
	return vo.istreamEingabe(in);
}
