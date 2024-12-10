#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Problem {
    std::string name;
    std::string speciality;
    int duration;
    int priority;

    bool operator<(const Problem& problem) const {
        return this->priority < problem.priority;
    }
};

struct Doctor {
    std::string name;
    std::string speciality;
    std::vector<Problem> assignedProblems;
    int timeLeft = 8;

    int getProblemCount() {
        return assignedProblems.size();
    }
};

int main()
{
    std::priority_queue<Problem> problems;
    std::vector<Doctor> doctors;

    ifstream inFile("input.txt");

    int no_problems, no_doctors;    
    string name, speciality;
    int duration, priority;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> duration;
        inFile >> priority;

        struct Problem problem = { name, speciality, duration, priority };
        problems.push(problem);

        //cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
            
        struct Doctor doctor = { name, speciality };
        doctors.push_back(doctor);

        //cout << name << ' ' << speciality << '\n';
    }

    //std::cout << "\n Rezolvare: \n";

    while (!problems.empty()) {
        Problem problem = problems.top();

        for (auto& doc : doctors) {
            if (problem.speciality == doc.speciality) {
                if (doc.timeLeft - problem.duration >= 0) {
                    doc.assignedProblems.push_back(problem);
                    doc.timeLeft -= problem.duration;

                    break;
                }
            }
        }

        problems.pop();
    }

    std::for_each(doctors.begin(), doctors.end(), [](struct Doctor doc) {
        if (doc.getProblemCount() > 0) {
            string problemsStr;
            std::for_each(doc.assignedProblems.begin(), doc.assignedProblems.end(), [&problemsStr](struct Problem p) {
                problemsStr += p.name + " ";
            });

            std::cout << doc.name << " " << doc.getProblemCount() << " " << problemsStr << std::endl;
        }
    });

    return 0;
}