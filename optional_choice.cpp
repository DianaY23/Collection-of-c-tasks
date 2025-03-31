#include <iostream>
#include <string>
using namespace std;

template <typename T>

T best_choice(T* arr, int size){
	T max = arr[0];
	for ( int i =1; i < size; i++){
		if ( arr[i] >= max)
			max = arr[i];
	}
	return max;
}

template <>

string best_choice(string* str, int size){
	string*  m_len = &str[0];
	for ( int i =1; i < size; i++){
		if ( str[i].size() >= m_len -> length())
			m_len = &str[i];
	}
	return *m_len;
}


int main() {
    int numbers[] = {3, 9, 1, 7, 5};
    cout << best_choice(numbers, 5) << endl;

    string words[] = {"apple", "banana", "kiwi", "strawberry"};
    cout << best_choice(words, 4) << endl;

    return 0;
}
