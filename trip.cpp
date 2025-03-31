#include <iostream>
#include <string>
using namespace std;

class Trip{
	private:
		string name;
		int year, month, day;
	public:
		Trip ( string n_name, int n_year, int n_month, int n_day) : name(n_name), year(n_year), month(n_month), day(n_day) {}
		virtual void print_info() const =0;
		void change_date(int new_year, int new_month, int new_day);

		string get_name () const { return name;}
		int get_year () const { return year;}
		int get_month () const { return month;}
		int get_day () const { return day;}
};

void Trip:: change_date( int new_year, int new_month, int new_day){
	year = new_year;
	month = new_month;
	day = new_day;
}

class HikingTrip: public Trip{
	private:
		int difficulty;
	public:
		HikingTrip ( string n_name, int n_year, int n_month, int n_day, int n_dif);
		virtual void print_info() const;
		void change_difficulty( int new_difficulty);
};


HikingTrip:: HikingTrip ( string n_name, int n_year, int n_month, int n_day, int n_dif) : Trip ( n_name, n_year, n_month, n_day){
	this->difficulty = n_dif;
}


void HikingTrip:: print_info () const{
	cout << get_name() << " " << get_year() << " " << get_month() << " ";
	cout << get_day() << " Difficulty " << difficulty << endl;
}

void HikingTrip:: change_difficulty ( int new_difficulty){
	difficulty = new_difficulty;
}

class KayakingTrip: public Trip{
	private:
		bool isExtreme;
		int level;
	public:
		KayakingTrip ( string n_name, int n_year, int n_month, int n_day, int n_level);
		virtual void print_info() const;
		void change_type( int danger_level);
};

KayakingTrip:: KayakingTrip ( string n_name, int n_year, int n_month, int n_day, int n_level) : Trip ( n_name, n_year, n_month, n_day){
	this-> level = n_level;
}

void KayakingTrip:: change_type( int danger_level){
	this-> level = danger_level;
	if ( level >= 7)
		isExtreme = true;
	else
		isExtreme = false;
}

void KayakingTrip:: print_info() const{
	cout << get_name() << " " << get_year() << " " << get_month() << " ";
	cout << get_day() << " ";
	if ( isExtreme == true)
		cout << "Extreme" << endl;
	else 
		cout <<"Regular" << endl;
}

int main() {
    HikingTrip hike("ГорныйПеревал", 2025, 7, 14, 3);
    hike.print_info();  

    hike.change_difficulty(5);
    hike.print_info();  

    KayakingTrip kayak("БурнаяРека", 2023, 9, 5, 8);
    kayak.print_info();  

    kayak.change_type(4);
    kayak.print_info();  

    return 0;
}
