
#include "gauge.h"

// This function is included ONLY for testing purposes
// It is not part of the gauge object
long getThreadId(void)
{
	long thread_id = 0;
	pthread_t ptid = pthread_self();
	memcpy(&thread_id, &ptid, min(sizeof(thread_id), sizeof(ptid)));
	return thread_id;
}

// This function is included for cross-platform development
// It is not part of the gauge object
time_t getCurrentTime(void)
{
	time_t time_val;

	#ifdef _WIN32
		time_val = time(0);	// in seconds
	#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_val = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) / ONE_THOUSAND_MILLISECONDS; // in seconds
	#endif

	return time_val;
}

// This function is included for constructing a gauge object
// It is not part of the gauge object, however, it could have been if my gauge was not designed as a typedef
gauge * constructGauge(unsigned int time_period, unsigned int precision)
{
	gauge * g = (gauge *) malloc(sizeof(gauge));

	if (g == NULL)
	{
		printf("ERROR: Out of memory\n");
		return NULL;
	}

	// Initialize call back functions and semaphores
	init_call_backs(g);

	init_semaphores(g);

	// Set readers counter to 0
	g->set_read_count(g, 0);

	// Initialize time period (in seconds) for calculating average gauge rate (in bytes per second)
	g->set_time_period(g, time_period);

	// Set precision at which the average rate will be calculated (in milliseconds)
	// Note: Currently the precision is not used
	g->set_precision(g, precision);
	
	// Calculate the size of the "circular" array
	// g->bytes_samples_size = (time_period * ONE_THOUSAND_MILLISECONDS / precision + 1);
	g->bytes_samples_size = (time_period + 1);

	// Create and initialize a "circular" array for keeping track of the running average of accumulated bytes
	g->bytes_samples = (int *) malloc(sizeof(int) * g->bytes_samples_size);

	if (g->bytes_samples == NULL)
	{
		printf("ERROR: Out of memory\n");
		return NULL;
	}

	// Set the total number of accumulated bytes to 0
	// Set the timestamp of the "last" clear operation
	// Reset the "circular" array
	g->clear(g);

	return g;
}

void count_packet(void * g, unsigned int num_bytes)
{
	if (DEBUG)
		printf("Thread %d is trying to gain access to the gauge for modifying its data\n", getThreadId());

	sem_wait(&((gauge *)g)->arrival_order_mutex);	// Remember order of arrival of the request
	sem_wait(&((gauge *)g)->access_mutex);			// Request exclusive access to the shared resource for this writer
	sem_post(&((gauge *)g)->arrival_order_mutex);	// Release order of arrival semaphore as this writer has been served

	// Write to the shared resource at will

	if (DEBUG)
		printf("Thread %d is writing into the gauge\n", getThreadId());

	// Add bytes to the running sum total of all bytes added thus far
	((gauge *)g)->total_num_bytes += num_bytes;

	// Add bytes to the running sum total of bytes for calculating average rate over the period of the past X seconds
	int index = getCurrentTime() % ((gauge *)g)->bytes_samples_size;
	int index_next = (index + 1) % ((gauge *)g)->bytes_samples_size;

	// Add bytes to the running sum total of the bytes arrived over the past X seconds
	((gauge *)g)->bytes_samples[index] += num_bytes;
	((gauge *)g)->bytes_samples[index_next] = 0;		// A little trick ;)

	if (DEBUG)
		printf("Thread %d is leaving the gauge\n", getThreadId());

	sem_post(&((gauge *)g)->access_mutex);			// Release exclusive access to the shared resource for this writer
}

unsigned long get_total_bytes(void * g)
{
	if (DEBUG)
		printf("Thread %d is trying to access the gauge for reading its data\n", getThreadId());

	sem_wait(&((gauge *)g)->arrival_order_mutex);	// Remember order of arrival

	sem_wait(&((gauge *)g)->readers_mutex);			// Gain exclusive access to manipulate the readers' counter

	if (((gauge *)g)->read_count == 0)				// See if it is the first reader
		sem_wait(&((gauge *)g)->access_mutex);		// Request exclusive access to the shared resource for readers

	((gauge *)g)->read_count++;						// There is now one more reader

	sem_post(&((gauge *)g)->arrival_order_mutex);	// Release order of arrival semaphore as this reader has been served

	sem_post(&((gauge *)g)->readers_mutex);			// Done accessing the number of readers for now

	if (DEBUG)
		printf("Thread %d is reading the gauge\n", getThreadId());
	
	// Read the shared resource at will
	unsigned long total_bytes = ((gauge *)g)->total_num_bytes;

	sem_wait(&((gauge *)g)->readers_mutex);			// Gain exclusive access to manipulate the readers' counter

	((gauge *)g)->read_count--;						// There is now one less reader

	if (((gauge *)g)->read_count == 0)				// See if there are still readers currently reading
		sem_post(&((gauge *)g)->access_mutex);		// Release exclusive access to the shared resource for readers

	if (DEBUG)
		printf("Thread %d is leaving the gauge\n", getThreadId());

	sem_post(&((gauge *)g)->readers_mutex);			// Done accessing the number of readers for now

	return total_bytes;
}

// The gauge_rate() function does the following two things:
// First, it checks to see that X number of seconds have passed since the last clear op; otherwise, 
// it returns -1 which indicates that there is still insufficient data for calculating average rate.
// If it were not to test for this condition the result would most likely be erroneous due to insufficient 
// data accumulation at the time of sampling since the last clear operation. 
// Second, it ensures that the average rate is calculated only over the last X seconds and no more.
// To accomplish that, it overwrites old samples of bytes with the new ones, conceptually keeping a sort of 
// moving window of calculated time length over which an average is calculated on demand.
// Note that smarter programs use a more complex Moving/Rolling Average algorithm, which 
// could use both recent and older averages, but give more weight to the recent averages.
int gauge_rate(void * g)
{
	// Check to see that X number of seconds have passed since the last clear operation
	if ((((gauge *)g)->clear_timestamp + ((gauge *)g)->time_period) > getCurrentTime())
		return -1;

	if (DEBUG)
		printf("Thread %d is trying to access the gauge for reading its data\n", getThreadId());

	sem_wait(&((gauge *)g)->arrival_order_mutex);	// Remember order of arrival

	sem_wait(&((gauge *)g)->readers_mutex);			// Gain exclusive access to manipulate the readers' counter

	if (((gauge *)g)->read_count == 0)				// See if it is the first reader
		sem_wait(&((gauge *)g)->access_mutex);		// Request exclusive access to the shared resource for readers

	((gauge *)g)->read_count++;						// There is now one more reader

	sem_post(&((gauge *)g)->arrival_order_mutex);	// Release order of arrival semaphore as this reader has been served

	sem_post(&((gauge *)g)->readers_mutex);			// Done accessing the number of readers for now

	if (DEBUG)
		printf("Thread %d is reading the gauge\n", getThreadId());

	// Read the shared resource at will

	// Sum up all the bytes read over the past X seconds ONLY
	int total = 0;
	for (unsigned int i = 0; i < ((gauge *)g)->bytes_samples_size; ++i)
	{
		total += ((gauge *)g)->bytes_samples[i];
	}

	((gauge *)g)->average_rate = total / ((gauge *)g)->time_period;

	sem_wait(&((gauge *)g)->readers_mutex);			// Gain exclusive access to manipulate the readers' counter

	((gauge *)g)->read_count--;						// There is now one less reader

	if (((gauge *)g)->read_count == 0)				// See if there are still readers currently reading
		sem_post(&((gauge *)g)->access_mutex);		// Release exclusive access to the shared resource for readers

	if (DEBUG)
		printf("Thread %d is leaving the gauge\n", getThreadId());

	sem_post(&((gauge *)g)->readers_mutex);			// Done accessing the number of readers for now

	return ((gauge *)g)->average_rate;
}

unsigned int get_time_period(void * g)
{
	return ((gauge *)g)->time_period;
}

void set_time_period(void * g, unsigned int time_period)
{
	((gauge *)g)->time_period = time_period;
}

void set_precision(void * g, unsigned int precision)
{
	((gauge *)g)->precision = precision;
}

void set_read_count(void * g, unsigned int read_count)
{
	((gauge *)g)->read_count = read_count;
}

void init_call_backs(void * g)
{
	// Initialize callback functions
	((gauge *)g)->count_packet = &count_packet;
	((gauge *)g)->get_total_bytes = &get_total_bytes;
	((gauge *)g)->gauge_rate = &gauge_rate;
	((gauge *)g)->get_time_period = &get_time_period;
	((gauge *)g)->set_time_period = &set_time_period;
	((gauge *)g)->set_precision = &set_precision;
	((gauge *)g)->set_read_count = &set_read_count;
	((gauge *)g)->init_semaphores = &init_semaphores;
	((gauge *)g)->release_semaphores = &release_semaphores;
	((gauge *)g)->clear = &clear;
}

void init_semaphores(void * g)
{
	// Initialize semaphores
	sem_init(&((gauge *)g)->access_mutex, 0, 1);
	sem_init(&((gauge *)g)->readers_mutex, 0, 1);
	sem_init(&((gauge *)g)->arrival_order_mutex, 0, 1);
}

void release_semaphores(void * g)
{
	// Release semaphores
	sem_destroy(&((gauge *)g)->access_mutex);
	sem_destroy(&((gauge *)g)->readers_mutex);
	sem_destroy(&((gauge *)g)->arrival_order_mutex);
}

void clear(void * g)
{
	// Set the total number of accumulated bytes to 0
	((gauge *)g)->total_num_bytes = 0;

	// Set the timestamp of the "last" clear operation	
	((gauge *)g)->clear_timestamp = getCurrentTime();

	// Reset the "circular" array
	for (unsigned int i = 0; i < ((gauge *)g)->bytes_samples_size; ++i)
	{
		((gauge *)g)->bytes_samples[i] = 0;
	}
}