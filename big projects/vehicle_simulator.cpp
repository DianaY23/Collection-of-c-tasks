#include <iostream>
#include <string>
using namespace std;

// ---------- Класс error ----------
class error {
private:
    int num;
public:
    error(int n_num);
    void print() const;
};

error::error(int n_num) : num(n_num) {}

void error::print() const {
    if (num == 1)
        cout << "Ошибка: недостаточно топлива!" << endl;
    else if (num == 2)
        cout << "Ошибка: самолёт не может взлететь без топлива!" << endl;
    else
        cout << "Неизвестная ошибка!" << endl;
}

// ---------- Абстрактный класс Vehicle ----------
class Vehicle {
protected:
    string name;
    double speed;
    double milage;
public:
    Vehicle(string n_name, double n_speed, double n_milage = 0);
    virtual ~Vehicle();

    virtual void move() = 0;

    string getName() const;
    double getSpeed() const;
    double getMilage() const;
    void addMilage(double km);

    double operator+(const Vehicle& op) const;
    bool operator-(const Vehicle& op) const;

    virtual void print(ostream& os) const;
    friend ostream& operator<<(ostream& os, const Vehicle& op);
};

Vehicle::Vehicle(string n_name, double n_speed, double n_milage)
    : name(n_name), speed(n_speed), milage(n_milage) {}

Vehicle::~Vehicle() {}

string Vehicle::getName() const { return name; }
double Vehicle::getSpeed() const { return speed; }
double Vehicle::getMilage() const { return milage; }
void Vehicle::addMilage(double km) { milage += km; }

double Vehicle::operator+(const Vehicle& op) const {
    return this->milage + op.milage;
}

bool Vehicle::operator-(const Vehicle& op) const {
    return this->speed > op.speed;
}

void Vehicle::print(ostream& os) const {
    os << "Vehicle: " << name << " , Speed: " << speed << " , Mileage: " << milage;
}

ostream& operator<<(ostream& os, const Vehicle& op) {
    op.print(os);
    return os;
}

// ---------- Класс Car ----------
class Car : public Vehicle {
private:
    double fuel;
public:
    Car(string n_name, double n_speed, double n_fuel);
    void move();
    void print(ostream& os) const;
};

Car::Car(string n_name, double n_speed, double n_fuel)
    : Vehicle(n_name, n_speed), fuel(n_fuel) {}

void Car::move() {
    if (fuel <= 0)
        throw error(1);
    fuel -= 1;
    addMilage(10);
}

void Car::print(ostream& os) const {
    os << "Car: " << name << " , Speed: " << speed
       << " , Fuel: " << fuel << " , Mileage: " << milage;
}

// ---------- Класс Bicycle ----------
class Bicycle : public Vehicle {
public:
    Bicycle(string n_name, double n_speed);
    void move();
    void print(ostream& os) const;
};

Bicycle::Bicycle(string n_name, double n_speed)
    : Vehicle(n_name, n_speed) {}

void Bicycle::move() {
    addMilage(5);
}

void Bicycle::print(ostream& os) const {
    os << "Bicycle: " << name << " , Speed: " << speed << " , Mileage: " << milage;
}

// ---------- Класс Airplane ----------
class Airplane : public Vehicle {
private:
    double fuel;
    double altitude;
public:
    Airplane(string n_name, double n_speed, double n_fuel);
    void move();
    void print(ostream& os) const;
};

Airplane::Airplane(string n_name, double n_speed, double n_fuel)
    : Vehicle(n_name, n_speed), fuel(n_fuel), altitude(0) {}

void Airplane::move() {
    if (fuel <= 0)
        throw error(2);
    fuel -= 2;
    altitude += 1000;
    addMilage(50);
}

void Airplane::print(ostream& os) const {
    os << "Airplane: " << name << " , Speed: " << speed
       << " , Fuel: " << fuel << " , Altitude: " << altitude
       << " , Mileage: " << milage;
}

// ---------- main ----------
int main() {
    try {
        Car car("BMW", 150, 2);
        Bicycle bike("Trek", 25);
        Airplane plane("Boeing", 900, 4);

        car.move();
        bike.move();
        plane.move();

        cout << car << endl;
        cout << bike << endl;
        cout << plane << endl;

        cout << "\nСуммарный пробег car + bike = " << (car + bike) << " км" << endl;

        if (car - bike)
            cout << car.getName() << " быстрее " << bike.getName() << endl;
        else
            cout << bike.getName() << " быстрее или равен по скорости " << car.getName() << endl;

        car.move(); // топливо 1 -> 0
        car.move(); // ошибка

    } catch (const error& e) {
        e.print();
    } catch (...) {
        cout << "Неизвестная ошибка!" << endl;
    }

    return 0;
}

