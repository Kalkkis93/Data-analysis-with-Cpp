# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "data_analysis.h"

using namespace std;
using data_analysis::Data_structure;
using data_analysis::readAndCleanFile;
using data_analysis::kmeans;
using data_analysis::knn;
using data_analysis::printData;

int main(int argc, char const *argv[]) {
	int i, j;

	// Read the file and clean the data.
	ifstream input("input.txt");
	vector< vector<double> > data = readAndCleanFile(input);

	// Initialize vector x.
	vector<double> x;
	for (i = 0; i < data[0].size(); i++)
		x.push_back(data[0][i]);

	// Use the k-means algorithm to classify the vector x and print it.
	Data_structure d = kmeans("x", x, 3, 10);
	printData(d);

	// Initialize vector y.
	vector<double> y;
	for (i = 0; i < data[1].size(); i++)
		y.push_back(data[1][i]);

	// Use the knn algorithm to classify the vector y and print it.
	Data_structure d2 = knn("y", d, y);
	printData(d2);
	return 0;
}
