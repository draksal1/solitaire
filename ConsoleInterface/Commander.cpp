#include "Commander.h"
#include <sstream>
#include <iostream>
void Commander::operator()(std::string& comand)
{
	std::vector<std::string> parsedCommand = parse(comand);
    int wordsCount = parsedCommand.size();
    if (wordsCount > 3 || wordsCount<1)
    {
        return;
    }
    if (wordsCount == 1)
    {
        if (parsedCommand[0] == "replay")
        {
            desk.initialize();
        }
        else if (parsedCommand[0] == "take")
        {
            desk.takeCardFromDeck();
        }
        else if (parsedCommand[0] == "return")
        {
            desk.returnCardsToDeck();
        }
    }
    else if(wordsCount == 2) {
        if (parsedCommand[0].size() == 2 || parsedCommand[1].size() == 2)
        {
            int first = parsedCommand[0][1] - '0';
            int second = parsedCommand[1][1] - '0';
            if (parsedCommand[0][0] == 'R' && first<8 && first>=0) {
                if (parsedCommand[1][0] == 'S' && second < 4 && second >= 0)
                {
                    desk.moveCardFromRowToStack(first, second);
                }
                else if (parsedCommand[1][0] == 'R' && second < 7 && second >= 0) {
                    desk.moveCardFromRowToRow(first, second);
                }
            }
        }
    }
    else {
        int first = parsedCommand[0][1] - '0';
        int second = parsedCommand[1][1] - '0';
        int count = 1;
        try {
            count = stoi(parsedCommand[2]);
        }
        catch(...) {
            return;
        }
        if (parsedCommand[0][0] == 'R' && first < 7 && first >= 0 && parsedCommand[1][0] == 'R' && second < 7 && second >= 0) {
            desk.moveNCardsFromRowToRow(first, second, count);
        }
    }
}

std::vector<std::string> Commander::parse(std::string str) {
    const char kDelim = 0x20;
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (getline(ss, item, kDelim)) {
        result.push_back(item);
    }
    return result;
}
