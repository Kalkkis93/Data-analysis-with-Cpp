# ifndef DATA_ANALYSIS_H
# define DATA_ANALYSIS_H

# include <iostream>
# include <fstream>
# include <vector>
# include <string>

using namespace std;

namespace data_analysis {
	typedef struct Data_structure {
		string name;
		vector<double> values;
		vector<int> classes;
		int number_of_classes;
	} Data_structure;

	vector< vector<double> > readAndCleanFile(istream &input);

	Data_structure kmeans(string name, vector<double> x, int k, int n_max);

	Data_structure knn(string name, Data_structure x, vector<double> y);

	void printData(Data_structure d);

	vector<double> sort(vector<double> v);
}

# endif
