#pragma once

#include <vector>
#include <fstream> 
#include <sstream>

#include "EncodeFunction.h"

namespace file {
	std::string readLigne(std::string fichier, int ligne);
	void write(std::string fichier, std::string texte);
	void write(std::string texte, int ligne, int afterNbWord);
	int getNbLigne(std::string fichier);
	void deleteContent(std::string fichier);
	std::vector<std::string> getAllLines(std::string fichier);
	std::vector<std::string> getAllLines(std::string fichier, bool indexCorelation);
	void writeAllLines(std::string fichier, std::vector<std::string> allLines);

	std::vector<std::string> getAllLinesUTF8(std::string fichier);
	std::vector<std::wstring> getAllLinesUTF8_W(std::string fichier);
	std::vector<std::string> getAllLinesUTF8(std::string fichier, bool indexCorelation);

}
