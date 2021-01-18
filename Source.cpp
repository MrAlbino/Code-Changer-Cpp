#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int find_loop_line(string loop_name) { //this function returns the line of searched loop line in the code.txt file
    ifstream fileInput;
    string line;
    string search = loop_name;
    fileInput.open("code.txt");

    unsigned int curLine = 0;
    while (getline(fileInput, line)) {
        curLine++;
        if (line.find(search, 0) != string::npos) {
            return curLine;
        }
    }
}
string get_loop_string(int loop_line) { //this function returns loop string, sample: for(int i=0;i<5;i++) 
    ifstream fileInput;
    string line;
    fileInput.open("code.txt");

    unsigned int curLine = 0;
    while (getline(fileInput, line)) {
        loop_line--;
        if (loop_line == 0) {
            return line;
        }
    }
}
string get_loop_initialization_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function gets the 'int i=0' part
    unsigned first = loop_string.find("(");
    unsigned last = loop_string.find(";");
    first++;
    return loop_string.substr(first, last - first);

}
string get_loop_condition_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function gets the 'i<5' part
    unsigned first = loop_string.find(";");
    unsigned last = loop_string.find_last_of(";");
    first++;
    return loop_string.substr(first, last - first);

}
string get_loop_increment_decrement_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function gets the 'i++' part
    unsigned first = loop_string.find_last_of(";");
    unsigned last = loop_string.find_last_of(")");
    first++;
    return loop_string.substr(first, last - first);
}

int main() {
    
    cout << get_loop_increment_decrement_string(get_loop_string(find_loop_line("for"))) << endl;

	return 0;
}