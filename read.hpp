#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
 *	Class that reads from csv
*/

class read{
private:
    string fname = "student.csv";
    vector<vector<string>> content;
	vector<string> row;
	string line, word;
 
public:
    vector<vector<string>> readCsv();
	
};