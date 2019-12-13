#include <iostream>
#include <cmath>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;

struct Abc
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    int roots;
};

void setAbc(Abc *data, double a, double b, double c)
{
    data->a = a;
    data->b = b;
    data->c = c;
}

double calculateD (Abc *data)
{
    return pow(data->b, 2) - 4 * data->a * data->c;
}


void calculateX(Abc *data)
{
    double D = calculateD(data);
    if (D > 0)
    {
        data->x1 = (-data->b + sqrt(D)) / (2 * data->a);
        data->x2 = (-data->b - sqrt(D)) / (2 * data->a);

        data->roots = 2;
    }

    else if (D == 0)
    {
        data->x1 = (-data->b) / (2 * data->a);

        data->roots = 1;
    }

    else
    {
        data->roots = 0;
    }
}

void print(Abc *data)
{

    cout << "Our ninjas did the math." << endl;
    cout << "" << endl;

    if (data->roots == 0)
    {
        cout << "You died. Your result: 0 roots." << endl;
    }

    if (data->roots == 1)
    {
        cout << "Single root: "<< data->x1 << endl;
    }

    if (data->roots == 2)
    {
        cout << "First root: "<< data->x1 << endl;
        cout << "Second root: "<< data->x2 << endl;
    }
    cout << "" << endl;

}

class unitTest
{
    public:
            void twoRoots(Abc *data, double a, double b, double c, double x1, double x2)
        {
            setAbc(data, a, b, c);
            calculateX(data);

            assert (data->roots == 2);
            assert (data->x1 == x1);
            assert (data->x2 == x2);
            print(data);

            cout << "|2 roots. Test passed.|" << endl;
            cout << "**************************" << endl;
        }

        void oneRoot(Abc *data, double a, double b, double c, double x1)
        {
            setAbc(data, a, b, c);
            calculateX(data);

            assert (data->roots == 1);
            assert (data->x1 == x1);
            print(data);

            cout << "|1 root. Test passed.|" << endl;
            cout << "**************************" << endl;
        }

        void noRoots(Abc *data, double a, double b, double c)
        {
            setAbc(data, a, b, c);
            calculateX(data);

            assert (data->roots == 0);
            print(data);

            cout << "|No roots. Test passed.|" << endl;
            cout << "**************************" << endl;
        }

        bool wrongInput(Abc *data, double a, double b, double c)
        {
            setAbc(data, a, b, c);
            calculateX(data);
            cout << "" << endl;

            if (a == 0 or b == 0)
                {
                    cout << "|Input is not correct. Test failed .|" << endl;
                    cout << "**************************" << endl;
                    return 1;
                }

            cout << "|Input is correct. Test passed.|" << endl;
            cout << "**************************" << endl;
            return 1;
        }
};

int main()
{
    Abc data;
    unitTest test;

    test.twoRoots(&data, 5, -7, 2 , 1, 0.4);
    test.oneRoot(&data, 1, 6, 9 , -3);
    test.noRoots(&data, 2, 1, 5);
    test.wrongInput(&data, 0, 0, 0);

    while (true)
    {

    }
    return 0;
}



