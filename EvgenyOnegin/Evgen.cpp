#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <cstring>

struct FileManager
{
    FILE* file;
    char* buffer;
    char** strings;
    int size;
    int stringsCount;
     
    int filelen()
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        return size;
    }

    void read()
    {
        file = fopen("file.txt", "r");

        if (file == NULL) 
        {
            perror ("Wrong path");
        }
        else
        {
            size = filelen();   
            buffer = new char[size];
            fread(buffer, sizeof(char), size, file);
            fclose (file);    
        }
    }

    void slice()
    {
        int p = 0;
        for (int i = 0; i < size; i = i + 1)
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
        for (int i = 0; n < p && i < size; i = i + 1)
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

    bool compareStrings(int str1, int str2)
    {
        int i = strlen(strings[str1]);
        int j = strlen(strings[str2]);

        while (i >= 0 && j >= 0)
        {
            if (strings[str1][i] > strings[str2][j])
            {
                return false;
            }

            if (strings[str1][i] < strings[str2][j])
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
                if (!compareStrings(i, j))
                {
                    char* ifake = strings[i];
                    strings[i] = strings[j];
                    strings[j] = ifake; 
                }
            }
        }
    }
    
    void print()
    {   
        for (int i = 0; i < stringsCount; i = i + 1)
        {
        std::cout << strings[i] << std::endl;     
        }       
    }

    void write()
    {
        file = fopen("output.txt", "w");
        for (int i = 0; i < stringsCount; i++)
        {   
            fprintf(file, strings[i]);
            fprintf(file, "\n");
        }
        delete[] buffer;
    }
};

int main()
{
    FileManager file;
    file.read();
    file.slice();

    file.changeOrder();
    file.print();
    file.write();    

    return 0;
}