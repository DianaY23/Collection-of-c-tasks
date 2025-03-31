#include <iostream>
using namespace std;


class error{
	private:
		int num;
	public:
		error ( int n_num) : num(n_num) {}
		void print () const;
};

void error:: print() const{
	switch (num){
		case 1: cout << "Division by zero!" << endl; break;
		case 2: cout <<"Invalid index!" << endl; break;
	}
}

class Transform3D{
	private:
		double x, y, z;
	public:
		Transform3D( double n_x, double n_y, double n_z) : x(n_x), y(n_y), z(n_z) {}
		const Transform3D operator+( const Transform3D& vec) const;
		const Transform3D operator-(const Transform3D& vec) const;
		Transform3D operator*( double a) const;
//		friend Transform3D operator* ( double a, const Transform3D& vec);
		Transform3D operator/ ( double a);
		const Transform3D& operator=(const Transform3D& vec);
		bool operator==(const Transform3D& vec) const;
		double operator[](int n);
		friend ostream& operator<<(ostream& os, const Transform3D& vec);
};

const Transform3D Transform3D:: operator+( const Transform3D& vec) const{
	return Transform3D(x + vec.x, y+ vec.y, z + vec.z);
}

const Transform3D  Transform3D:: operator-( const Transform3D& vec) const{
	return Transform3D(x - vec.x, y - vec.y, z - vec.z);
}

Transform3D Transform3D::  operator*( double a) const{
	return Transform3D( x * a, y * a, z * a);
}
/*
Transform3D  Transform3D::  operator* ( double a, const Transform3D& vec){
	return Transform3D(vec.x * a, vec.y * a, vec.z *a);
} */

Transform3D  Transform3D:: operator/ ( double a){
	if ( a ==0)
		throw error(1);
	else
		return Transform3D( x / a, y / a, z / a);
}


const Transform3D& Transform3D:: operator=(const Transform3D& vec){
	if ( this == &vec)
		return *this;
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

bool Transform3D:: operator==(const Transform3D& vec) const{
	if ( x != vec.x || y != vec.y || z != vec.z)
		return false;
	else
		return true;
}

double Transform3D:: operator[](int n){
	if ( n == 0)
		return x;
	else if (n == 1)
		return y;
	else if ( n == 2)
		return z;
	else
		throw error(2);
}

ostream& operator<< ( ostream& os, const Transform3D& vec){
	os <<"( " << vec.x << ", " << vec.y << ", " << vec.z << ")" << endl;
	return os;
}

int main() {
    Transform3D t1(1.2, 3.4, 5.6);
    Transform3D t2(0.8, -1.4, 2.4);

    // Проверка оператора +
    Transform3D t3 = t1 + t2;
    cout << t3 << endl;  
    // Вывод: (2, 2, 8)

    // Проверка оператора *
    t3 = t1 * 2;
    cout << t3 << endl;  
    // Вывод: (2.4, 6.8, 11.2)

    // Проверка исключения при делении на 0
    try {
        t3 = t1 / 0;  // Ошибка: деление на ноль
    } catch (const error& e) {
	    e.print();
	return 1;
    }

    return 0;
}
