#include <iostream>
#include <cstring>
using namespace std;

class mstring {
private:
    char* sw;
    int len;

public:
    static const int MAX = 1000;    
    mstring() : sw(nullptr), len(0) {}
    mstring(const mstring& str1);
    mstring(const char* str1);
    ~mstring() { delete[] sw; }

    int length() const;
    bool isempty() const;
    void add(char c);
    void add(const char* c);
    void insert(char c, int i);
    void insert(const char* c, int i);
    void del(int i);
    void del(int i, int j);
    int search(const char* str) const;
    void replace(const char* sub_str, const char* new_str);
    void print() const;

    // new
    mstring operator+(const mstring& so) const;
    friend mstring operator+( const char* m, const mstring& so);
    mstring operator*(int n) const;
    friend mstring operator*(int n, const mstring& so);
    mstring& operator=(const mstring& so);
    bool operator>(const mstring& so) const;
    bool operator<(const mstring& so) const;
    bool operator>=(const mstring& so) const;
    bool operator<=(const mstring& so) const;
    bool operator==(const mstring& so) const;
    const char& operator[](int n) const;
    char& operator[](int n);
    friend istream& operator>>(istream& is, mstring& so);
    friend ostream& operator<<(ostream& os, const mstring& so);
};

mstring::mstring ( const mstring& str1){
	len = str1.len;
	sw = new char [len +1];
	for ( int i =0; i < len; i++){
		sw[i] = str1.sw[i];
	}
	sw[len] = '\0';
}

mstring::mstring(const char* str1){
	if ( str1 == nullptr){
		sw = nullptr;
		len =0;
		return;
	}
	len = strlen(str1);
	sw = new char [len +1];
	for ( int i =0; i < len; i++){
		sw[i] = str1[i];
	}
	sw[len] = '\0';
}

// new
mstring mstring::operator+(const mstring& so) const {
    int new_len = len + so.len;
    char* n_str = new char[new_len + 1];
    for ( int i =0; i < len; i++)
	    n_str[i] = sw[i];
    for ( int i =0; i < so.len; i++)
	    n_str[len + i] = so.sw[i];
    n_str[new_len] = '\0';
    return mstring(n_str);
}
mstring operator+(const char* m, const mstring& so){
    return mstring(m) + so;
}

mstring mstring::operator*(int n) const {
    if (n == 0) return mstring("");
    int new_len = len * n;
    char* n_str = new char[new_len + 1];
    int cnt =0, ind =0;
    while ( cnt != n && ind != new_len){
	    for ( int i =0; i <len; i++){
		    n_str[ind] = sw[i];
		    ++ind;
	    }
	    ++cnt;
    }
    n_str[new_len] = '\0';
    return mstring(n_str);
}

mstring operator*(int n, const mstring& so) {
    return so * n;
}

mstring& mstring::operator=(const mstring& so) {
    if (this == &so) return *this;
    delete[] sw;
    len = so.len;
    sw = new char[len + 1];
    for ( int i =0; i < len; i++)
	    sw[i] = so.sw[i];
    sw[len] = '\0';
    return *this;
}

bool mstring::operator>(const mstring& so) const {
	if ( strcmp(sw, so.sw) > 0) return true;
	else return false;
}

bool mstring::operator<(const mstring& so) const {
	if ( strcmp(sw, so.sw) < 0) return true;
	else return false;
}

bool mstring::operator>=(const mstring& so) const {
	if ( strcmp(sw, so.sw) >= 0) return true;
	else return false;
}

bool mstring::operator<=(const mstring& so) const {
	if ( strcmp(sw, so.sw) <= 0) return true;
	else return false;
}

bool mstring::operator==(const mstring& so) const {
        if ( strcmp(sw, so.sw) == 0) return true;
        return false;
}


const char& mstring::operator[](int n) const {
    return sw[n];
}

char& mstring::operator[](int n) {
    return sw[n];
}


istream& operator>>(istream& is, mstring& so) {
    delete [] so.sw;
    char* b = new char [mstring::MAX];
    int ind =0;
    char ch;
    while( is.get(ch) && ch !='\n'){
	    if ( ind >= mstring::MAX -1){
		    int n_len = (mstring::MAX) * 2;
		    char *n_b = new char [n_len];
		    for ( int i =0; i < ind; i++)
			    n_b[i] = b[i];
		    delete [] b;
		    b = n_b;
	    }
	    b[ind++] = ch;
    }
    b[ind] = '\0';
    so.len = ind;
    so.sw = new char [ so.len +1];
    for ( int i =0; i < so.len; i++)
	    so.sw[i] = b[i];
    so.sw[so.len] = '\0';
    delete [] b;
    return is;
}

ostream& operator<<(ostream& os, const mstring& so) {
    for ( int i =0; i < so.len ; i++)
	    os << so.sw[i];
    return os;
}

int mstring::length() const{
	return len;
}

bool mstring::isempty() const{
    return len == 0;
}

void mstring::add(char c){
	char* n_str = new char[len + 2];
	for ( int i=0; i < len; i++){
		n_str[i] = sw[i];
	}
	n_str[len] = c;
	n_str[len + 1] = '\0';
	delete [] sw;
	sw = n_str;
	++len;
}
void mstring::add(const char* c){
	int n_len = strlen(c);
	int new_len = n_len + len;
	char* n_str = new char[new_len + 1];

	for ( int i = 0; i < len; i++){
		n_str[i] = sw[i];
	}

	// [0, n_len)
	for ( int i = 0; i < n_len; i++){
		n_str[len + i] = c[i];
	}
	n_str[new_len] = '\0';
	delete [] sw;
	sw = n_str;
	len = new_len;
}

void mstring::insert(char c, int i){
	char* n_str = new char[len +2];
	// [0, i), c, [i, n)
	for ( int j =0; j < i; j++)
		n_str[j] = sw[j];
	n_str[i] = c;

	for ( int j = i; j < len; j++)
		n_str[j + 1] = sw[j];

	n_str[len + 1] = '\0';
	delete [] sw;
	sw = n_str;
	++ len;
}

void mstring::insert(const char* c, int i){
	int c_len = strlen(c);
	int new_len = c_len + len;
	char* n_str = new char[new_len + 1];
	for ( int j =0; j < i; j++)
		n_str[j] = sw[j];
	for ( int j =0; j < c_len; j++)
		n_str[i + j] = c[j];
	for ( int j = i; j < len; j++)
		n_str[c_len + j] = sw[j];
	n_str[new_len] = '\0';
	delete [] sw;
	sw = n_str;
	len = new_len;
}

void mstring::del(int i){
	char* n_str = new char [len];
	int ind =0;
	for ( int j =0; j < len; j++){
		if ( j != i){
			n_str[ind] = sw[j];
			++ind;
		}
	}
	n_str[len-1] = '\0';
	delete [] sw;
	sw = n_str;
	--len;
}
void mstring::del(int i, int j){
	int n_len = len - ( j - i + 1);
	char* n_str = new char [n_len + 1];
	int ind =0;
	for ( int h =0; h < len; h++){
		if ( h < i || h > j){
			n_str[ind] = sw[h];
			++ind;
		}
	}
	n_str[n_len] = '\0';
	delete [] sw;
	sw = n_str;
	len = n_len;
}


int mstring::search( const char* str) const{
	int str_len = strlen(str);
	if ( str_len > len) return -1;
	for ( int i =9; i <= len - str_len; i++){
		bool fnd = true;
		for ( int j =0; j < str_len; j++){
			if (sw[i + j] != str[j]){
				fnd = false;
				break;
			}
		}
		if ( fnd == true)
			return i;
	}
	return -1;
}

void mstring::replace(const char* sub_str, const char* new_str){
	int p = search(sub_str); // position
	if ( p == -1)
		return;
	int ind =0;
	int sub_len = strlen(sub_str);
	int new_len = strlen(new_str);
	int n_len = len - sub_len + new_len;
	char* n_str = new char[ n_len + 1];
	for ( int i =0; i < p; i++){
		n_str[ind] = sw[i];
		++ind;
	}
	for ( int i =0; i < new_len; i++){
		n_str[ind] = new_str[i];
		++ind;
	}
	for ( int i = p + sub_len; i< len; i++){
		n_str[ind] = sw[i];
		++ind;
	}
	n_str[n_len] = '\0';
	delete [] sw;
	sw = n_str;
	len = n_len;
}

void mstring::print() const{
	cout << sw << endl;
}
/*
int main() {
    mstring u("Hello"), v("world!"), w(v), z;

    cout << "u + v = " << u + " " + v << endl;
    if (u == w)
        w = 2 * u + w;
    else
        w = u + v * 2;
    cout << "w = " << w << endl;
    w[10] = '?';
    cout << "w = " << w << endl;
    cin >> z;
    cout << "z = " << z << endl;
    return 0;
} */
