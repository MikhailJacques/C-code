
/* Designed and written by Mikhail Jacques
Email: jacques.mikhail@gmail.com
GitHub: https://github.com/MikhailJacques
LinkedIn: https://www.linkedin.com/in/mikhailjacques
*/

#include "reader.h"
#include "headers.h"

void * Reader(void * arg)
{
	int reader_id = (int) arg;
	
	for (int i = 0; i < NUM_ITERATIONS; ++i)
	{
		if (DEBUG)
			printf("Reader %d is trying to access the gauge for reading its data.\n", reader_id);
		
		printf("\tAverage rate (bytes per second): %d\n", g->gauge_rate(g));
		printf("\tTotal number of bytes accumulated thus far: %d\n", g->get_total_bytes(g));

		// Pause this thread for 1 second
		#ifdef _WIN32
			Sleep(1000);
		#else
			sleep(1);
		#endif
	}

	pthread_exit(NULL);
	
	// A really unnecessary statement the only purpose of which is to eliminate MS VS 2013 compiler warnings
	return NULL;	
}