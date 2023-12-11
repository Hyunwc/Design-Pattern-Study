#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;
    string color;

public:
    Car(const string& brand, const string& model, int year, const string& color)
        : brand(brand), model(model), year(year), color(color) {}

    // Builder
    class Builder {
    private:
        string brand;
        string model;
        int year;
        string color;

    public:
        Builder& setBrand(const string& brand) {
            this->brand = brand;
            return *this;
        }

        Builder& setModel(const string& model) {
            this->model = model;
            return *this;
        }

        Builder& setYear(int year) {
            this->year = year;
            return *this;
        }

        Builder& setColor(const string& color) {
            this->color = color;
            return *this;
        }

        Car build() {
            return Car(brand, model, year, color);
        }
    };
};

int main() {
    Car::Builder br;
    Car car = br
        .setBrand("GENESIS")
        .setModel("Gv80")
        .setYear(2024)
        .setColor("NCM")
        .build();

    cout << "�� ����" << endl;
    cout << "�귣��: " << car.brand << endl;
    cout << "��: " << car.model << endl;
    cout << "����: " << car.year << endl;
    cout << "����: " << car.color << endl;

    return 0;
}