#include "papi.h"
#include <ctime>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace std;

#define N 2500

int main(int argc, char **argv) {

	double sum = 0;
	static double a[N][N], b[N][N], c[N][N], d[2200][2200];
    srand(time(0));

	cout << N << ": \n";

	/*a = new double *[n];
	b = new double *[n];
	c = new double *[n];*/

    for (int i = 0; i < N; i++) {
		/*a[i] = new double[n];
		b[i] = new double[n];
		c[i] = new double[n];*/
		for (int j = 0; j < N; j++) {
			a[i][j] = ((double) rand() / (RAND_MAX + 1));
			b[i][j] = ((double) rand() / (RAND_MAX + 1));
			c[i][j] = 0;
		}
	}

	for (int i = 0; i < 2200; i++) {
		//d[i] = new double[2200];
		for (int j = 0; j < 2200; j++) {
			d[i][j] = ((double) rand() / (RAND_MAX + 1));
		}
	}

    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
			sum += c[i][j];
		}
	}

	if (sum) {
		cout << "Using sum variable" << '\n';
	}

    exit(0);
}
