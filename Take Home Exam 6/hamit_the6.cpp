// Hamit Kartal 28404

#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "favoriteseries.h"
#include <sstream>
#include "strutils.h"
#include <fstream>
using namespace std;

void insert(vector<episode>& a, episode newnum){  		// NOT const vector
// pre: a[0] <= … <= a[a.size()-1], a is sorted
// post: newnum inserted into a, a still sorted
    int count = a.size();  // size before insertion
    a.push_back(newnum);   // increase size –newnum is inserted at the
                   	// end but inserted value is not important
    int loc = count;      // start searching insertion loc from end
   
    while ((loc > 0 && a[loc-1].date > newnum.date) || (loc > 0 && a[loc-1].date == newnum.date && a[loc-1].slot > newnum.slot) ||	(loc > 0 && a[loc-1].date == newnum.date && a[loc-1].slot == newnum.slot && a[loc-1].seriesCode > newnum.seriesCode)){    
		a[loc] = a[loc-1]; 
		loc--;        // shift right until the proper insertion cell
    }
    
	a[loc] = newnum;  //actual insertion 
}


void dataSetDisplayer(const vector<episode>& eps, const vector<series>& dataSet){
	cout <<	"CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for (int i=0; i < eps.size(); i++){
		cout << eps[i].seriesCode << ",";
		int j=0;
		for (; j < dataSet.size(); j++){
			if (dataSet[j].seriesCode == eps[i].seriesCode){
				break;
			}
		}
		cout << dataSet[j].seriesName << "," << eps[i].episodeName << "," << eps[i].date.ToString() << "," << eps[i].slot.substr(1) << endl;
	}
}


int main(){
    string File1 = "series.txt", File2 = "episodes.txt";
    ifstream file1, file2;
    file1.open(File1.c_str());
    file2.open(File2.c_str());
    
    
    vector<series> dataSet;
    string line;
    while (getline(file1, line)){
        istringstream file1(line);
        string contemp="", name="", actorname;
        int commaCount=0, code=0;
        series obj;
        for (int i=0; i < line.length(); i++){
            if (line.at(i) == ','){
                commaCount++;
            }
        }
        file1 >> code;
        obj.seriesCode = code;
        while (file1 >> contemp){
            if (contemp.at(contemp.length()-1) != ';'){
                name += contemp + " ";
            }
            else{
                name += contemp.substr(0, contemp.length()-1) + " ";
                break;
            }
        }
        ToUpper(name);
        StripWhite(name);
        obj.seriesName = name;
        for (int i=0; i < commaCount; i++){
            while (file1 >> contemp){
                if (contemp.at(contemp.length()-1) != ','){
                    actorname += contemp + " ";
                }
                else{
                    actorname += contemp.substr(0, contemp.length()-1) + " ";
                    ToUpper(actorname);
                    StripWhite(actorname);
					obj.actorNames.push_back(actorname);
                    actorname = "";
                    break;
                }
            }
        }
        while (file1 >> contemp){
            actorname += contemp + " ";
        }
        ToUpper(actorname);
        StripWhite(actorname);
        obj.actorNames.push_back(actorname);
        dataSet.push_back(obj);
    }
    
    while (getline(file2, line)){
        istringstream file2(line);
        int code=0;
        string date, timeslot, episodename;
        file2 >> code >> date >> timeslot;
        getline(file2, episodename);
        if (timeslot == "morning"){
            timeslot = "a" + timeslot;
        }
        else if (timeslot == "afternoon"){
            timeslot = "b" + timeslot;
        }
        else if (timeslot == "evening"){
            timeslot = "c" + timeslot;
        }
        else{
            timeslot = "d" + timeslot;
        }
        ToUpper(timeslot);
        ToUpper(episodename);
        StripWhite(episodename);
        int first_indx = date.find('/');
        int sec_indx = date.find('/', first_indx + 1);
        int month = atoi(date.substr(0, first_indx));
        int day = atoi(date.substr(first_indx + 1 , sec_indx - first_indx - 1));
        int year = atoi(date.substr(sec_indx + 1));
        Date tarih(month, day, year);
        episode eps;
        eps.episodeName = episodename;
        eps.seriesCode = code;
        eps.date = tarih;
        eps.slot = timeslot;
        int i = 0;
        for (; i < dataSet.size(); i++){
            if (dataSet[i].seriesCode == code){
                break;
            }
        }
        dataSet[i].episodes.push_back(eps);
    }

	vector<episode> dataSet2;
	for (int i=0; i < dataSet.size(); i++){
		for (int x=0; x < dataSet[i].episodes.size(); x++){
			insert(dataSet2, dataSet[i].episodes[x]);
		}
	}

	string name, surname;
	cout << "Welcome to my favorite TV series schedule program!" << endl << "Please, enter your name and surname: ";
	cin >> name >> surname;
	ToUpper(name);
	ToUpper(surname);
	FavoriteSeries obj (name, surname);
	while(true){
		string input;
		cout << "---\nMENU\n1. Print all TV series\n2. Add TV series\n3. Drop TV series\n4. Print your favorite series with schedule\n5. Print all your favorite actors\n6. Exit\n---\nPlease enter your choice: ";
		cin >> input;
		if (input == "1"){
			dataSetDisplayer(dataSet2, dataSet);
		}
		else if (input == "2"){
			int code;
			cout << "Enter code for the TV series you want to add: ";
			cin >> code;
			int i=0;
			bool flag = false;
			for (; i < dataSet.size() && !flag; i++){
				if (dataSet[i].seriesCode == code){
					flag = true;
					break;
				}
			}
			if (flag){
				if ( !obj.ifExists(code)){
					if ( !obj.isConflict(dataSet[i]) ){
						obj.addSeries(dataSet[i]);
						cout << obj.getFullName() << ", " << dataSet[i].seriesName << " added to your schedule." << endl;
					}
					else{
						cout << obj.getFullName() << ", you can't add this TV series because of a date and slot conflict!" << endl;
					}
				}	
				else{
					cout << obj.getFullName() << ", you can't add this TV series because you already added it!" << endl;
				}
			}
			else{
				cout << obj.getFullName() << ", there is no such TV series in the database!" << endl;
			}	
			
		}
		else if (input == "3"){
			if ( obj.isListEmpty() ){
				cout << obj.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else{
				int code;
				cout << "Enter code for the TV series you want to drop: ";
				cin >> code;
				if ( obj.ifExists(code) ){
					obj.dropSeriesSorted(code);
				}
				else{
					cout << obj.getFullName() << ", there is no such TV series in your favorite list!" << endl;
				}
			}
		}
		else if (input == "4"){
			if ( !obj.isListEmpty() ){
				cout << obj.getFullName() << ", here is your favorite TV series:" << endl;
				obj.displayFavoriteList();
			}
			else{
				cout << obj.getFullName() << ", you did not add any TV series yet!" << endl;
			}
		}
		else if (input == "5"){
			if ( !obj.isListEmpty() ){
				obj.displayFavoriteActors();
			}
			else{
				cout << obj.getFullName() << ", you did not add any TV series yet!" << endl;
			}
		}
		else if (input == "6"){
			cout << "Goodbye, " << obj.getFullName() << "!" << endl;
			break;
		}
		else{
			cout << "Invalid option!" << endl;
		}
	}

	return 0;
}