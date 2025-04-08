#include <iostream>
#include <string>
#include <vector>
using namespace std;

// --------Student-----------
class Student {
private:
    string surname;
    string name;
    int age;
    int id;

public:
    Student(string n_s, string n_n, int n_age, int n_id)
        : surname(n_s), name(n_n), age(n_age), id(n_id) {}

    string getSurname() const { return surname; }
    string getName() const { return name; }
    int getAge() const { return age; }
    int getId() const { return id; }

    void print() const {
        cout << "Фамилия: " << surname << ", Имя: " << name
             << ", Возраст: " << age << ", ID: " << id << endl;
    }
};

// --------Course-----------
class Course {
private:
    string course_name;
    int course_id;
    int max_students;
    vector<Student*> enrolled_students;

public:
    Course(string n_name, int i_id, int max)
        : course_name(n_name), course_id(i_id), max_students(max) {}

    string getCourseName() const { return course_name; }
    int getCourseId() const { return course_id; }
    int getMaxStudents() const { return max_students; }
    const vector<Student*>& getEnrolledStudents() const { return enrolled_students; }

    bool registrate_student(Student* student) {
        if ((int)enrolled_students.size() >= max_students) {
            cout << "Места на курсе закончились.\n";
            return false;
        }

        for (int i = 0; i < (int)enrolled_students.size(); i++) {
            if (enrolled_students[i]->getId() == student->getId()) {
                cout << "Студент уже записан на курс.\n";
                return false;
            }
        }

        enrolled_students.push_back(student);
        return true;
    }

    void print_course() const {
        cout << "Курс: " << course_name << " (ID: " << course_id << ")\n";
        cout << "Записанные студенты:\n";
        for (int i = 0; i < (int)enrolled_students.size(); i++) {
            enrolled_students[i]->print();
        }
    }

    void remove_student_by_id(int student_id) {
        for (int i = 0; i < (int)enrolled_students.size(); ++i) {
            if (enrolled_students[i]->getId() == student_id) {
                enrolled_students.erase(enrolled_students.begin() + i);
                --i; // чтобы не пропустить следующий элемент
            }
        }
    }
};

// --------UniversitySystem-----------
class UniversitySystem {
private:
    vector<Student> students;
    vector<Course> courses;

public:
    void add_student() {
        string surname, name;
        int age, id;

        cout << "Введите фамилию: ";
        cin >> surname;
        cout << "Введите имя: ";
        cin >> name;
        cout << "Введите возраст: ";
        cin >> age;
        cout << "Введите ID: ";
        cin >> id;

        for (int i = 0; i < (int)students.size(); ++i) {
            if (students[i].getId() == id) {
                cout << "Студент с таким ID уже существует.\n";
                return;
            }
        }

        students.push_back(Student(surname, name, age, id));
        cout << "Студент добавлен.\n";
    }

    void add_course() {
        string name;
        int id, max;

        cout << "Введите название курса: ";
        cin >> name;
        cout << "Введите ID курса: ";
        cin >> id;
        cout << "Введите максимальное количество студентов: ";
        cin >> max;

        for (int i = 0; i < (int)courses.size(); ++i) {
            if (courses[i].getCourseId() == id) {
                cout << "Курс с таким ID уже существует.\n";
                return;
            }
        }

        courses.push_back(Course(name, id, max));
        cout << "Курс добавлен.\n";
    }

    void registr_to_course() {
        int student_id, course_id;
        cout << "Введите ID студента: ";
        cin >> student_id;
        cout << "Введите ID курса: ";
        cin >> course_id;

        Student* student_ptr = NULL;
        for (int i = 0; i < (int)students.size(); ++i) {
            if (students[i].getId() == student_id) {
                student_ptr = &students[i];
                break;
            }
        }

        if (!student_ptr) {
            cout << "Студент не найден.\n";
            return;
        }

        for (int i = 0; i < (int)courses.size(); ++i) {
            if (courses[i].getCourseId() == course_id) {
                courses[i].registrate_student(student_ptr);
                return;
            }
        }

        cout << "Курс не найден.\n";
    }

    void print_students_in_course() {
        int course_id;
        cout << "Введите ID курса: ";
        cin >> course_id;

        for (int i = 0; i < (int)courses.size(); ++i) {
            if (courses[i].getCourseId() == course_id) {
                courses[i].print_course();
                return;
            }
        }

        cout << "Курс не найден.\n";
    }

    void print_student_courses() {
        int student_id;
        cout << "Введите ID студента: ";
        cin >> student_id;

        Student* target = NULL;
        for (int i = 0; i < (int)students.size(); ++i) {
            if (students[i].getId() == student_id) {
                target = &students[i];
                break;
            }
        }

        if (!target) {
            cout << "Студент не найден.\n";
            return;
        }

        cout << "Курсы студента " << target->getSurname() << ":\n";
        for (int i = 0; i < (int)courses.size(); ++i) {
            const vector<Student*>& enrolled = courses[i].getEnrolledStudents();
            for (int j = 0; j < (int)enrolled.size(); ++j) {
                if (enrolled[j]->getId() == student_id) {
                    cout << courses[i].getCourseName() << " (ID: " << courses[i].getCourseId() << ")\n";
                }
            }
        }
    }

    void remove_student() {
        int student_id;
        cout << "Введите ID студента для удаления: ";
        cin >> student_id;

        bool found = false;
        for (int i = 0; i < (int)students.size(); ++i) {
            if (students[i].getId() == student_id) {
                students.erase(students.begin() + i);
                found = true;
                break;
            }
        }

        if (found) {
            for (int i = 0; i < (int)courses.size(); ++i) {
                courses[i].remove_student_by_id(student_id);
            }
            cout << "Студент удалён.\n";
        } else {
            cout << "Студент не найден.\n";
        }
    }
};


// --------Main-----------
int main() {
    UniversitySystem system;
    int choice;

    do {
        cout << "\n==== Университетская система ====\n";
        cout << "1. Добавить студента\n";
        cout << "2. Добавить курс\n";
        cout << "3. Записать студента на курс\n";
        cout << "4. Показать студентов на курсе\n";
        cout << "5. Показать курсы студента\n";
        cout << "6. Удалить студента\n";
        cout << "0. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
            case 1: system.add_student(); break;
            case 2: system.add_course(); break;
            case 3: system.registr_to_course(); break;
            case 4: system.print_students_in_course(); break;
            case 5: system.print_student_courses(); break;
            case 6: system.remove_student(); break;
            case 0: cout << "До свидания!\n"; break;
            default: cout << "Неверный выбор.\n"; break;
        }

    } while (choice != 0);

    return 0;
}

