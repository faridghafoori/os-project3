#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define INPUT_FILE "inputs.txt"
#define WEIGHT_FILE "weights.txt"

using namespace std;

vector<string> split_string(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

int string_to_int(string str) {
  int result;
  stringstream ss(str);
  ss >> result;
  return result;
}

vector<vector<int> > input_parser(vector<string> store_input) {
	vector<vector<int> > int_inputs_table;
	vector<int> row;
	vector<vector<string> > inputs_table;
	vector<string> temp;

	for(int i = 2; i < store_input.size(); i++) {
		string a = store_input[i].substr(1, store_input[i].size()-3);
		temp = split_string(a, ',');
		inputs_table.push_back(temp);
		temp.clear();
	}

	for(int i = 0; i < inputs_table.size(); i++) {
		row.clear();
		for(int j = 0; j < inputs_table[i].size(); j++) {
			row.push_back(string_to_int(inputs_table[i][j]));
		}
		int_inputs_table.push_back(row);
	}


	// INPUT CHECK 
	// for(int i = 0; i < int_inputs_table.size(); i++) {
	// 	for(int j = 0; j < int_inputs_table[i].size(); j++) {
	// 		cout << int_inputs_table[i][j] << " | ";
	// 	}
	// 	cout << "\n\n";
	// }

	return int_inputs_table;
}

void *read_inputs(void *arg) {
	ifstream input_file;
	string line;
	vector<string> store_input;
	vector<vector<int> > number_inputs;

	input_file.open(INPUT_FILE);
	if (!input_file) {
    cerr << "Unable to open file " << INPUT_FILE << endl;
    exit(1);
	}
	while(getline(input_file, line)) {
		store_input.push_back(line);
	}

	number_inputs = input_parser(store_input);

	input_file.close();
	 
  pthread_exit(NULL);
}

vector<int> weight_parser(vector<string> store_weight) {
	vector<int> temp;
	cout << store_weight[1] <<endl;
	string a = store_weight[2].substr(1, store_weight[2].size()-2);
	cout << a << endl;
	return temp;
}

void *read_weights(void *arg) {
	ifstream weight_file;
	string line;
	vector<string> store_weight;
	int BIAS = 0;
	vector<int> weights;

	weight_file.open(WEIGHT_FILE);
	if (!weight_file) {
    cerr << "Unable to open file " << WEIGHT_FILE << endl;
    exit(1);
	}

	while(getline(weight_file, line)) {
		store_weight.push_back(line);
	}

	weights = weight_parser(store_weight);


	for(int i = 0; i < store_weight.size(); i++) {
		cout << store_weight[i] << endl;
	}

	weight_file.close();

  pthread_exit(NULL);	
}

int main()
{
  pthread_t inputs_thread, weights_thread;
  int inputs_thread_err, weights_thread_err;

  inputs_thread_err = pthread_create(&inputs_thread, NULL, read_inputs, NULL);
  weights_thread_err = pthread_create(&weights_thread, NULL, read_weights, NULL);

  if(inputs_thread_err != 0 || weights_thread_err != 0) {
	  cout << "Error: inputs_thread() or weights_thread() failed\n";
	  exit(EXIT_FAILURE);
	}

  pthread_exit(NULL);
}