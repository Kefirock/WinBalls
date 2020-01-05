#include <iostream>
#include <fstream>
#include <cstring>
#include <SFML/Graphics.hpp>

struct FileReader
{
    FILE* file;
    int size;

    int filelen()
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        return size;        
    }

    void read(char** buffer)
    {
        file = fopen("resources/PentagonData.txt", "r");

        if (file == NULL) 
        {
            perror ("Wrong path");
        }
        else
        {
            size = filelen();   
            *buffer = new char[size];
            fread(*buffer, sizeof(char), size, file);
            fclose (file);    
        } 
    }
};

struct Texxt
{
    sf::Font font;
    sf::Text words;

    Texxt()
    {
        font.loadFromFile("resources/arial.ttf");
        words.setFont(font);
        words.setFillColor(sf::Color::White);
        words.setCharacterSize(16);
    };
};

struct FileManager
{
    char* buffer;

    void readFile(FileReader *reader)
    {
        reader->read(&buffer);
    } 
};

struct Hackertyper
{
    int currentSymbols = 0;
    int currentVisibleSymbols = 0;
    char* visibleText;
    char* realText;

    void importLen (int size)
    {
        visibleText = new char [size + 1];
    }  

    void addWords(int size, char* buffer)
    {
        if (currentSymbols < size)
        {
            for (int i = 0; i < 5 && buffer[i] + 1 != '\n'; i++)
            {
                visibleText [currentVisibleSymbols] = buffer [currentSymbols];
                currentSymbols = currentSymbols + 1;
                currentVisibleSymbols = currentVisibleSymbols + 1;
            }
            visibleText [currentVisibleSymbols] = '\0';
        }
    }

    int countStrings(char* chr)
    {
        int stringsCount = 1;

        for (int i = 0; i < currentVisibleSymbols; i++)
        {
            if (chr[i] == '\n')
            {
                stringsCount = stringsCount + 1;
            }
        }
        
        return stringsCount;
    }

    int countShift(char* chr)
    {
        int currentStrings = countStrings(chr);
        
        int limit = 30;

        int strings = 0;
        int shift = 0;


        while(strings < currentStrings - limit) 
        {
            if (chr[shift] == '\n')
            {
                strings = strings + 1;
            }
            shift = shift + 1;
        }
        return shift;
    }

    void shift (char* chr)
    {
        int shift = countShift(chr);
        int i = 0;
        
        if (visibleText[i + shift] != '\0')
        {
            while (visibleText[i + shift] != '\0')
            {            
                char j = visibleText [i + shift];
                visibleText [i] = j;
                i = i + 1;  
            }
            visibleText[i] = '\0';
            currentVisibleSymbols = i;
        }         
    }

    void setText(Texxt *text)
    {
        text->words.setString(visibleText);
    }

    void hackData(sf::Event event, Texxt* text, int size, char* buffer)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            addWords(size, buffer);
            shift(visibleText);
            setText(text);
        }
    }
};

int main()
{
    Texxt text;
    sf::Event event;
    FileReader reader;
    FileManager manager;
    Hackertyper troyan;

    int width = 1280;
    int height = 720;

    manager.readFile(&reader);
    troyan.importLen(reader.size);
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Pentagon files");

    while (true)
    {
        window.clear();

        while (window.pollEvent(event))
        {
            troyan.hackData(event, &text, reader.size, manager.buffer);
        }

        window.draw(text.words); 
        window.display();
    }
    
    return 0;  
}

