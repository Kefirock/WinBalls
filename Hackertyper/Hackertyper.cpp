#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

struct Text
{
    sf::Font font;
    sf::Text words;

    Text()
    {
        font.loadFromFile("resources/arial.ttf");
        words.setFont(font);
        words.setFillColor(sf::Color::White);
        words.setCharacterSize(24);
    };

    /*
    int fileLen(std::ifstream *fd, int visibleLen)
    {
        fd-> seekg(0, std::ios::visibleLen);
        int len = file.tellg();
        fd-> seekg(0, std::ios::beg);

        return len;
    }
    */

    void print(const char* something)
    {
        words.setString(something);
    }

    void import()
    {       
        //int len = fileLen(&file);

        char buff[50];
        std::ifstream file("resouces/text.txt");

        file.getline(buff, 50);
        
        //file.read(buffer, len);

        file.close();
        
        text.words = buffer.getline(buffer, 1);
        
        delete[] buffer;
    }
};


int main()
{
    Text text;

    int width = 1280;
    int height = 720;

    sf::RenderWindow window(sf::VideoMode(width, height), "Pentagon files");

    text.import();
    //text.print("");

   while (true)
   {
        window.clear();

    
        window.draw(text.words);

        
        window.display();
   }
   return 0;
}

