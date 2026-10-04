#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
    int duration;
    int startHour;
    int dayOfWeek;
    int isRegular;

    cout << "Введите данные звонка:\n";

    cout << "Длительность (мин): ";
    cin >> duration;

    if (duration <= 0) {
        cout << "Ошибка: длительность должна быть больше нуля.\n";
        return 1;
    }

    cout << "Час начала (0-23): ";
    cin >> startHour;

    if (startHour < 0 || startHour > 23) {
        cout << "Ошибка: час начала должен быть в диапазоне от 0 до 23.\n";
        return 1;
    }

    cout << "День недели (1-7, 1-пн): ";
    cin >> dayOfWeek;

    if (dayOfWeek < 1 || dayOfWeek > 7) {
        cout << "Ошибка: день недели должен быть в диапазоне от 1 до 7.\n";
        return 1;
    }

    cout << "Постоянный клиент (1-да/0-нет): ";
    cin >> isRegular;

    if (isRegular != 0 && isRegular != 1) {
        cout << "Ошибка: статус клиента должен быть 0 или 1.\n";
        return 1;
    }

    double rate;
    string tariffName;

    if (dayOfWeek == 6 || dayOfWeek == 7) {
        rate = 2.0;
        tariffName = "выходной (2.00 руб/мин)";
    } else {
        if (startHour >= 8 && startHour < 22) {
            rate = 5.0;
            tariffName = "будни-день (5.00 руб/мин)";
        } else {
            rate = 3.0;
            tariffName = "будни-ночь (3.00 руб/мин)";
        }
    }

    double baseCost = duration * rate;

    double durationDiscount = 0;
    if (duration >= 60) {
        durationDiscount = round(baseCost * 0.10 * 100) / 100;
    }
    double afterDuration = baseCost - durationDiscount;

    double regularDiscount = 0;
    if (isRegular == 1) {
        regularDiscount = round(afterDuration * 0.05 * 100) / 100;
    }

    double totalBeforeVat = round((afterDuration - regularDiscount) * 100) / 100;
    double vat = round(totalBeforeVat * 0.20 * 100) / 100;
    double totalToPay = totalBeforeVat + vat;

    cout << "\n=== РАСЧЕТ СТОИМОСТИ ===\n";
    cout << "Тариф: " << tariffName << "\n";
    cout << "Базовая стоимость: " << baseCost << " руб\n";
    cout << "Скидки:\n";
    cout << "  - За длительность: " << durationDiscount << " руб\n";
    cout << "  - Постоянный клиент: " << regularDiscount << " руб\n";
    cout << "Итого без НДС: " << totalBeforeVat << " руб\n";
    cout << "НДС 20%: " << vat << " руб\n";
    cout << "К ОПЛАТЕ: " << totalToPay << " руб\n";

    return 0;
}
