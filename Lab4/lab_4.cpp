#include <iostream>
using namespace std;

const size_t MAX = 10;

void inputMatrix(int f[][MAX], size_t m)
{
    for (size_t i = 0; i < m; i++)
    {
        cout << "Строка " << i + 1 << ": ";
        for (size_t j = 0; j < m; j++)
        {
            cin >> f[i][j];
        }
    }
}

void printMatrix(int f[][MAX], size_t m)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
}

int rowSum(int f[][MAX], size_t m, size_t k)
{
    int s = 0;
    for (size_t j = 0; j < m; j++)
    {
        s = s + f[k][j];
    }
    return s;
}

int colSum(int f[][MAX], size_t m, size_t k)
{
    int s = 0;
    for (size_t i = 0; i < m; i++)
    {
        s = s + f[i][k];
    }
    return s;
}

size_t findRows(int f[][MAX], size_t m, size_t rows[])
{
    size_t count = 0;
    for (size_t i = 0; i < m; i++)
    {
        if (rowSum(f, m, i) == colSum(f, m, i))
        {
            rows[count] = i + 1;
            count++;
        }
    }
    return count;
}

int main()
{
    int f[MAX][MAX];
    size_t rows[MAX];
    size_t m;
    cout << "Введите размер матрицы m (от 1 до 10): ";
    cin >> m;
    while (m < 1 || m > MAX)
    {
        cout << "Неверный размер. Введите m (от 1 до 10): ";
        cin >> m;
    }
    cout << "Введите элементы матрицы по строкам:" << endl;
    inputMatrix(f, m);
    cout << "Исходная матрица:" << endl;
    printMatrix(f, m);
    size_t count = findRows(f, m, rows);
    if (count == 0)
        cout << "Одноименных строк и столбцов с равными суммами нет" << endl;
    else
    {
        cout << "Найденные строки (столбцы) и их суммы:" << endl;
        for (size_t k = 0; k < count; k++)
        {
            cout << "Номер " << rows[k] << ": сумма = ";
            cout << rowSum(f, m, rows[k] - 1) << endl;
        }
    }
    return 0;
}