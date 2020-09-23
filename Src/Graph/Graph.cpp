#include "Graph.h"

namespace graph
{
    Graph<int> loadFromFile(std::string fileName, bool isOriented)
    {
        Graph<int> g;
        std::vector<std::string> allLines = file::getAllLines(fileName);

        for (size_t i = 0; i < allLines.size(); i++)
        {
            std::string baliseName ="";
            std::string value = parcer::getValueOfBaliseXML(allLines[i], baliseName);

            if (baliseName == "Node")
            {
                g.addNode(std::to_int(value));
            }
            else if (baliseName == "Edge")
            {
                int from = std::to_int(parcer::getValueOfAttributXML(allLines[i], "from"));
                int to = std::to_int(parcer::getValueOfAttributXML(allLines[i], "to"));
                double distance = std::to_double(value);

                g.addEdges(from, to, distance);
                if (!isOriented) g.addEdges(to, from, distance);
            }
        }
        return g;
    }
        
} // namespace graph


