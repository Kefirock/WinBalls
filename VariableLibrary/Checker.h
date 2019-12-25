#include <iostream>

void printTrue(bool something, const char* name)
{
    if (something == true)
    {
        std::cout << "Test |" << name << "| passed\n" << std::endl;
    }
        
    else
    {
        std::cout << "Test |" << name << "| failed\n" << std::endl; 
    }       
}

void printFalse(bool something, const char* name)
{
    if (something == false)
    {
        std::cout << "Test |" << name << "| passed\n" << std::endl;
    }
        
    else
    {
        std::cout << "Test |" << name << "| failed\n" << std::endl; 
    }       
}

bool check(char* v1, char* v2)
{
    if(v1 == v2)
        std::cout << v1 <<" = " << v2 << std::endl;
    int i = 0;
    while (v1[i] != '\0' && v2[i] != '\0')
    {
        if (v1[i] == v2[i])
        {
            i = i + 1;
            continue;
        }
        std::cout << v1 <<" != " << v2 << std::endl;     
        return false;
    }
    std::cout << v1 <<" = " << v2 << std::endl;
    return true;  
}

bool check(char* v1, const char* v2)
{
    if(v1 == v2)
        std::cout << v1 <<" = " << v2 << std::endl;
    int i = 0;
    while (v1[i] != '\0' && v2[i] != '\0')
    {
        if (v1[i] == v2[i])
        {
            i = i + 1;
            continue;
        }
        std::cout << v1 <<" != " << v2 << std::endl;    
        return false;
    }
    std::cout << v1 <<" = " << v2 << std::endl;
    return true;  
}

bool check(int v1, int v2)
{
    if(v1 == v2)
        std::cout << v1 <<" = " << v2 << std::endl;
        return true;
    return false;
}