#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cout << "Использование: calculator -o|--operation height|range УГОЛ СКОРОСТЬ\n"
                  << "УГОЛ — в градусах, СКОРОСТЬ — в м/с\n";
        return 0;
    }

    if (argc != 5 || (std::string(argv[1]) != "-o" && std::string(argv[1]) != "--operation")) {
        std::cerr << "Ошибка: укажите операцию, угол и скорость.\n";
        return 1;
    }

    const std::string operation = argv[2];
    if (operation != "height" && operation != "range") {
        std::cerr << "Ошибка: неизвестная операция. Используйте height или range.\n";
        return 1;
    }

    char* angleEnd;
    char* speedEnd;
    const double angle = std::strtod(argv[3], &angleEnd);
    const double speed = std::strtod(argv[4], &speedEnd);
    if (angleEnd == argv[3] || *angleEnd != '\0' || speedEnd == argv[4] ||
        *speedEnd != '\0' || !std::isfinite(angle) || !std::isfinite(speed)) {
        std::cerr << "Ошибка: угол и скорость должны быть числами.\n";
        return 1;
    }

    const double radians = angle * (std::acos(-1.0) / 180.0);
    const double g = 9.81;
    const double sinAngle = std::sin(radians);
    const double result = operation == "height"
        ? speed * speed * sinAngle * sinAngle / (2 * g)
        : speed * speed * std::sin(2 * radians) / g;
    if (!std::isfinite(result)) {
        std::cerr << "Ошибка: результат выходит за пределы допустимого диапазона.\n";
        return 1;
    }
    std::cout << (operation == "height" ? "Максимальная высота: " : "Дальность полёта: ")
              << result << " м\n";
}
