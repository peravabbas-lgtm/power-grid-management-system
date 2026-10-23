#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_DISTRICTS = 100;
const int MAX_TECHS = 50;

struct district {
    string name;
    string type;
    int num_resident;
    int power;
    bool has_power;
    int num_technician;
    string technicians[MAX_TECHS];
};

void sort_by_residents(district a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (a[j].num_resident > a[j + 1].num_resident) {
                district temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int find_district(district a[], int n, const string& name) {
    for (int i = 0; i < n; ++i) {
        if (a[i].name == name) {
            return i;
        }
    }
    return -1;
}

void load(string fname, district districts[], int& num, int& power) {

    for (int i = 0; i < num; i++) {
        districts[i].name = "";
        districts[i].type = "";
        districts[i].num_resident = 0;
        districts[i].power = 0;
        districts[i].has_power = 0;
        districts[i].num_technician = 0;
        for (int t = 0; t < 10; t++) {
            districts[i].technicians[t] = "";
        }
    }

    ifstream fin(fname.c_str());
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        num = 0;
        power = 0;
        return;
    }

    fin >> power;
    fin >> num;
    fin.ignore();

    for (int i = 0; i < num; ++i) {
        getline(fin, districts[i].name);
        getline(fin, districts[i].type);
        fin >> districts[i].num_resident;
        fin >> districts[i].power;
        fin >> districts[i].has_power;
        fin >> districts[i].num_technician;
        fin.ignore();

        for (int t = 0; t < districts[i].num_technician; ++t) {
            getline(fin, districts[i].technicians[t]);
        }
    }
    fin.close();
    sort_by_residents(districts, num);
}

void save(string fname, district districts[], int num, int power) {
    ofstream fout(fname.c_str());
    fout << power << endl;
    fout << num << endl;

    for (int i = 0; i < num; ++i) {
        fout << districts[i].name << endl;
        fout << districts[i].type << endl;
        fout << districts[i].num_resident << endl;
        fout << districts[i].power << endl;
        fout << districts[i].has_power << endl;
        fout << districts[i].num_technician << endl;

        for (int t = 0; t < districts[i].num_technician; ++t) {
            fout << districts[i].technicians[t] << endl;
        }
    }
    fout.close();
}

void print_all(district districts[], int num, int power) {
    cout << "The current power supply is " << power << "MW." << endl;
    for (int i = 0; i < num; ++i) {
        cout << districts[i].name << endl;
        cout << "District type: " << districts[i].type << endl;
        cout << "Number of residents: " << districts[i].num_resident << endl;
        if (districts[i].has_power) {
            cout << "Power use: " << districts[i].power << "MW" << endl;
        }
        else {
            cout << "Power use: 0MW" << endl;
        }
        cout << "Has power: " << districts[i].has_power << endl;
        if (districts[i].num_technician > 0) {
            cout << "Technicians: ";
            for (int t = 0; t < districts[i].num_technician; ++t) {
                cout << districts[i].technicians[t];
                if (t != districts[i].num_technician - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "---" << endl;
    }
    int demand = 0;
    for (int i = 0; i < num; ++i) {
        if (districts[i].has_power) {
            demand += districts[i].power;
        }
    }
    if (power < demand) {
        cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << demand << "MW of power demand. Please shut off one or more districts." << endl;
        cout << "---" << endl;
    }
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district) {
    int idx = find_district(districts, num_district, district_name);
    if (idx == -1) {
        cout << "Error! The district with that name doesn't exist." << endl;
        return;
    }
    if (districts[idx].num_technician < MAX_TECHS) {
        districts[idx].technicians[districts[idx].num_technician] = tech_name;
        districts[idx].num_technician++;
        cout << "Technician assigned!" << endl;
    }
}

void cut_power(string district_name, district districts[], int num_district) {
    int idx = find_district(districts, num_district, district_name);
    if (idx == -1) {
        cout << "Error! The district with that name doesn't exist." << endl;
    }
    else {
        districts[idx].has_power = 0;
        cout << "The district's power has been successfully turned off." << endl;
    }
}

void restore_power(string district_name, district districts[], int num_district) {
    int idx = find_district(districts, num_district, district_name);
    if (idx == -1) {
        cout << "Error! The district with that name doesn't exist." << endl;
    }
    else {
        districts[idx].has_power = 1;
        cout << "The district's power has been successfully turned back on." << endl;
    }
}


int main() {

    district districts[MAX_DISTRICTS];
    int num = 0;
    int power = 0;
    string fname;

    cout << "Please enter the name of the file to load:" << endl;
    cin >> fname;
    load(fname, districts, num, power);

    print_all(districts, num, power);

    int choice;
    while (true) {
        cout << "Main Menu" << endl << "1- Status" << endl << "2- Set Power Supply" << endl << "3- Shutoff Power" << endl << "4- Restore Power" << endl << "5- Assign Technician" << endl << "6- Save" << endl << "7- Load" << endl << "8- Exit" << endl << "Please enter your choice:" << endl;
        cin >> choice;

        if (choice == 1) {
            print_all(districts, num, power);
        }
        else if (choice == 2) {
            cout << "Enter the updated power supply in megawatts:" << endl;
            cin >> power;
        }
        else if (choice == 3) {
            cout << "Enter the name of the district:" << endl;
            cin.ignore();
            string dname;
            getline(cin, dname);
            cut_power(dname, districts, num);
        }
        else if (choice == 4) {
            cout << "Enter the name of the district:" << endl;
            cin.ignore();
            string dname;
            getline(cin, dname);
            restore_power(dname, districts, num);
        }
        else if (choice == 5) {
            cout << "Enter the name of the technician:" << endl;
            cin.ignore();
            string tech;
            getline(cin, tech);
            cout << "Enter the name of the district to assign them to:" << endl;
            string dname;
            getline(cin, dname);
            assign_technician(tech, dname, districts, num);
        }
        else if (choice == 6) {
            cout << "Enter the file name to save to:" << endl;
            cin >> fname;
            save(fname, districts, num, power);
        }
        else if (choice == 7) {
            cout << "Enter the file name to load from:" << endl;
            cin >> fname;
            load(fname, districts, num, power);
        }
        else if (choice == 8) {
            break;
        }
        else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}
