//Copies up to n characters from the string pointed to, by src to dest.
char *strncpy(char *dest, const char *src, int n)
{
    int i = 0;
    while (src[i] != '\0' && i < n)
    {
        dest[i] = src[i];
        i = i + 1; 
    }
    dest[i] = '\0';
}

//Computes the length of the string str up to but not including the terminating null character.
int strlen(const char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i = i + 1;    
    }
    return i;
}

//Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long.
char *strncat(char *dest, const char *src, int n)
{
    int i = 0;
    while (dest[i] != '\0')
    {
        i = i + 1; 
    }
    
    int p = 0;
    while (src[p] != '\0' && p < n)
    {
        dest[i] = src[p];
        i = i + 1;
        p = p + 1;
    }
    dest[i] = '\0';
}

//Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str.
char *strchr(const char *str, int c)
{
    //???????????????
}

//Compares the string pointed to, by str1 to the string pointed to by str2.
bool strcmp(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] == str2[i])
        {
            i = i + 1;
            continue;
        }    
        return false;
    }
    return true;     
}

//Compares at most the first n bytes of str1 and str2.
bool strncmp(const char *str1, const char *str2, int n)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && i < n)
    {
        
        if (str1[i] == str2[i])
        {
            i = i + 1;       
            continue;
        }
        return false;
    }
    return true;  
}

//Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
char* strstr(const char *haystack, const char *needle)
{

}

//Appends the string pointed to, by src to the end of the string pointed to by dest.
char* strcat(char *dest, const char *src)
{
    int i = 0;
    while (dest[i] != '\0')
    {
        i = i + 1; 
    }
    
    int p = 0;
    while (src[p] != '\0')
    {
        dest[i] = src[p];
        i = i + 1;
        p = p + 1;
    }
    dest[i] = '\0';    
}






