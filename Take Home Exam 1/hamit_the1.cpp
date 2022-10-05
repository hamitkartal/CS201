//HAMİT KARTAL 28404
#include <iostream>
#include <string>
using namespace std;
int main(){
    string name, course, first_time, current_grade, convert, previous_grade, wanted_grade;
    cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
    cin >> name;
    cout << "Hello " << name << "! Please enter the name of the course to be processed: ";
    cin >> course;
    cout << "Hello " << name << "! If you take the " << course << " for the first time, enter YES otherwise NO: ";
    cin >> first_time;
    if (first_time == "YES"){
        cout << "What is your grade from (A,B,C,D,F)? ";
        cin >> current_grade;
        if (current_grade == "A" || current_grade == "B" || current_grade == "C" || current_grade == "D"){
            cout << "Do you want to switch your grade from " << current_grade << " to S (YES or NO)? ";
            cin >> convert;
            if (convert == "YES"){
                cout << name << ", your final grade for " << course << " is S. Goodbye..." << endl;
            }else if (convert == "NO"){
                cout << name << ", your final grade for " << course << " is " << current_grade << ". Goodbye..." << endl;
            }else{
                cout << "Invalid grade selection. Goodbye..." << endl;
            }
        }else if (current_grade == "F"){
            cout << "Do you want to switch your grade from F to U (YES or NO)? ";
            cin >> convert;
            if (convert == "YES"){
                cout << name << ", your final grade for " << course << " is U. Goodbye..." << endl;
            }else if (convert == "NO"){
                cout << name << ", your final grade for " << course << " is F. Goodbye..." << endl;
            }else{
                cout << "Invalid grade selection. Goodbye..." << endl;
            }
        }else{
            cout << "Invalid grade selection. Goodbye..." << endl;
        }
    }else if (first_time == "NO"){
        cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
        cin >> previous_grade;
        if (previous_grade == "A" || previous_grade == "B" || previous_grade == "C" || previous_grade == "D" || previous_grade == "F" || previous_grade == "S" || previous_grade == "U"){
            cout << "Please enter your current grade from (A,B,C,D,F): ";
            cin >> current_grade;
            if (current_grade == "A" || current_grade == "B" || current_grade == "C" || current_grade == "D" || current_grade == "F"){
                cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
                cin >> wanted_grade;
                if (wanted_grade == "A" || wanted_grade == "B" || wanted_grade == "C" || wanted_grade == "D" || wanted_grade == "F" || wanted_grade == "S" || wanted_grade == "U"){
                    if (previous_grade == "S" && current_grade == "F" && wanted_grade != "F"){
                        cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
                    }else if ((previous_grade == "U" && (current_grade == "A" || current_grade == "B" || current_grade == "C" || current_grade == "D")) && !(wanted_grade == "S" || wanted_grade == current_grade)){
                        cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;
                    }else if (previous_grade == "F" && current_grade == "F" && wanted_grade != "F"){
                        cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;
                    }else if ((current_grade == "A" || current_grade == "B" || current_grade == "C" || current_grade == "D") && !(current_grade == wanted_grade || wanted_grade == "S")) {
                        cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
                    }else if (current_grade == "F" && !(wanted_grade == "U" || current_grade == wanted_grade)){
                        cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
                    }else{
                        cout << name << ", your final grade for " << course << " is " << wanted_grade << ". Goodbye..." << endl;
                    }
                }else{
                    cout << "Invalid grade selection. Goodbye..." << endl;
                }
            }else{
                cout << "Invalid grade selection. Goodbye..." << endl;
            }
        }else{
            cout << "Invalid grade selection. Goodbye..." << endl;
        }
    }
    return 0;
}
//HAMİT KARTAL 28404
