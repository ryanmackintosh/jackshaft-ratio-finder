#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// TODO
// user input ratios and sprocket sizes, ratio upper & lower bounds
// search top half of array only
// option for stock sprockets only
// print to a file that can be imported by excel
// multiple sprocket ranges, including stock sprockets and certain custom sprockets, eg. small stock & custom sprockets (cheaper), stock large sprockets only

int main(int argc, char* argv[]) {

	// epsilon: tolerance for comparing rounded ratios
	double epsilon = 0.000000000001;

	// User input: sorter headshaft ratio
	double sorter_ratio = 12.0 / 36.0;
	//sorter_ratio = 12.0 / 36.0;

	// User input: sorter feeder ratio
	double feeder_ratio = 5.0 / 9.0;

	// User input: ratio lower & upper bounds
	double ratio_lower_bound = 1.4;
	double ratio_upper_bound = 2.4;

	// User input: choose stock sprockets only, or include custom sprockets

	unsigned int smallest_sprocket = 28;
	unsigned int largest_sprocket = 224;
	unsigned int sprocket_count = largest_sprocket - smallest_sprocket;

	// ratio_wrt_sorter is the resulting jackshaft ratio using the given sprockets
	// allocate heap memory because of the array size
	double* ratio_wrt_sorter = malloc(sizeof(double) * (sprocket_count + 1) * (sprocket_count + 1));

	// ratio_wrt_feeder is the resulting jackshaft ratio using the given sprockets
	double* ratio_wrt_feeder = malloc(sizeof(double) * (sprocket_count + 1) * (sprocket_count + 1));

	// sprocket_vector contains the desired range of sprockets
	unsigned int* sprocket_vector = malloc(sizeof(int) * (sprocket_count+1));
	
	// Option 1: fill sprocket_vector with a continuous range of sprocket sizes
	for (unsigned int n = 0; n <= sprocket_count; n++) {
		sprocket_vector[n] = n + smallest_sprocket;
	}

	// Option 2: fill sprocket_vector with stock sprockets
	//unsigned int sprocket_vector[] = { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 43, 44, 45, 48, 50, 52, 53, 56, 60, 63, 64, 67, 68, 71, 72, 75, 80, 90, 112, 140, 144, 168, 180, 192, 200, 216, 224 };
	// need to count sprockets
	//unsigned int sprocket_count = ....for loop


	// Fill ratio_wrt_sorter & ratio_wrt_feeder with calculated ratios
	unsigned int count = 0, array_size = (sprocket_count + 1) * (sprocket_count + 1);
	for (unsigned int x = 0; x <= sprocket_count; x++) {
		for (unsigned int y = 0; y <= sprocket_count; y++) {
			*(ratio_wrt_sorter + count) = sorter_ratio * (double)sprocket_vector[y] / (double)sprocket_vector[x];
			*(ratio_wrt_feeder + count) = feeder_ratio * (double)sprocket_vector[y] / (double)sprocket_vector[x];
			count++;
		}
	}

	// Index through ratio_wrt_sorter looking for a matching value in ratio_wrt_feeder
	for (count = 0; count <= (array_size - 1); count++) {
		for (unsigned int x = 0; x <= (array_size - 1); x++) {
				if (fabs(*(ratio_wrt_sorter + count) - *(ratio_wrt_feeder + x)) < epsilon && *(ratio_wrt_sorter + count) >= ratio_lower_bound && *(ratio_wrt_sorter + count) <= ratio_upper_bound) {
					//printf("comparing ratio %6.4f to ratio %6.4f\n", *(ratio_wrt_sorter + count), *(ratio_wrt_feeder + x));
					double ratio = *(ratio_wrt_sorter + count);
					unsigned int sorter_driveN = sprocket_vector[(count % (sprocket_count +1))];
					unsigned int sorter_driveR = sprocket_vector[(count / (sprocket_count +1))];
					unsigned int feeder_driveN = sprocket_vector[(x % (sprocket_count +1))];
					unsigned int feeder_driveR = sprocket_vector[(x / (sprocket_count + 1))];
					
					printf("%6.4f %3u %3u %3u %3u\n", ratio, sorter_driveN, sorter_driveR, feeder_driveN, feeder_driveR);
				}
		}
	}

	// Release heap meory
	free(ratio_wrt_sorter);
	free(ratio_wrt_feeder);
	free(sprocket_vector);

	return 0;
}