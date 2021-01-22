#include "Operation.h"

int Operation::find_loop_line(string loop_name) { //this function returns the searched loop line in the code.txt file
	ifstream fileInput;
	string line;
	string search = loop_name;
	fileInput.open("code.txt");
	if (loop_name == "for" || loop_name == "while") {
		unsigned int curLine = 0;
		while (getline(fileInput, line)) {
			curLine++;
			if (line.find(search, 0) != string::npos) {
				fileInput.close();
				return curLine;
			}
		}
	}
	return 0;

}
string Operation::get_loop_string(int loop_line) { //this function returns loop string, sample: for(int i=0;i<5;i++) 
	ifstream fileInput;
	string line;
	fileInput.open("code.txt");

	unsigned int curLine = 0;
	while (getline(fileInput, line)) {
		loop_line--;
		if (loop_line == 0) {
			fileInput.close();
			return line;
		}
	}
}
string Operation::get_loop_initialization_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function returns the 'int i=0' part
	unsigned first = loop_string.find("(");
	unsigned last = loop_string.find(";");
	first++;
	return loop_string.substr(first, last - first);

}
string Operation::get_loop_condition_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function returns the 'i<5' part
	unsigned first = loop_string.find(";");
	unsigned last = loop_string.find_last_of(";");
	first++;
	return loop_string.substr(first, last - first);

}
string Operation::get_loop_increment_decrement_string(string loop_string) { //for example for(int i=0;i<5;i++) loop this function returns the 'i++' part
	unsigned first = loop_string.find_last_of(";");
	unsigned last = loop_string.find_last_of(")");
	first++;
	return loop_string.substr(first, last - first);
}
/*
* std::ifstream infile("thefile.txt");
int a, b;
while (infile >> a >> b)
{
	// process pair (a,b)
}
*/
int Operation::find_loop_body_length(int curly_brace_count_in_loop_string) {
	ifstream file("code.txt");
	int allowed = curly_brace_count_in_loop_string;
	int length = 0;
	int curLine = 0;
	string line;
	while (getline(file, line)) {
		curLine++;
		if (curLine > loop_line) {
			length++;
			cout << line << endl;
			if (line.find("{") != std::string::npos) {
				allowed++;
			}
			if (line.find("}") != std::string::npos) {

				allowed--;
				if (allowed == 0) {
					file.close();
					return length;
				}
			}
		}
	}
}
void Operation::change_loop(int line_number) { //change the loop 
	loop_line = line_number;
	loop_string = get_loop_string(loop_line);
	if (loop_string.find("{") != std::string::npos) {
		loop_length = find_loop_body_length(1);

	}
	else {
		loop_length = find_loop_body_length(0);

	}
	string delimiter = " ";
	string initialization_string = get_loop_initialization_string(loop_string);
	ifstream file("code.txt");
	ofstream myfile("temp.txt");
	int tab_space_count = 8;
	char space = loop_string[0];

	if (loop_string.find("{") != std::string::npos) {
		int curLine = 0;
		string line;

		while (getline(file, line)) {
			curLine++;
			if (curLine > loop_line - 1 && curLine < loop_line + loop_length) {
				if (is_variable_exists(loop_string,loop_line-1)) {
					size_t pos = 0;
					std::string token;
					while ((pos = initialization_string.find(delimiter)) != std::string::npos) {
						token = initialization_string.substr(0, pos);
						std::cout << token << std::endl;
						initialization_string.erase(0, pos + delimiter.length());
					}
					myfile << space << initialization_string << ";" << "\n";

				}
				else {
					myfile << space << get_loop_initialization_string(loop_string) << ";" << "\n";
				}
				myfile << space << "while(" << get_loop_condition_string(loop_string) << "){" << "\n";
				while (getline(file, line)) {
					curLine++;
					if (curLine > loop_line + loop_length - 1) break;
					myfile << line << "\n";
				}
				for (int i = 0; i < tab_space_count; i++)
				{
					myfile << " ";
				}
				myfile << space << get_loop_increment_decrement_string(loop_string) << ";" << "\n" << space << "}" << "\n";

			}
			else {
				myfile << line << "\n";

			}
		}

	}
	else {
		int curLine = 0;
		string line;

		while (getline(file, line)) {
			curLine++;
			if (curLine > loop_line - 1 && curLine < loop_line + loop_length) {
				if (is_variable_exists(loop_string,loop_line-1)) {
					size_t pos = 0;
					std::string token;
					while ((pos = initialization_string.find(delimiter)) != std::string::npos) {
						token = initialization_string.substr(0, pos);
						std::cout << token << std::endl;
						initialization_string.erase(0, pos + delimiter.length());
					}
					myfile << space << initialization_string << ";" << "\n";

				}
				else {
					myfile << space << get_loop_initialization_string(loop_string) << ";" << "\n";
				}
				myfile << space << "while(" << get_loop_condition_string(loop_string) << ")" << "\n";
				while (getline(file, line)) {
					curLine++;
					if (curLine > loop_line + loop_length - 1) break;
					myfile << line << "\n";
				}
				for (int i = 0; i < tab_space_count; i++)
				{
					myfile << " ";
				}
				myfile << space << get_loop_increment_decrement_string(loop_string) << ";" << "\n" << space << "}" << "\n";

			}
			else {
				myfile << line << "\n";

			}
		}
	}
	myfile.close();
	file.close();
	remove("code.txt");
	rename("temp.txt", "code.txt");

}
int Operation::get_line_count_in_file() {
	ifstream file("code.txt");
	int counter = 0;
	string line;
	while (getline(file, line)) {
		counter++;
	}
	return counter;
}
bool Operation::is_variable_exists(string loop_string,int line_restriction) {
	string current_variable =get_loop_initialization_string(loop_string);
	ifstream file("code.txt");
	string line;
	while (getline(file, line)) {
		line_restriction--;
		if (line.find(current_variable) != string::npos) {
			file.close();
			return true;
		}
		if (line_restriction == 0)break;
	}
	file.close();
	return false;

}
void Operation::begin() {
	int curLine = 0;
	int line_count_in_file = get_line_count_in_file();
	int old_loop_line = 0;
	string line;
	while (curLine < line_count_in_file) {
		ifstream file("code.txt");
		cout << curLine << endl;
		curLine = 0;
		while (getline(file, line)) {
			curLine++;
			if (line.find("for") != std::string::npos&&curLine>old_loop_line) {
				file.close();
				old_loop_line = curLine;
				change_loop(curLine);
				cout << curLine << "***" << endl;
				break;
			}
		}
	}
	
	if (loop_line == 0) return;

}
