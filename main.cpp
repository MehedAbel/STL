#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Problem {
    std::string name;
    std::string speciality;
};

struct Doctor {
    std::string name;
    std::string speciality;
};

int main()
{
    std::vector<Problem> problems;
    std::vector<Doctor> doctors;

    ifstream inFile("input.txt");

    int no_problems, no_doctors;    
    string name, speciality;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;

        struct Problem problem = { name, speciality };
        problems.push_back(problem);

        cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
            
        struct Doctor doctor = { name, speciality };
        doctors.push_back(doctor);

        cout << name << ' ' << speciality << '\n';
    }

    std::cout << "\n Rezolvare: \n";

    for (auto& problem : problems) {
        std::string speciality = problem.speciality;
        std::string name = problem.name;
        int status = 0;
        
        for (auto& doctor : doctors) {
            if (speciality == doctor.speciality) {
                status = 1;
                break;
            } 
        }

        if (status == 1) {
            std::cout << name << " Accepted" << std::endl;
        }
        else {
            std::cout << name << " Rejected" << std::endl;
        }
    }

    return 0;
}