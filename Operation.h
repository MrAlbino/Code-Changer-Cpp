#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Operation
{
	private:
		int loop_line;
		string loop_string;
	public:
		int find_loop_line(string);
		string get_loop_string(int);
		string get_loop_initialization_string(string);
		string get_loop_condition_string(string);
		string get_loop_increment_decrement_string(string);
		void change_loop();
		void begin();
};

