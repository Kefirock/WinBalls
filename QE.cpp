#include <iostream>
#include <cmath>
#include <ctype.h>

using std::cout;
using std::cin;
using std::endl;

double calculateD (double a, double b, double c)
{
    return pow(b,2) - 4*a*c;
}

int calculateX(double a, double b, double c, double *x1, double *x2)
{
    double D = calculateD(a,b,c);
    if (D > 0)
    {
        *x1 = (-b + sqrt(D)) / (2*a);
        *x2 = (-b - sqrt(D)) / (2*a);

        return 2;
    }

    if (D == 0)
    {
        *x1 = (-b) / (2*a);

        return 1;
    }

    return 0;
}

void print(double *x1, double *x2, int roots)
{

    cout << "Our ninjas did the math." << endl;
    cout << "" << endl;

    if (roots == 0)
    {
        cout << "No roots. But here's a cookie for you." << endl;
    }

    if (roots == 1)
    {
        cout << "Single root: "<< *x1 << endl;
    }

    if (roots == 2)
    {
        cout << "First root: "<< *x1 << endl;
        cout << "Second root: "<< *x2 << endl;
    }

}

int main()
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    int roots;

    while (true)
    {
        cout << "************************" << endl;

        cout << "a:";
        cin >> a;
        cout << "b:";
        cin >> b;
        cout << "c:";
        cin >> c;

        roots = calculateX(a,b,c, &x1, &x2);
        print(&x1, &x2, roots);
    }

    return 0;
}




