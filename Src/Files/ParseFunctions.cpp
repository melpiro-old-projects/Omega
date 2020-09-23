#include "ParseFunctions.h"


namespace parcer {
	std::vector< std::vector<std::string>> parceSVG(std::string pathToSVG)
	{
		std::vector<std::string> data = file::getAllLines(pathToSVG, false);
		std::vector< std::vector<std::string>> res;
		for (size_t i = 0; i < data.size(); i++)
		{
			res.push_back(std::vector<std::string>(0)); // on cr�� la ligne
			vector::pushBack(res.back(), str::split(data[i], ",")); // on la remplie
		}
		return res;
	}

	///////////////////////////////////////////////////////////////
	std::string getValueOfAttributXML(std::string line, std::string attrName)
	{
		int index = str::findStrInStr(line, attrName);
		if (index == -1) return "";

		std::string str = "";
		int i = index + attrName.size() + 2;
		while (i < line.size() && line[i] != '"')
		{
			str += line[i];

			i++;
		}
		if (line[i] != '"') return "";

		return str;
	}

	std::string getValueOfBaliseXML(std::string line, std::string& name)
	{
		int i = 0;
		name="";
		bool opened = false;
		while (i < line.size() && line[i] != '>')
		{
			if (line[i] == ' ') opened = false;
			if (opened)
			{
				name+= line[i];
			}
			else if (line[i] == '<') opened = true;
			
			i++;
		}
		if (i >= line.size()) return "";

		i++;
		std::string res = "";
		while (i < line.size() && line[i] != '<')
		{
			res += line[i];
			i++;
		}
		if (i >= line.size()) return "";
		return res;
	}

	std::string getValueOfBaliseXML(std::string line)
	{
		int i = 0;
		while (i < line.size() && line[i] != '>')
		{
			i++;
		}
		if (i >= line.size()) return "";

		i++;
		std::string res = "";
		while (i < line.size() && line[i] != '<')
		{
			res += line[i];
			i++;
		}
		if (i >= line.size()) return "";
		return res;
	}
}