#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x)
{
    return x - cos(x);
}

void task1()
{
    double xl, xr, xm;
    double eps = 0.0001;

    cout << "Задание 1" << endl;
    cout << "Введите xL: ";
    cin >> xl;
    cout << "Введите xR: ";
    cin >> xr;

    if (f(xl) * f(xr) >= 0)
    {
        cout << "На этом отрезке корня нет" << endl;
        return;
    }

    while (xr - xl >= eps)
    {
        xm = (xl + xr) / 2;
        if (f(xl) * f(xm) <= 0)
            xr = xm;
        else
            xl = xm;
    }

    xm = (xl + xr) / 2;
    cout << fixed << setprecision(5);
    cout << "Корень уравнения x = " << setw(8) << xm << endl;
}

void task2()
{
    double eps = 0.000001;
    double x, y, s, a;
    int n;

    cout << endl << "Задание 2" << endl;
    cout << setw(10) << "X" << setw(12) << "Y(x)";
    cout << setw(12) << "S(x)" << setw(5) << "N" << endl;

    for (int i = 0; i <= 5; i++)
    {
        x = i * 0.2;
        y = exp(2 * x);

        a = 1;
        s = 1;
        n = 0;

        while (a >= eps)
        {
            n++;
            a = a * 2 * x / n;
            s += a;
        }

        cout << fixed << setprecision(6);
        cout << setw(10) << x << setw(12) << y;
        cout << setw(12) << s << setw(5) << n << endl;
    }
}

int main()
{
    task1();
    task2();
    return 0;
}