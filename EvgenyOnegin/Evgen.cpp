#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <cstring>

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

    void read(char* *buffer)
    {
        file = fopen("file.txt", "r");

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

struct FileManager
{
    char* buffer;
    char** strings;
    int stringsCount;

    void readFile(FileReader *reader)
    {
        reader->read(&buffer);
    }

    void slice(FileReader reader)
    {
        int p = 0;
        for (int i = 0; i < reader.size; i = i + 1)
        {
            if (buffer[i] == '\n')
            {   
                buffer[i] = '\0';
                p = p + 1;  
            }
        }
        strings = new char* [p];

        int n = 0;
        int k = 0;
        for (int i = 0; n < p && i < reader.size; i = i + 1)
        {
            if (buffer[i] == '\0')
            {
                strings[n] = &buffer[i - k];
                n = n + 1;
                k = 0;
            }

            else
            {
                k = k + 1;     
            } 
        }
        stringsCount = p;
    }

    bool compareStrings(char* str1, char* str2)
    {
        int i = strlen(str1);
        int j = strlen(str2);

        while (i >= 0 && j >= 0)
        {
            if (str1[i] > str2[j])
            {
                return false;
            }

            if (str1[i] < str2[j])
            {
                return true;
            }

            i = i - 1;
            j = j - 1;
        }
        return true;
    }

    void changeOrder()
    { 
        for (int i = 0; i < stringsCount; i++)
        {
            for (int j = 0; j < stringsCount - 1; j++)
            {
                if (!compareStrings(strings[i], strings[j]))
                {
                    char* ifake = strings[i];
                    strings[i] = strings[j];
                    strings[j] = ifake; 
                }
            }
        }
    }

    void write(FileReader *reader)
    {
        reader->file = fopen("output.txt", "w");
        for (int i = 0; i < stringsCount; i++)
        {   
            fprintf(reader->file, strings[i]);
            fprintf(reader->file, "\n");
        }
        delete[] buffer;
    }
};

int main()
{
    FileManager text;
    FileReader reader;
    text.readFile(&reader);
    text.slice(reader);
    text.changeOrder();
    text.write(&reader);    

    return 0;
}