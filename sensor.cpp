#include "papi.h"
#include <ctime>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace std;

#define N 4500
#define NUM_EVENT 7
#define THRESHOLD 100000
#define ERROR_RETURN(retval) { fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }

int main(int argc, char **argv) {
	int retval;
    int EventSet = PAPI_NULL;
    int event_codes[NUM_EVENT] = {PAPI_TOT_INS, PAPI_TOT_CYC, PAPI_REF_CYC,
                                  PAPI_L1_DCM, PAPI_L3_TCM, PAPI_LD_INS,
                                  PAPI_SR_INS};
    char errstring[PAPI_MAX_STR_LEN];
    long long values[NUM_EVENT];
	if ((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT) {
		fprintf(stderr, "Error: %s\n", errstring);
		exit(1);
	}


	if ((retval = PAPI_create_eventset(&EventSet)) != PAPI_OK) {
		ERROR_RETURN(retval);
	}


	if ((retval = PAPI_add_events(EventSet, event_codes, NUM_EVENT)) != PAPI_OK) {
		ERROR_RETURN(retval);
	}


	if ((retval = PAPI_start(EventSet)) != PAPI_OK) {
		ERROR_RETURN(retval);
	}

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
			a[i][j] = ((double) rand() / (RAND_MAX));
			b[i][j] = ((double) rand() / (RAND_MAX));
			c[i][j] = 0;
		}
	}

	for (int i = 0; i < 2200; i++) {
		//d[i] = new double[2200];
		for (int j = 0; j < 2200; j++) {
			d[i][j] = ((double) rand() / (RAND_MAX));
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

    if ((retval = PAPI_stop(EventSet, values)) != PAPI_OK) {
		ERROR_RETURN(retval);
	}

    cout << values[0] << '\n'
         << values[1] << '\n'
         << values[2] << '\n'
         << values[3] << '\n'
         << values[4] << '\n'
         << values[5] << '\n'
         << values[6] << '\n';

	if ((retval = PAPI_remove_events(EventSet,event_codes, NUM_EVENT)) != PAPI_OK)
		ERROR_RETURN(retval);

    if ((retval = PAPI_destroy_eventset(&EventSet)) != PAPI_OK)
		ERROR_RETURN(retval);

    PAPI_shutdown();

    exit(0);
}
