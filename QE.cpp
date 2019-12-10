#include <iostream>
#include <cmath>
#include <ctype.h>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    double a;
    double b;
    double c;
    double x;
    double D;

    while (true)
    {
        cout << "************************" << endl;

        cout << "a:";
        cin >> a;
        cout << "b:";
        cin >> b;
        cout << "c:";
        cin >> c;

        D = pow(b,2) - 4*a*c;

        cout << "" << endl;
        cout << "Our ninjas did the math." << endl;
        cout << "" << endl;

        if (D > 0)
            {
                x = (-b + sqrt(D)) / (2*a);
                cout << "First root: "<< x << endl;

                x = (-b - sqrt(D)) / (2*a);
                cout << "Second root: "<< x << endl;

                continue;
            }

        else if (D == 0)
            {
                x = (-b) / (2*a);
                cout << "Single root: "<< x << endl;
                continue;
            }

        cout << "No roots. But here's a cookie for you." << endl;

    }

    return 0;
}




