#include <iostream>

int main() {
    int cat = 0;
    std::cin.good() >> cat;
    if (cat % 2 == 0) {
        std::cout << "четное";
    } else {
        std::cout << "нечетное";
    }

}
