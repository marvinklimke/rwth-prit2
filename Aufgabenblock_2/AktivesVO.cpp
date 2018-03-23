// file:	AktivesVO.cpp
// author:	Marvin Klimke
// date:	07.09.2016

#include "AktivesVO.h"

#include <iomanip>
#include <iostream>

using namespace std;

int AktivesVO::p_iMaxID = 0;


AktivesVO::AktivesVO()
{
	vInitialisierung();
}

AktivesVO::AktivesVO(const AktivesVO& rhs)
{
	vInitialisierung();
	p_sName = rhs.p_sName + " (K)";
}

AktivesVO::AktivesVO(const string sName)
{
	vInitialisierung();
	p_sName = sName;
}

AktivesVO::~AktivesVO()
{
}

void AktivesVO::vInitialisierung()
{
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dZeit = 0.0;
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

string AktivesVO::getName()
{
	return p_sName;
}

AktivesVO& AktivesVO::operator = (const AktivesVO& rhs)
{
	vInitialisierung();
	p_sName = rhs.p_sName + " (K)";
	return *this;
}

ostream& operator << (ostream& out, const AktivesVO& vo)
{
	return vo.ostreamAusgabe(out);
}
