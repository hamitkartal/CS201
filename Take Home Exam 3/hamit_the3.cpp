#include <iostream>
#include <string>
using namespace std;

bool sourceCheck(const string & source){
    for(int i = 0; i < source.length(); i += 1){
        int ascii_no = char(source.at(i));
        if (!((ascii_no >= 97 && ascii_no <= 122) || (ascii_no <= 90 && ascii_no >= 65) || (ascii_no >= 48 && ascii_no <= 57) || (ascii_no == 32))){
            return false;
        }
    }
	return true;
}

bool searchCheck(const string & search){
	char last = search.at(search.length()-1);
	if (search.at(0) != last){
		if (last == '+' || last == '.' || last == '*' || search.substr(search.length()-2, 2) == "**"){
		return true;
		}
	}
	return false;
}

void plusSign(const string & search, const string & source){
	int position = 0, index = 0;
	while (index != -1){
		index = source.find(search, position);
		if (index != -1){
			if (source.at(index-1) == ' '){
				int next_space = source.find(" ", index);
				int word_length = next_space - index; 
				cout << "index: " << index-1 << " word: " << source.substr(index, word_length) << endl;
				position = next_space + 1;
			}
			else{
				int next_space = source.find(" ", index);
			    position = next_space + 1;
			}
		}
	}
}

void dot(const string & search, const string source){
	int position = 0, index = 0;
	while (index != -1){
		index = source.find(search, position);
		if (index != -1){
			if (source.at(index + search.length()) == ' '){
				int next_space = index + search.length();
				int last_space = source.rfind(" ", next_space - 1);
				cout << "index: " << index-1 << " word: " << source.substr(last_space + 1, next_space - last_space - 1) << endl;
				position = next_space + 1;
			}
			else{
				position = index + search.length();
			}
		}
	}
}

void star(const string & search, const string & source){
    int position = 0, index = 0;
	while (index != -1){
		index = source.find(search, position);
		if (index != -1){
			if (source.at(index-1) != ' ' && source.at(index + search.length()) != ' '){
				int next_space = source.find(" ", index);
				int last_space = source.rfind(" ", next_space - 1);
				string word = source.substr(last_space +1, next_space - last_space -1);
				if (word.substr(0, search.length()) != search && word.substr(word.length() - search.length(), search.length()) != search){
					cout << "index: " << index-1 << " word: " << source.substr(last_space + 1, next_space - last_space - 1) << endl;
					position = index + search.length();
				}
				else{
					position = next_space + 1;
				}
			}
			else{
				position = index + search.length();
			}
		}
	}
}

void doubleStar(const string & search, const string & source){
    int position = 0, index = 0;
	while (index != -1){
        index = source.find(search, position);
        if (index != -1){
            int next_space = source.find(" ", index);
            int last_space = source.rfind(" ", index-1);
            cout << "index: " << index-1 << " word: " << source.substr(last_space + 1, next_space - last_space - 1) << endl;
			position = index + search.length();
		}
	}
}

void executioner(const string & search, const string & source){
	if(search.at(search.length()-1) == '+'){
		string sub = search.substr(0, search.length()-1);
		plusSign(sub, source);
	}
	else if(search.at(search.length()-1) == '.'){
		string sub = search.substr(0, search.length()-1);
		dot(sub, source);
	}
	else if(search.substr(search.length()-2, 2) == "**"){
		string sub = search.substr(0, search.length()-2);
		doubleStar(sub, source);
	}
	else{
		string sub = search.substr(0, search.length()-1);
        star(sub, source);
	}
}

int main(){
	bool flag = true;
	string source;
	while (flag){
		cout << "Enter source string: ";
		string sourceWord;
		source = " ";
		bool flag2 = true;
		while(flag2 && cin >> sourceWord){
			if (sourceWord == "END" || sourceWord == "end"){
				flag2 = false;
			}
			else{
				source += sourceWord + " ";
			}
		}
		if (sourceCheck(source)){
			flag = false;
		}	
	}
	string search;
	cout << "Enter search string: ";
	cin >> search;
	while (search != "QUIT" && search != "quit"){
		if (searchCheck(search)){
			executioner(search, source);
		}
		cin.clear();
		cout << "Enter search string: ";
		cin >> search;
	}
    return 0;
}
