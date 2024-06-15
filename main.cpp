#include <iostream>
#include <Windows.h>
class Equation {
public:
    virtual void solve() = 0;
    virtual ~Equation() {}
};

class LinearEquation : public Equation {
protected:
    double a;
    double b;
public:
    LinearEquation(double coefA, double coefB) : a(coefA), b(coefB) {}

    void solve() override {
        if (a == 0) {
            if (b == 0)
                std::cout << "Рівняння має безліч розв'язків (всі значення x)" << std::endl;
            else
                std::cout << "Рівняння не має розв'язків" << std::endl;
        }
        else {
            double x = -b / a;
            std::cout << "Рівняння має один розв'язок:" << std::endl;
            std::cout << "x = " << x << std::endl;
        }
    }
};

class QuadraticEquation : public Equation {
protected:
    double a;
    double b;
    double c;
public:
    QuadraticEquation(double coefA, double coefB, double coefC) : a(coefA), b(coefB), c(coefC) {}

    void solve() override {
        if (a == 0) {
            LinearEquation linear(b, c);
            linear.solve();
        }
        else {
            double discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                std::cout << "Рівняння не має розв'язків у множині дійсних чисел" << std::endl;
            }
            else if (discriminant == 0) {
                double x = -b / (2 * a);
                std::cout << "Рівняння має один подвійний розв'язок:" << std::endl;
                std::cout << "x = " << x << std::endl;
            }
            else {
                double sqrtDiscriminant = sqrt_positive(discriminant);
                double x1 = (-b + sqrtDiscriminant) / (2 * a);
                double x2 = (-b - sqrtDiscriminant) / (2 * a);
                std::cout << "Рівняння має два розв'язки:" << std::endl;
                std::cout << "x1 = " << x1 << std::endl;
                std::cout << "x2 = " << x2 << std::endl;
            }
        }
    }

private:
    double sqrt_positive(double value) {
        double x = 1.0;
        double next_x;

        for (;;) {
            next_x = (x + value / x) / 2.0;
            if (next_x == x) {
                break;
            }
            x = next_x;
        }

        return x;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Equation* equations[] = {
        new LinearEquation(2, -3),
        new QuadraticEquation(1, -3, 2),
        new QuadraticEquation(1, 0, -4)
    };

    for (auto eq : equations) {
        eq->solve();
        delete eq;
        std::cout << std::endl;
    }

    return 0;
}
