#include "FileFunctions.h"


namespace file {
	///////////////////////////////////////////////////////////////
	std::string readLigne(std::string fichier, int ligne)
	{
		std::string res("");        // resutlat final
		std::ifstream flux(fichier);

		for (int i(0); i < ligne; i++)
		{
			std::getline(flux, res);
		}
		flux.close();
		for (int i(0); i < res.size(); i++)
		{
			if (res[i] == '�') res[i] = '\n';
		}
		return res;
	}
	///////////////////////////////////////////////////////////////
	void write(std::string fichier, std::string texte)
	{
		std::ofstream flux(fichier.c_str(), std::ios::app);
		flux << texte;
		flux.close();

	}
	///////////////////////////////////////////////////////////////
	void write(std::string texte, int ligne, int afterNbWord)
	{
		std::ifstream fluxI("Data/Save/00001.save");
		std::string result;
		for (int i(0); i < ligne; i++)
		{
			std::getline(fluxI, result);
		}

		for (int i(0); i < afterNbWord; i++)
		{
			fluxI >> result;
		}
		std::ofstream fluxO("Data/Save/00001.save", std::ios::app);

		fluxO.seekp(fluxI.tellg());
		fluxO << texte;
		fluxO.close();
		fluxI.close();

	}
	///////////////////////////////////////////////////////////////
	int getNbLigne(std::string fichier)
	{
		std::ifstream in(fichier, std::ios::in);
		std::string s;
		int nbLignes(0);
		while (std::getline(in, s))
		{
			nbLignes++;
		}
		in.close();
		return nbLignes;
	}
	///////////////////////////////////////////////////////////////
	void deleteContent(std::string fichier)
	{
		std::ofstream flux(fichier.c_str());
		flux.close();
	}

	///////////////////////////////////////////////////////////////
	std::vector<std::string> getAllLines(std::string fichier)
	{
		std::vector<std::string> res(0);        // resutlat final
		std::ifstream flux(fichier);
		std::string s;
		while (std::getline(flux, s))
		{
			res.push_back(s);
		}
		flux.close();
		return res;
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::string> getAllLines(std::string fichier, bool indexCorelation)
	{
		std::vector<std::string> res(0);        // resutlat final
		if (indexCorelation) res.push_back(""); // pour d�caler les index
		std::ifstream flux(fichier);
		std::string s;
		while (std::getline(flux, s))
		{
			res.push_back(s);
		}
		flux.close();
		return res;
	}
	void writeAllLines(std::string fichier, std::vector<std::string> allLines)
	{
		std::ofstream flux(fichier.c_str(), std::ios::app);
		for (size_t i = 0; i < allLines.size(); i++)
		{
			flux << allLines[i] << '\n';
		}
		flux.close();
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::string> getAllLinesUTF8(std::string fichier)
	{
		std::vector<std::string> res(0);        // resutlat final
		res.push_back(""); // pour d�caler les index
		std::ifstream flux(fichier);
		std::string s;
		while (std::getline(flux, s))
		{
			res.push_back(encodage::encodeToUTF32(s));
		}
		flux.close();
		return res;
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::wstring> getAllLinesUTF8_W(std::string fichier)
	{
		std::vector<std::wstring> res(0); 
		std::wifstream flux(fichier);
		std::wstring s;
		while (std::getline(flux, s))
		{
			res.push_back(encodage::encodeToUTF32(s));
		}
		flux.close();
		return res;
	}
	///////////////////////////////////////////////////////////////
	std::vector<std::string> getAllLinesUTF8(std::string fichier, bool indexCorelation)
	{
		std::vector<std::string> res(0);        // resutlat final
		if (indexCorelation) res.push_back(""); // pour d�caler les index
		std::ifstream flux(fichier);
		std::string s;
		while (std::getline(flux, s))
		{
			res.push_back(encodage::encodeToUTF32(s));
		}
		flux.close();
		return res;
	}
	///////////////////////////////////////////////////////////////
}