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

    
    int fileLen(std::ifstream *fd)
    {
        fd-> seekg(0, std::ios::end);
        int len = fd->tellg();
        fd-> seekg(0, std::ios::beg);

        return len;
    }
    

    void print(const char* something)
    {
        words.setString(something);
    }

    void import()
    {
        std::ifstream file("resouces/text.txt");

        int len = fileLen(file);
        char *buffer = new char[len];

        file.read(buffer, len);
        file.close();

        delete [] buffer;

         
    }
};

int main()
{
    Text text;

    int width = 1280;
    int height = 720;

    sf::RenderWindow window(sf::VideoMode(width, height), "Pentagon files");

    text.import();
    text.print("It's working");

   while (true)
   {
        window.clear();

    
        window.draw(text.words);

        
        window.display();
   }
   return 0;
}

