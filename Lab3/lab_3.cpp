#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const size_t N = 8;

void fillArray(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
}

void printArray(int a[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void copyArray(int from[], int to[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        to[i] = from[i];
    }
}

bool better(int x, int y, bool ascending)
{
    if (ascending)
        return x < y;
    else
        return x > y;
}

void selectionSort(int a[], size_t n, bool ascending, size_t counts[])
{
    for (size_t i = 0; i + 1 < n; i++)
    {
        size_t min = i;
        for (size_t j = i + 1; j < n; j++)
        {
            counts[1] = counts[1] + 1;
            if (better(a[j], a[min], ascending))
                min = j;
        }
        if (i != min)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
            counts[0] = counts[0] + 1;
        }
    }
}

void bubbleSort(int a[], size_t n, bool ascending, size_t counts[])
{
    size_t i = 0;
    bool t = true;
    while (t)
    {
        t = false;
        for (size_t j = 0; j + 1 < n - i; j++)
        {
            counts[1] = counts[1] + 1;
            if (better(a[j + 1], a[j], ascending))
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                counts[0] = counts[0] + 1;
                t = true;
            }
        }
        i++;
    }
}

void printStepTitle(int step)
{
    if (step == 1)
        cout << "1) По возрастанию:" << endl;
    else if (step == 2)
        cout << "2) Снова по возрастанию:" << endl;
    else
        cout << "3) По убыванию:" << endl;
}

void testSort(int original[], size_t n, int method)
{
    int a[N];
    size_t counts[2];
    copyArray(original, a, n);

    if (method == 1)
        cout << endl << "Сортировка выбором" << endl;
    else
        cout << endl << "Сортировка пузырьком" << endl;

    for (int step = 1; step <= 3; step++)
    {
        printStepTitle(step);

        bool ascending = true;
        if (step == 3)
            ascending = false;

        counts[0] = 0;
        counts[1] = 0;
        if (method == 1)
            selectionSort(a, n, ascending, counts);
        else
            bubbleSort(a, n, ascending, counts);

        printArray(a, n);
        cout << "Перестановок: " << counts[0] << endl;
        cout << "Сравнений: " << counts[1] << endl;
    }
}

int main()
{
    int original[N];

    srand(time(NULL));
    fillArray(original, N);

    cout << "Исходный массив:" << endl;
    printArray(original, N);

    testSort(original, N, 1);
    testSort(original, N, 2);

    return 0;
}