#include <iostream>
#include <list>
#include <string>
using namespace std;

class error{
	private:
		int num;
	public:
		error ( int n_num) : num(n_num) {}
		void print_error() const;
};

void error::print_error() const{
	switch (num){
		case 1: cerr << "Все клиенты обслужены!" << endl; break;
		default: cerr <<"Неизвестная ошибка (" << endl; break;
	}
}
class Queue{
	private:
		list<string> name;
	public:
		void addClient( const string& client);
		void addVipClient(const string& client);
		void serve();
		void print() const;
};

void Queue::addClient(const string& client){
	name.push_back(client);
}

void Queue::addVipClient(const string& client){
	name.push_front(client);
}

void Queue::serve(){
	if ( name.empty())
		throw error(1);
	name.pop_front();
	cout <<"Клиент обслужен!"<< endl;
}

void Queue::print() const{
	if (name.empty()){
		cout <<"Очередь пусту!" << endl;
		return;
	}

	cout <<"Текущая очередь: ";
	for ( list<string>::const_iterator i = name.begin(); i != name.end(); i++)
		cout << *i << " ";
	cout << endl;
}

int main() {
    Queue q;
    q.addClient("Alice");
    q.addClient("Bob");
    q.addClient("Charlie");

    q.addVipClient("David");

    cout << "До обслуживания:" << endl;
    q.print();

    try {
        q.serve(); // Обслужить VIP-клиента (David)
        q.serve(); // Обслужить Alice
    } catch (const error& e) {
        e.print_error(); // Печать ошибки, если очередь пуста
    }

    cout << "После обслуживания:" << endl;
    q.print();

    try {
        q.serve(); // Обслужить Bob
        q.serve(); // Обслужить Charlie
    } catch (const error& e) {
        e.print_error(); // Печать ошибки, если очередь пуста
    }

    // Попытка обслужить клиента, когда очередь пуста
    try {
        q.serve();
    } catch (const error& e) {
        e.print_error(); // Ошибка, если очередь пуста
    }

    return 0;
}
