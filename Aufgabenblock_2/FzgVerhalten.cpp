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

double FzgVerhalten::dGeschwindigkeitslimit()
{
	switch (p_pWeg->getLimit())
	{
	case Weg::Innerorts:   return 50;
	case Weg::Landstrasse: return 100;
	case Weg::Autobahn:    return numeric_limits<double>::max();
	default: return 0;
	}
}
