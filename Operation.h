#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Operation
{
private:
	int loop_line = 0;
	int loop_length = 0;
	string loop_string;
public:
	int find_loop_line(string);
	string get_loop_string(int);
	string get_loop_initialization_string(string);
	string get_loop_condition_string(string);
	string get_loop_increment_decrement_string(string);
	int find_loop_body_length(int);
	void change_loop(int);
	int get_line_count_in_file();
	bool is_variable_exists(string, int);
	string extract_variable_name(string);
	string generate_new_variable_name(string,string);
	void begin();
};
