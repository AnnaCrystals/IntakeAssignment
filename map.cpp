#include "map.h"
#include "template.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>

using namespace std;



namespace Tmpl8
{
    Map::Map() {
        
    }

    /*void Map::FolderRead() 
    {
        for (auto& file : experimental::filesystem::directory_iterator( "./assets/tile" ))  
        {
            std::string foo("tilemap_");

            int result = strcmp(foo.c_str(), file.path().filename().string().substr(0,foo.length()).c_str());
            if (result != 0) { continue; }
            
            int i = 0;
            ifstream fs{ file.path() };

        }
    }*/

    void Map::LoadMap(const char* nameFile, const int layer) {
        int x = 0;
        int y = 0;

        int numCounter = 0;
        int number = 0;
        bool isNegative = false;
        
        
       string mapData = TextFileRead(nameFile);

        for (int i = 0; i < mapData.size(); i++) {
            char c = mapData[i];
            if (c == '\n') {
                
                if (isNegative) {
                    map[layer][y][x] = -number;
                }
                else {
                    map[layer][y][x] = number;
                }
                y++;
                x = 0;
                number = 0;
                numCounter = 0;
                isNegative = false;
            }
            else if (c == ',') {

                if (isNegative) {
                    map[layer][y][x] = -number;
                }
                else {
                    map[layer][y][x] = number;
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

    }

   string Map::TextFileRead(const char* nameFile)
   {
        ifstream file(nameFile);
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }
        else {
            return "";
        }
    }

   
};