
/* Designed and written by Mikhail Jacques
Email: jacques.mikhail@gmail.com
GitHub: https://github.com/MikhailJacques
LinkedIn: https://www.linkedin.com/in/mikhailjacques
*/

#include "writer.h"
#include "headers.h"

void * Writer(void * arg)
{	
	int writer_id = (int) arg;
	srand((unsigned int) time(NULL) * writer_id);

	for (int i = 0; i < NUM_ITERATIONS; ++i)
	{
		if (DEBUG)
			printf("Writer %d is trying to gain access to the gauge for modifying its data.\n", writer_id);

		// Generate random number of bytes in an imaginary packet in the range [16, 64]
		unsigned int num_bytes = 16 + rand() % 49;

		// num_bytes = 10; // for testing

		if (DEBUG)
			printf("Writer %d has a new packet to add with %d bytes in it.\n", writer_id, num_bytes);

		g->count_packet(g, num_bytes);

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