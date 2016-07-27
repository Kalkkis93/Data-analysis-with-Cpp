# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cmath>
# include "data_analysis.h"

using namespace std;

namespace data_analysis {
	vector< vector<double> > readAndCleanFile(istream &input) {
		vector< vector<double> > v;
		string line, term;
		istringstream ss1, ss2;
		double d; char c;

		// Read the lines from the file.
		while (getline(input, line)) {
			ss1.str(line);
			vector<double> w;

			// Read every term in the line.
			while (ss1 >> term) {
				ss2.str(term);
				ss2 >> d;

				// Check if the term is a decimal number.
				if (ss2.fail() == 0) {
					ss2 >> c;

					// If it is, add it into the vector w.
					if (ss2.fail() == 1)
						w.push_back(d);
				}
				ss2.clear();
			}
			// Add the vector w into the 2-dimensional vector v.
			v.push_back(w);
			ss1.clear();
		}
		return v;
	}

	Data_structure kmeans(string name, vector<double> x, int k, int n_max) {
		int i, j;
		int n = 0;
		Data_structure d;
		vector<double> means;
		vector<int> classes;

		// Sort the vector x.
		x = sort(x);

		// Initialize means and classes.
		for (i = 0; i < x.size(); i++) {
			if (i < k) {
				means.push_back(x[i]);
				classes.push_back(i);
			}
			else
				classes.push_back(0);
		}

		// Repeat the algorithm n_max times.
		while (n < n_max) {

			// Operate every value in the vector x.
			for (i = 0; i < x.size(); i++) {

				// Put the value in the first class.
				int c = 0;
				double diff1 = abs(x[i] - means[0]);
				double diff2 = 0;
				double m = (means[0] + x[i]) / 3;
				classes[i] = 0;

				// Find the nearest class for x[i].
				for (j = 0; j < k; j++) {

					// Compute the Euclidean distance from the jth class.
					diff2 = sqrt((x[i] - means[j]) * (x[i] - means[j]));

					// Check if this is the nearest class.
					if (diff2 < diff1) {
						diff1 = diff2;
						m = (means[j] + x[i]) / 2;
						classes[i] = j;
						c = j;
					}
				}

				// Update means.
				means[c] = m;
			}

			// Grow n.
			n++;
		}

		// Fill the data structure and return it.
		d.name = name;
		d.values = x;
		d.classes = classes;
		d.number_of_classes = k;
		return d;
	}

	Data_structure knn(string name, Data_structure d, vector<double> x) {
		int i, j;
		vector<int> classes;

		// Sort the vector x.
		x = sort(x);

		// Classify the vector x.
		for (i = 0; i < x.size(); i++) {
			int diff = abs(x[i] - d.values[0]);
			int c = d.classes[0];
			for (j = 0; j < d.values.size(); j++) {
				int diff2 = abs(x[i] - d.values[j]);
				if (diff2 < diff) {
					diff = diff2;
					c = d.classes[j];
				}
			}
			classes.push_back(c);
		}

		// Fill the data structure and return it.
		d.name = name;
		d.values = x;
		d.classes = classes;
		return d;
	}

	/*
	 * Print the data structure d.
	 *
	 */
	void printData(Data_structure d) {
		int i, j;

		// Print the name of d.
		cout << "Data " << d.name << ":\n";

		// Print number of the values.
		cout << "- Number of values: " << d.values.size() << "\n";

		// Print all the classes.
		for (i = 0; i < d.number_of_classes; i++) {
			int n = 0;
			cout << "- Class " << i << ": [";
			for (j = 0; j < d.classes.size(); j++) {
				if (d.classes[j] == i) {
					cout << " " << d.values[j];
					n++;
				}
			}
			// Print the size of the class i.
			cout << " ] (Size: " << n << ")\n";
		}
		cout << "\n";
	}

	/*
	 * Sort the values in vector v.
	 *
	 */
	vector<double> sort(vector<double> v) {
		int i, j, k;

		// Set k = 0.
		k = 0;

		// Sort the vector.
		while (k == 0) {

			// Set k = 1.
			k = 1;

			// Check all the values in vector v.
			for (i = 0; i < v.size() - 1; i++) {
				for (j = i; j < v.size(); j++) {

					// Compare values v[j] and v[i].
					if (v[j] < v[i]) {
						double x = v[i];
						v[i] = v[j];
						v[j] = x;
						k = 0; // Set k = 0.
					}
				}
			}
		}
		// Return sorted v.
		return v;
	}
}
