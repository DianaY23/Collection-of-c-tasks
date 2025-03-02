#include <iostream>
#include <cstring>
using namespace std;

class mstring{
	private:
		char* sw;
		int len;
	public:
		mstring ():  sw(nullptr), len(0) {}
		mstring( const mstring& str1) {
			len = str1.len;
			sw = new char [len +1];
			for ( int i =0; i < len; i++){
				sw[i] = str1.sw[i];
			}
			sw[len] = '\0';
		}
		mstring(const char* str1) {
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
		~mstring() {
			if ( sw != nullptr)
				delete [] sw;
		}
		int length() const;
		bool isempty() const;
		void add(char c);
		void add(const char* c);
		void insert(char c, int i);
		void insert(const char*c, int i);
		void del(int i);
		void del(int i, int j);
		int search(const char* str) const;
		void replace(const char* sub_str, const char* new_str);
		void print() const;

};

int mstring::length() const{
	return len;
}

bool mstring::isempty() const{
    /*
	if (len == 0)
		return true;
	else
		return false;
		*/
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

	// text: [0, n)
	// pat: [0, m)
	// [n - m, n)

	for ( int i =0; i <= len - str_len; i++){
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

//
//int main()
//{
//        mstring s ("hello world");
//        mstring s1 = s;
//        mstring s2;
//        cout << s.length() << endl;
//        if (s2.isempty())
//        {
//          s.add('!');
//          s2.add("HI!");
//          s.print();
//          s2.print();
//        }
//        if (!s1.isempty())
//        {
//           s1.insert(' ',5);
//           s1.insert('m',6);
//           s1.insert('y',7);
//           s.insert(" my",5);
//           s.print();
//           s1.print();
//        }
//        s.del(9);
//        s1.del(5,7);
//        s.print();
//        s1.print();
//
//        mstring ms1 { "buba" };
//        ms1.print();
//        ms1.add("gop");
//        ms1.print();
//
//        for (int i = 0; i != ms1.length() + 1; ++i) {
//            mstring ms1copy { ms1 };
//            ms1copy.insert('D', i);
//            cout << i << " ";
//            ms1copy.print();
//        }
//
//        for (int i = 0; i != ms1.length() + 1; ++i) {
//            mstring ms1copy { ms1 };
//            ms1copy.insert("DD", i);
//            cout << i << " ";
//            ms1copy.print();
//        }
//
//
//        for (int i = 0; i != ms1.length(); ++i) {
//            mstring ms1copy { ms1 };
//            ms1copy.del(i);
//            cout << i << " ";
//            ms1copy.print();
//        }
//
//        for (int i = 0; i != ms1.length(); ++i) {
//            for (int j = i; j != ms1.length(); ++j) {
//                mstring ms1copy { ms1 };
//                ms1copy.del(i, j);
//                cout << i << " " << j << " ";
//                ms1copy.print();
//            }
//        }
//
//
//        return 0;
//}
