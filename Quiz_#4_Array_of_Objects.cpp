#include <iostream>
#include <cstdlib>
#define SIZE 4
using namespace std;

// GLOBAL VARIABLE
string class_info[SIZE];

class Animal
{
public:
    string name;
    string habitat;
    string group;
    string population;
    

    void displayInfo(){
        #ifdef __linux__
            system("clear");
        #elif _WIN32
            system("CLS");
        #endif

        static int count = 0;
    
        class_info[count] = "=== ANIMAL #" + to_string(count+1) + " ===\n"
                            + "Name: " + name + "\n"
                            + "Habitat: " + habitat + "\n"
                            + "Group: " + group + "\n"
                            + "Population: " + population + "\n"
                            + "=================" + "\n";
        
        count++;
        
        for (string i : class_info)
            cout << i;
    }
};

int main()
{
    Animal animals[SIZE];

    for (int i = 0; i < SIZE - 1; i++)
    {
        cout << "Enter Name: ";
        getline(cin, animals[i].name);

        cout << "Enter Habitat: ";
        getline(cin, animals[i].habitat);

        cout << "Enter Group: ";
        getline(cin, animals[i].group);

        cout << "Enter Population: ";
        getline(cin, animals[i].population);
        
        cout << endl;
        animals[i].displayInfo();
    }

    return 0;
}