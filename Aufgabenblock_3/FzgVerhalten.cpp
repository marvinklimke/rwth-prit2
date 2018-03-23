// file:	FzgVerhalten.cpp
// author:	Marvin Klimke
// date:	08.09.2016

#include "FzgVerhalten.h"

FzgVerhalten::FzgVerhalten(Weg* pWeg)
	: p_pWeg(pWeg)
{
}

FzgVerhalten::~FzgVerhalten()
{
}

Weg* FzgVerhalten::getWeg() const
{
	return p_pWeg;
}
