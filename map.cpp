#include "map.h"
#include "template.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;



namespace Tmpl8
{

    string TextFileRead(const char* _File) {
        ifstream file(_File);
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }
        else {
            return "";
        }
    }


    void Map::LoadMap(const char* loadFile, const int layer) {
        int x = 0;
        int y = 0;

        int numCounter = 0;
        int number = 0;
        bool isNegative = false;
        
        
       string mapData = TextFileRead(loadFile);

        for (int i = 0; i < mapData.size(); i++) {
            char c = mapData[i];
            if (c == '\n') {
                y++;
                x = 0;
                if (isNegative) {
                    map[layer][x][y] = -number;
                }
                else {
                    map[layer][x][y] = number;
                }
                number = 0;
                numCounter = 0;
                isNegative = false;
            }
            else if (c == ',') {

                if (isNegative) {
                    map[layer][x][y] = -number;
                }
                else {
                    map[layer][x][y] = number;
                }

                number = 0;
                numCounter = 0;
                isNegative = false;
                x++;
            }
            else if (c == '-') {
                isNegative = true;
            }
            else if (c > 47 && c < 58) {
                number *= static_cast<int>(pow(10, numCounter));
                number += stoi(&c);
                numCounter++;
            }
        }

        loadedLayers++;
    }
};