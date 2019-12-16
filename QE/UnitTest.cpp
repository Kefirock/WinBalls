#include "QE.h"

class UnitTest
{
    public:
        int id;
        Data data;

            UnitTest(double a, double b, double c, int i)
        {
            data = Data(a, b, c);
            id = i;
        }

        void twoRoots(double check1, double check2)
        {
            calculateX(&data);

            assert (data.result == 2);
            assert (data.x1 == check1);
            assert (data.x2 == check2);
            print(data);

            cout << "|Test " << id << " passed. 2 roots.|" << endl;
            cout << "**************************" << endl;
        }

        void oneRoot(double check1)
        {
            calculateX(&data);

            assert (data.result == 1);
            assert (data.x1 == check1);
            print(data);

            cout << "|Test " << id << " passed. 1 root.|" << endl;
            cout << "**************************" << endl;
        }

        void noRoots()
        {
            calculateX(&data);

            assert (data.result == 0);
            print(data);

            cout << "|Test " << id << " passed. No roots.|" << endl;
            cout << "**************************" << endl;
        }

        void aZero(double a, double b, double c)
        {
            calculateX(&data);

            print(data);
        }
};

int main()
{
    UnitTest test1(5,-7,2,1);
    UnitTest test2(1,6,9, 2);
    UnitTest test3(2,1,5, 3);
    UnitTest test4(0,0,0, 4);
    UnitTest test5(5,0,0, 5);
    UnitTest test6(0,5,0, 6);
    UnitTest test7(0,0,5, 7);
    UnitTest test8(4,8,0, 8);
    UnitTest test9(0,4,8, 9);


    test1.twoRoots(1, 0.4);
    test2.oneRoot(-3);
    test3.noRoots();
    test4.noRoots();
    test5.oneRoot(0);
    test6.oneRoot(0);
    test7.noRoots();
    test8.twoRoots(0,-2);
    test9.oneRoot(-2);


    while (true)
    {

    }
    return 0;
}
