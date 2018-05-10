#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

#define INPUT_FILE "inputs.txt"
#define WEIGHT_FILE "weights.txt"
#define DEVIDE_NUMBER 32768
#define PI 3.14
#define OUTPUT_FILE "output_test.txt"

// GLOBAL VALUES
double BIAS;
vector<double> WEIGHTS;
vector<vector<double> > INPUTS;

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

vector<vector<double> > input_parser(vector<string> store_input) {
	vector<vector<double> > int_inputs_table;
	vector<double> row;
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

	for(int i = 0; i < int_inputs_table.size(); i++) {
		for(int j = 0; j < int_inputs_table[i].size(); j++) {
			int_inputs_table[i][j] /= DEVIDE_NUMBER;
		}
	}
	return int_inputs_table;
}

vector<double> weight_parser(vector<string> store_weight) {
	vector<double> int_weight_values;
	vector<string> weights;
	string a = store_weight[1].substr(1, store_weight[1].size()-2);
	weights = split_string(a, ',');
	for(int i = 0; i < weights.size(); i++) {
		int_weight_values.push_back(string_to_int(weights[i]));
	}

	for(int i = 0; i < int_weight_values.size(); i++) {
		int_weight_values[i] /= DEVIDE_NUMBER;
	}
	return int_weight_values;
}

double bias_parser(string bias_value) {
	double bias;
	string a = bias_value.substr(6, bias_value.size());
	return bias = string_to_int(a);
}

void read_inputs() {
	ifstream input_file;
	string line;
	vector<string> store_input;
	vector<vector<double> > number_inputs;

	input_file.open(INPUT_FILE);
	if (!input_file) {
    cerr << "Unable to open file " << INPUT_FILE << endl;
    exit(1);
	}
	while(getline(input_file, line)) {
		store_input.push_back(line);
	}

	number_inputs = input_parser(store_input);

	INPUTS = number_inputs;

	input_file.close();
}

void read_weights() {
	ifstream weight_file;
	string line;
	vector<string> store_weight;
	double bias;
	vector<double> weights;

	weight_file.open(WEIGHT_FILE);
	
	if (!weight_file) {
    cerr << "Unable to open file " << WEIGHT_FILE << endl;
    exit(1);
	}

	while(getline(weight_file, line)) {
		store_weight.push_back(line);
	}

	weights = weight_parser(store_weight);
	bias = bias_parser(store_weight[2]) / DEVIDE_NUMBER;

	WEIGHTS = weights;
	BIAS = bias;

	weight_file.close();
}

vector<double> process_answer() {
	vector<double> sum;
	vector<double> result;
  for(int i = 0; i < INPUTS.size(); i++) {
		double a = 0;
  	for(int j = 0; j < INPUTS[i].size(); j++) {
  		a += WEIGHTS[j] * INPUTS[i][j];
  	}
  	sum.push_back(a);
  }

  for(int i = 0; i < sum.size(); i++) {
  	sum[i] += BIAS;
  	result.push_back(atan (sum[i]));
  }
  return result;
}

void generate_output(vector<double> result) {
  ofstream output;
  output.open(OUTPUT_FILE);
  for(int i = 0; i < result.size(); i++) {
  	output << result[i] << endl;
  }
  output.close();
}

int main(int argc, char const *argv[]) {
	vector<double> result;
  read_inputs();
  read_weights();
  result = process_answer();
  generate_output(result);
}