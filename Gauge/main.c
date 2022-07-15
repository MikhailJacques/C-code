
/* Designed and written by Mikhail Jacques
Email: jacques.mikhail@gmail.com
GitHub: https://github.com/MikhailJacques
LinkedIn: https://www.linkedin.com/in/mikhailjacques
*/

#include "gauge.h"
#include "reader.h"
#include "writer.h"
#include "headers.h"

// Declare global gauge variable that will be share among by the threads
gauge * g;

int main()
{
	unsigned int time_period, precision;

	printf("The following two values are necessary for calculating average gauge rate.\n");

	do
	{
		printf("Enter an integer value representing a time period (measured in seconds)\nin the range [0-%d]: ", 
			MAX_TIME_PERIOD);
		#ifdef _WIN32
		scanf_s("%d", &time_period);
		#else
		scanf("%d", &time_period);
		#endif
		
		if (time_period < 1 || time_period > MAX_TIME_PERIOD)
			printf("Invalid entry.Please try again ...\n");

	} while ((time_period < 1 || time_period > MAX_TIME_PERIOD));

	// Note: Currently the value of the precision is not used
	do
	{
		printf("Enter an integer value representing precision (measured in milliseconds)\n");
		printf("for calculating average gauge rate in the range [0-%d]: ", MIN_PRECISION);
		#ifdef _WIN32
		scanf_s("%d", &precision);
		#else
		scanf("%d", &precision);
		#endif

		if (precision < 1 || precision > MIN_PRECISION)
			printf("Invalid entry.Please try again ...\n");

	} while ((precision < 1 || precision > MIN_PRECISION));

	// Initialize local variables
	int i = 0, num_readers = 0, num_writers = 0;

	pthread_t readers[MAX_NUM_READERS], writers[MAX_NUM_WRITERS];

	do
	{
		printf("Enter number of Readers in the range [0-%d]: ", MAX_NUM_READERS);
		#ifdef _WIN32
		scanf_s("%d", &num_readers);
		#else
		scanf("%d", &num_readers);
		#endif

		if (num_readers < 1 || num_readers > MAX_NUM_READERS)
			printf("Invalid entry.Please try again ...\n");

	} while ((num_readers < 1 || num_readers > MAX_NUM_READERS));

	do
	{
		printf("Enter number of Writers in the range [0-%d]: ", MAX_NUM_WRITERS);
		#ifdef _WIN32
		scanf_s("%d", &num_writers);
		#else
		scanf("%d", &num_writers);
		#endif

		if (num_writers < 1 || num_writers > MAX_NUM_WRITERS)
			printf("Invalid entry.Please try again ...\n");

	} while ((num_writers < 1 || num_writers > MAX_NUM_WRITERS));


	// Construct the gauge
	g = constructGauge(time_period, precision);

	if (g == NULL)
	{
		printf("ERROR: Construction of gauge object failed\n");
		return 0;
	}

	for (i = 1; i <= num_readers; i++)
	{
		pthread_create(&readers[i], NULL, Reader, (void *)i);
	}

	for (i = 1; i <= num_writers; i++)
	{
		pthread_create(&writers[i], NULL, Writer, (void *)i);
	}

	for (i = 1; i <= num_writers; i++)
	{
		pthread_join(writers[i], NULL);
	}

	for (i = 1; i <= num_readers; i++)
	{
		pthread_join(readers[i], NULL);
	}

	system("pause");

	// CLEAR
	g->clear(g);
	printf("Total number of bytes (after clear): %d\n", get_total_bytes(g));
	printf("Average byte rate (after clear): %f\n", gauge_rate(g));

	system("pause");

	// Destruct the gauge
	g->release_semaphores(g);

	free(g);

	return 0;
}