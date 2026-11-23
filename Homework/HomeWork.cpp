#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int makeKeys(int keys[], int maxCount)
{
    std::ifstream file("key.txt");
    std::string word;
    int count = 0;
    while (count < maxCount && file >> word)
    {
        int sum = 0;
        int len = word.length();
        for (int j = 0; j < len; j++)
        {
            sum = sum + word[j];
        }
        keys[count] = sum % 128;
        count++;
    }
    file.close();
    return count;
}

int encode(const int keys[], int keyCount, int stat[128][128])
{
    std::ifstream in("source.txt", std::ios::binary);
    std::ofstream out("encoded.txt", std::ios::binary);
    int k = 0;
    int length = 0;
    char ch;
    while (in.get(ch))
    {
        int code = ch;
        if (code >= 0)
        {
            int coded = (code + keys[k]) % 128;
            out.put(coded);
            stat[code][coded]++;
            length++;
            k++;
            if (k == keyCount)
            {
                k = 0;
            }
        }
    }
    in.close();
    out.close();
    return length;
}

void decode(const int keys[], int keyCount)
{
    std::ifstream in("encoded.txt", std::ios::binary);
    std::ofstream out("decoded.txt", std::ios::binary);
    int k = 0;
    char ch;
    while (in.get(ch))
    {
        int coded = ch;
        int code = (coded - keys[k] + 128) % 128;
        out.put(code);
        k++;
        if (k == keyCount)
        {
            k = 0;
        }
    }
    in.close();
    out.close();
}

void showStat(int stat[128][128], int keyCount, int length)
{
    int again = 1;
    while (again == 1)
    {
        char ch;
        std::cout << "Введите символ: ";
        std::cin.ignore();
        std::cin.get(ch);
        int code = ch;
        if (code < 0)
        {
            std::cout << "Символ не входит в таблицу ASCII" << '\n';
        }
        else
        {
            int total = 0;
            int variants = 0;
            for (int j = 0; j < 128; j++)
            {
                total = total + stat[code][j];
                if (stat[code][j] > 0)
                {
                    variants++;
                }
            }
            std::cout << "символ | кол-во в исх-ом | кол-во вар-ов | ";
            std::cout << "размер блокнота | длина исх-ый" << '\n';
            std::cout << std::setw(6) << ch << " | ";
            std::cout << std::setw(15) << total << " | ";
            std::cout << std::setw(13) << variants << " | ";
            std::cout << std::setw(15) << keyCount << " | ";
            std::cout << std::setw(12) << length << '\n';
            for (int j = 0; j < 128; j++)
            {
                if (stat[code][j] > 0)
                {
                    std::cout << "Символ \'" << ch << "\' закодирован символом ";
                    if (j < 32 || j == 127)
                    {
                        std::cout << "с кодом " << j;
                    }
                    else
                    {
                        std::cout << "\'" << (char)j << "\'";
                    }
                    std::cout << " " << stat[code][j] << " раз(а)" << '\n';
                }
            }
        }
        std::cout << "Продолжить? (1 - да, 0 - нет): ";
        std::cin >> again;
    }
}

int main()
{
    int keys[20];
    int stat[128][128] = {0};
    int keyCount = makeKeys(keys, 20);
    if (keyCount == 0)
    {
        std::cout << "Файл key.txt не найден или пуст" << '\n';
        return 1;
    }
    int length = encode(keys, keyCount, stat);
    if (length == 0)
    {
        std::cout << "Файл source.txt не найден или пуст" << '\n';
        return 1;
    }
    decode(keys, keyCount);
    std::cout << "Кодирование и раскодирование выполнено" << '\n';
    std::cout << "Показать статистику? (1 - да, 0 - нет): ";
    int answer;
    std::cin >> answer;
    if (answer == 1)
    {
        showStat(stat, keyCount, length);
    }
    return 0;
}