#include "Variable.h"
#include "Checker.h"

int main()
{
    //strlen
    const char *str1 = "Alladin";
    bool ch = check(strlen(str1), 7);
    printTrue (ch, "strlen");

    //strncpy
    const char src[100] = "Abdullah";
    char dest[100] = " ";
    strncpy (dest,src, 5);

    bool ch1 = check(dest, "Abdud");
    printFalse (ch1, "strncpy - 1");
    bool ch2 = check(dest, "Abdul");
    printTrue (ch2, "strncpy - 2");

    //strncat
    const char src1[100] = "Abdullahh";
    char dest1[100] = "Abdrahmanov ";
    strncat(dest1, src1, 8);

    bool ch3 = check(dest1, "Abdrahmanov Abdullah");
    printTrue (ch3, "strncat - 1");
    bool ch4 = check(dest1, "Abudi Dabudai");
    printFalse (ch4, "strncat - 2");

    //strcmp
    const char str2[100] = "Alladin";
    const char str3[100] = "Alladin";
    const char str4[100] = "Alduin";

    bool ch5 = strcmp(str2, str3);
    printTrue(ch5, "strcmp - 1");
    bool ch6 = strcmp(str2, str4);
    printFalse(ch6, "strcmp - 2");

    //strncmp
    const char str5[100] = "Alban";
    const char str6[100] = "Alduin";

    bool ch7 = strncmp(str5, str6, 2);
    printTrue(ch7, "strncmp - 1");
    bool ch8 = strncmp(str5, str6, 7);
    printFalse(ch8, "strncmp - 2");

}