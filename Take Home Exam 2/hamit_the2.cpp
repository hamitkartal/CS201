#include <iostream>
#include <string>
#include <iomanip>
#include "strutils.h"
using namespace std;

bool check_input (const string & cuboid, const double & a, const double & b, const double & c){
  if (a <= 0 || b <= 0 || c <= 0){
      cout << "Invalid entry for " << cuboid << " cuboid. Dimensions should be positive real numbers!" << endl;
      return false;
    }
  return true;
}

void checkCubeAndDisplay (const string & cuboid, const double & a, const double & b, const double & c){
  if (a == b && a == c){
      cout << cuboid << " cuboid is a cube." << endl << endl;
    }
  else{
      cout << cuboid << " cuboid is not a cube." << endl << endl;
    }
}

void display (const string & cuboid, const double & area, const double & volume){
  cout << "Results for the " << cuboid << " cuboid:" << endl << "Area: " << area << endl << "Volume: " << volume << endl;
}

void calculate (const string & cuboid, const double & a, const double & b, const double & c, double & area, double & volume){
  area = 2 * (a * b + a * c + b * c);
  volume = a * b * c;
  display (cuboid, area, volume);
  checkCubeAndDisplay (cuboid, a, b, c);
}

string compare (const string & cuboid1, const string & cuboid2, string desired_metric, const double & metric1, const double & metric2){
  string result = "";
  if (metric1 < metric2){
      result += cuboid2 + " has the largest " + desired_metric + ".\n";
    }
  else if (metric1 > metric2){
      result += cuboid1 + " has the largest " + desired_metric + ".\n";
    }
  else{
      result += "Two cuboids have the same " + desired_metric + ".\n";
    }
  return result;
}

int main (){
    cout.setf(ios::fixed);
    cout.precision(2);
    
    string cuboid1, cuboid2;
    double a1, b1, c1, a2, b2, c2, area1, volume1, area2, volume2;
    
    cout << "Hello! This program compares two cuboids..." << endl;
    cout << "Please enter colors for the two cuboids: ";
    cin >> cuboid1 >> cuboid2;
    string copy1 = cuboid1, copy2 = cuboid2;
	ToLower(copy1);
	ToLower(copy2);
    
    if (copy1 == copy2){
        cout << "Color names cannot be the same, good bye..." << endl;
    }
    else{
        cout << "Please enter length, width and height of the " << cuboid1 << " cuboid: ";
        cin >> a1 >> b1 >> c1;
        if (check_input(cuboid1, a1, b1, c1)){
    	    cout << "Please enter length, width and height of the " << cuboid2 << " cuboid: ";
	        cin >> a2 >> b2 >> c2;
	        if (check_input(cuboid2, a2, b2, c2)){
    	        calculate(cuboid1, a1, b1, c1, area1, volume1);
		        calculate(cuboid2, a2, b2, c2, area2, volume2);
				cout << "Comparison of the two cuboids:\n";
		        cout << compare(cuboid1, cuboid2, "volume", volume1, volume2);
				cout << compare(cuboid1, cuboid2, "area", area1, area2);
	        }
        }
    }
    return 0;
}