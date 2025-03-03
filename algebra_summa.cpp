#include <iostream>
#include <cmath>


double betta ( double z, double b, double a, double bet){
	double x;
	x = pow(z,3) - b + pow (a,2) / pow(tan(bet),2);
	return x;
}

using namespace std;
int main(){
	int x;
	cout << "Введите количесто иксов: ";
	cin >> x;
	cout << endl;
	double z,b,a, bet, s=0;
	for ( int i =1; i <= x; i++){
		cout << "Введите значения Z, B, A, Betta для X" << i << ":" << endl;
		cout << "Z = ";
		cin >> z;
		cout << "B = ";
		cin >> b;
		cout << "A = ";
		cin >> a;
		cout << "Betta =";
		cin >> bet;
		s += betta(z,b,a,bet);
	}
	cout << "y = " << s << endl;
	return 0;
}
		
