#include <iostream>
#include <sqlite3.h>
#include <string>
#include <sstream>

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << "--------------------------" << endl;
    return 0;
}

void executeSQL(sqlite3 *db, const string &sql) {
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("med_clinic.db", &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    } else {
        cout << "Opened database successfully.\n";
    }

    // Создание таблиц
    string createPatients = "CREATE TABLE IF NOT EXISTS Patients ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "name TEXT NOT NULL,"
                            "birthdate TEXT NOT NULL);";

    string createObservations = "CREATE TABLE IF NOT EXISTS Observations ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "patient_id INTEGER,"
                                "datetime TEXT,"
                                "temperature REAL,"
                                "blood_pressure_sys INTEGER,"
                                "blood_pressure_dia INTEGER,"
                                "glucose_level REAL,"
                                "FOREIGN KEY(patient_id) REFERENCES Patients(id));";

    executeSQL(db, createPatients);
    executeSQL(db, createObservations);

    string name, birthdate;
    cout << "Введите имя пациента: ";
    getline(cin, name);
    cout << "Введите дату рождения (ГГГГ-ММ-ДД): ";
    getline(cin, birthdate);

    stringstream ss;
    ss << "INSERT INTO Patients (name, birthdate) VALUES ('" << name << "', '" << birthdate << "');";
    executeSQL(db, ss.str());

    cout << "\nСписок пациентов:\n";
    executeSQL(db, "SELECT * FROM Patients;");

    sqlite3_close(db);
    return 0;
}
