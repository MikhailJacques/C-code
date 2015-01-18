
#include "writer.h"
#include "headers.h"

void * Writer(void * arg)
{	
	int writer_id = (int) arg;
	srand((unsigned int) time(NULL) * writer_id);

	for (int i = 0; i < 20; ++i)
	{
		if (DEBUG)
			printf("Writer %d is trying to gain access to the gauge for modifying its data.\n", writer_id);

		// Generate random number of bytes in an imaginary packet in the range [16, 64]
		unsigned int num_bytes = 16 + rand() % 49;

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

	return NULL;
}