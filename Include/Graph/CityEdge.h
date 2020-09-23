#pragma once
#include "CityNode.h"
class CityEdge
{
public:
	CityNode* from=0;
	CityNode* to=0;

	double x = 0.0;
	double y = 0.0;
	double angle = 0.0;
	double distance = 0.0;
	double width = 0.0;
	
	double addedWeight = 0.0;

};

