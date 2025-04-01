#include <iostream>
#include <cmath>  
using namespace std;

class TimePeriod {
private:
    int hour, minute;

public:
    TimePeriod(int n_hour, int n_minute) : hour(n_hour), minute(n_minute) {}

    friend ostream& operator<<(ostream& os, const TimePeriod& op);
    const TimePeriod operator+(const TimePeriod& op) const;
    const TimePeriod operator-(const TimePeriod& op) const;
    TimePeriod& operator++();
    TimePeriod operator++(int);
    TimePeriod& operator--();
    TimePeriod operator--(int);
    bool operator==(const TimePeriod& op) const;
};

ostream& operator<<(ostream& os, const TimePeriod& op) {
    if (op.hour < 10)
        os << "0" << op.hour;
    else
        os << op.hour;
    os << "h:";
    if (op.minute < 10)
        os << "0" << op.minute;
    else
        os << op.minute;
    os << "m";
    return os;
}

const TimePeriod TimePeriod::operator+(const TimePeriod& op) const {
    int ost = 0;
    TimePeriod res(hour, minute);
    if (res.minute + op.minute >= 60) {
        res.minute = (res.minute + op.minute) - 60;
        ost = 1;
    } else {
        res.minute += op.minute;
    }
    
    if (res.hour + op.hour + ost >= 24)
        res.hour = (res.hour + op.hour + ost) - 24;
    else
        res.hour = res.hour + op.hour + ost;

    return res;
}

const TimePeriod TimePeriod::operator-(const TimePeriod& op) const {
    int ost = 0;
    TimePeriod res(hour, minute);

    if (res.minute < op.minute && res.hour < op.hour) {
        res.hour = 0;
        res.minute = 0;
    } else {
        if (res.minute < op.minute) {
            ost = 1;
            res.minute = abs(res.minute - op.minute);
            res.hour = abs(res.hour - op.hour - ost);
        } else {
            res.hour -= op.hour;
            res.minute -= op.minute;
        }
    }
    return res;
}

TimePeriod& TimePeriod::operator++() {
    if (minute == 59) {
        minute = 0;
        ++hour;
    } else {
        ++minute;
    }
    return *this;
}

TimePeriod TimePeriod::operator++(int) {
    TimePeriod res(hour, minute);
    if (res.minute == 59) {
        res.minute = 0;
        res.hour += 1;
    } else {
        res.minute += 1;
    }
    return res;
}

TimePeriod& TimePeriod::operator--() {
    if (minute == 0) {
        minute = 59;
        --hour;
    } else {
        --minute;
    }
    return *this;
}

TimePeriod TimePeriod::operator--(int) {
    TimePeriod res(hour, minute);
    if (res.minute == 0) {
        res.minute = 59;
        res.hour -= 1;
    } else {
        res.minute -= 1;
    }
    return res;
}

bool TimePeriod::operator==(const TimePeriod& op) const {
    return hour == op.hour && minute == op.minute;
}

int main() {
    TimePeriod t1(9, 15);
    TimePeriod t2(17, 0);

    cout << t1 << endl;
    cout << t2 << endl;

    TimePeriod t3 = t1 + t2;
    cout << "t1 + t2: " << t3 << endl;

    TimePeriod t4 = t1 - t2;
    cout << "t1 - t2: " << t4 << endl;

    cout << "++t1: " << ++t1 << endl;
    cout << "t1++: " << t1++ << endl;
    cout << "t1 после t1++: " << t1 << endl;

    cout << "--t2: " << --t2 << endl;
    cout << "t2--: " << t2-- << endl;
    cout << "t2 после t2--: " << t2 << endl;

    return 0;
}

