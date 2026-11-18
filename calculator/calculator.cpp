#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cout << "Usage: calculator -o|--operation height|range ANGLE SPEED\n"
                  << "ANGLE in degrees, SPEED in m/s\n";
        return 0;
    }

    if (argc != 5 || (std::string(argv[1]) != "-o" && std::string(argv[1]) != "--operation")) {
        std::cerr << "Error: expected an operation, an angle and a speed.\n";
        return 1;
    }

    const std::string operation = argv[2];
    if (operation != "height" && operation != "range") {
        std::cerr << "Error: unknown operation. Use height or range.\n";
        return 1;
    }

    char* angleEnd;
    char* speedEnd;
    const double angle = std::strtod(argv[3], &angleEnd);
    const double speed = std::strtod(argv[4], &speedEnd);
    if (angleEnd == argv[3] || *angleEnd != '\0' || speedEnd == argv[4] ||
        *speedEnd != '\0' || !std::isfinite(angle) || !std::isfinite(speed)) {
        std::cerr << "Error: angle and speed must be numbers.\n";
        return 1;
    }

    const double radians = angle * (std::acos(-1.0) / 180.0);
    const double g = 9.81;
    const double sinAngle = std::sin(radians);
    const double result = operation == "height"
        ? speed * speed * sinAngle * sinAngle / (2 * g)
        : speed * speed * std::sin(2 * radians) / g;
    std::cout << result << '\n';
}
