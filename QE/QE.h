#include <iostream>
#include <cmath>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;
using std::abs;

class Data
{
    public:

        double a;
        double b;
        double c;
        double x1;
        double x2;
        int result;

        Data()
        {
        };

        Data(double a, double b, double c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        };
};

bool isEqual(double n, double m)
{
    if(abs(m - n) < 0.0000000001)
    {
        return 1;
    }

    return 0;
}

void discriminant(Data *data)
{
    double D = pow(data->b, 2) - 4 * data->a * data->c;
    if (D > 0)
    {
        data->x1 = (-data->b + sqrt(D)) / (2 * data->a);
        data->x2 = (-data->b - sqrt(D)) / (2 * data->a);

        data->result = 2;
    }

    else if (D == 0)
    {
        data->x1 = (-data->b) / (2 * data->a);

        data->result = 1;
    }

    else
    {
        data->result = 0;
    }
}

void calculateX(Data *data)
{
    double a = data->a;
    double b = data->b;
    double c = data->c;

    if (isEqual(a,0))
    {
        if (isEqual(b,0))
        {
            data->result = 0;
        }

        if (!isEqual(b,0))
        {
            if (isEqual(c,0))
            {
                data->x1 = 0;

                data->result = 1;
            }

            if (!isEqual(c,0))
            {
                data->x1 = -data->c/data->b;

                data->result = 1;
            }
        }
    }

    if (!isEqual(a,0))
    {
        discriminant(data);
    }
}

void print(Data data)
{
    cout << "a = " << data.a << endl;
    cout << "b = " << data.b << endl;
    cout << "c = " << data.c << endl;

    cout << "Our ninjas did the math." << endl;
    cout << "" << endl;

    if (data.result == 0)
    {
        cout << "0 roots" << endl;
    }

    if (data.result == 1)
    {
        cout << "x = "<< data.x1 << endl;
    }

    if (data.result == 2)
    {
        cout << "x1 = "<< data.x1 << endl;
        cout << "x2 = "<< data.x2 << endl;
    }

    cout << "" << endl;

}
