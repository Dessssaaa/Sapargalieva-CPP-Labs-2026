#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int duration;      // длительность разговора, мин
    int startHour;     // час начала разговора (0-23)
    int dayOfWeek;     // день недели (1-7, 1 - понедельник)
    int isRegular;     // постоянный клиент: 1 - да, 0 - нет

    cout << "Введите данные звонка:\n";

    cout << "Длительность (мин): ";
    cin >> duration;

    // Проверка корректности длительности
    if (duration <= 0) {
        cout << "Ошибка: длительность должна быть больше нуля.\n";
        return 1;
    }

    cout << "Час начала (0-23): ";
    cin >> startHour;

    // Проверка диапазона часов
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

    // --- Определение тарифа (вложенные ветвления) ---
    double rate;            // руб./мин
    string tariffName;

    bool isWeekend = (dayOfWeek == 6 || dayOfWeek == 7); // сб, вс

    if (isWeekend) {
        // Выходные: фиксированная ставка на все время
        rate = 2.0;
        tariffName = "выходной (2.00 руб/мин)";
    } else {
        // Будни: тариф зависит от времени суток
        if (startHour >= 8 && startHour < 22) {
            rate = 5.0;
            tariffName = "будни-день (5.00 руб/мин)";
        } else {
            rate = 3.0;
            tariffName = "будни-ночь (3.00 руб/мин)";
        }
    }

    // --- Расчет стоимости ---
    // Каждая промежуточная сумма округляется до копеек, как в чеке
    auto roundToCents = [](double value) {
        return round(value * 100.0) / 100.0;
    };

    double baseCost = roundToCents(duration * rate);

    // Скидка за длительность (от 60 минут - 10%)
    double durationDiscount = 0.0;
    if (duration >= 60) {
        durationDiscount = roundToCents(baseCost * 0.10);
    }
    double afterDurationDiscount = roundToCents(baseCost - durationDiscount);

    // Скидка постоянному клиенту (+5% от оставшейся суммы)
    double regularDiscount = 0.0;
    if (isRegular == 1) {
        regularDiscount = roundToCents(afterDurationDiscount * 0.05);
    }
    double totalBeforeVat = roundToCents(afterDurationDiscount - regularDiscount);

    // НДС 20%
    double vat = roundToCents(totalBeforeVat * 0.20);
    double totalToPay = roundToCents(totalBeforeVat + vat);

    // --- Вывод детализированного чека ---
    cout << fixed << setprecision(2);
    cout << "\n=== РАСЧЕТ СТОИМОСТИ ===\n";
    cout << "Тариф: " << tariffName << "\n";
    cout << "Базовая стоимость: " << baseCost << " руб\n";
    cout << "Скидки:\n";
    cout << "- За длительность: " << durationDiscount << " руб\n";
    cout << "- Постоянный клиент: " << regularDiscount << " руб\n";
    cout << "Итого без НДС: " << totalBeforeVat << " руб\n";
    cout << "НДС 20%: " << vat << " руб\n";
    cout << "К ОПЛАТЕ: " << totalToPay << " руб\n";

    return 0;
}
