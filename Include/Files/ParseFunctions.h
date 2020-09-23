#pragma once

#include "VectorFunctions.h"
#include "FileFunctions.h"
#include "StringFunctions.h"

namespace parcer {
	std::vector< std::vector<std::string>> parceSVG(std::string pathToSVG);

	std::string getValueOfAttributXML(std::string line, std::string attrName);
	std::string getValueOfBaliseXML(std::string line, std::string& name);
	std::string getValueOfBaliseXML(std::string line);

}
