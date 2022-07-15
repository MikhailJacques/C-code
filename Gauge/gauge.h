
/* Designed and written by Mikhail Jacques
Email: jacques.mikhail@gmail.com
GitHub: https://github.com/MikhailJacques
LinkedIn: https://www.linkedin.com/in/mikhailjacques
*/

/* The readers-writers problem is a classical one in computer science.
Assume we have a shared resource that can be accessed by readers,
which do not modify the resource and writers, which can modify the resource.
When a writer is modifying the resource, no-one else (reader or writer)
can access it at the same time since another writer could corrupt the resource
and another reader could read a partially modified (thus possibly inconsistent) value.

The readers-writers algorithm implemented in this gauge favors neither readers nor writers.
All readers and writers are granted access to the resource in their order of arrival.
If a writer arrives while readers are accessing the resource, it waits until those readers
free the resource, and then modifies it. New readers arriving in the meantime will wait too. */

#ifndef __gauge_h__
#define __gauge_h__

#include "headers.h"

// This structure holds both the data and a list of function pointers 
// to point to the relevant functions for manipulation/processing of the data.
typedef struct {

	// PRIME VARIABLES (DATA)

	// The time period (measured in seconds) is used to calculate average rate (measured in bytes per second).
	// It is determined at construction time.
	unsigned int time_period;

	// Gauge rate precision controlling variable (in milliseconds)
	unsigned int precision;

	// The total number of bytes is used to keep a running sum total of the number of bytes counted until the clear 
	// (reset) function is invoked. Note: In order to avoid overflow the clear function must be invoked every so often.
	unsigned long total_num_bytes;

	// Average rate (in bytes per second) over the last X seconds. 
	int average_rate;

	
	// AUXILIARY VARIABLES

	// Keeps track of the number of readers accessing the shared resource at any given point in time
	unsigned int read_count;

	// Time stamp of the last clear (reset) operation
	time_t clear_timestamp;

	// "Circular" array of bytes samples where each element stores a sum total of all bytes added in one 
	// precision resolution unit for a period defined by the value stored in the time_period variable
	// until it is reached and then the arrays wraps around.
	int * bytes_samples;

	// Size of the "Circular" array of bytes 
	unsigned int bytes_samples_size;

	// Index into the bytes_samples circular array
	int index_prev;


	// BINARY SEMAPHORES (MUTEXES)

	// Purpose of each semaphore:
	//
	// arrival_order_mutex - is used to guarantee fair queuing between readers and writers to prevent starvation.
	// It is taken by any entity (either reader or writer) that requests access to the shared resource and it is 
	// released as soon as this entity gains access to the shared resource.
	//
	// access_mutex - is use to provide exclusive access to the shared resource.
	// 
	// readers_mutex - is used to protect the reader counter against conflicting accesses.
	// Since multiple readers can simultaneously access the shared resource we let the first reader get access 
	// to the resource to lock it so that no writer can access it at the same time. Similarly, when a reader is done
	// with the shared resource it will release the lock on it if there are no more readers currently accessing it.
	sem_t arrival_order_mutex, access_mutex, readers_mutex;

	
	// FUNCTIONS

	// Adds to the total number of bytes the value of the argument, which represents the number of bytes in a packet.
	void (*count_packet) (void * self, unsigned int num_bytes);

	// Returns the total number of bytes counted since the last time the gauge was cleared (reset).
	unsigned long (*get_total_bytes) (void * self);

	// Returns the average rate (measured in bytes per second) over the last X (time_period) number of seconds.
	int (*gauge_rate) (void * self);

	// Retrieves time period (measured in seconds) for calculating average rate (measured in bytes per second)
	unsigned int(*get_time_period) (void * self);

	// Sets time period (measured in seconds) for calculating average rate (measured in bytes per second)
	void (*set_time_period) (void * self, unsigned int time_period);

	// Sets the precision of the average rate (measured in bytes per second)
	void(*set_precision) (void * self, unsigned int precision);

	// Sets readers counter
	void (*set_read_count) (void * self, unsigned int read_count);

	// Initializes semaphores
	void (*init_semaphores) (void * self);

	// Releases semaphores
	void (*release_semaphores) (void * self);

	// Sets the total number of bytes to zero
	void (*clear) (void * self);

} gauge;


// Function prototypes
void count_packet(void * g, unsigned int num_bytes);
unsigned long get_total_bytes(void * g);
int gauge_rate(void * g);
void set_time_period(void * g, unsigned int time_period);
void set_precision (void * g, unsigned int precision);
unsigned int get_time_period(void * g);
void set_read_count(void * g, unsigned int read_count);
void init_call_backs(void * self);
void init_semaphores(void * g);
void release_semaphores(void * g);
void clear(void * g);

long getThreadId(void);
time_t getCurrentTime(void);
gauge * constructGauge(unsigned int time_period, unsigned int precision);


// SOME ADDITIONAL THOUGHTS AND IDEAS
// (NEITHER OF THE TYPES BELOW ARE USED IN THIS PROJECT. THEY ARE INCLUDED SOLELY FOR DEMONSTRATION PURPOSES)
//
// The gauge structure could have an internal queue or a linked-list of read/write requests.
// That way anytime an operation (either read or write) is requested, it would be enqueued into 
// the gauge's internal queue and wait for its turn to get processed in the FIFO order.
// For example:
typedef enum { READ, WRITE } RequestType;
typedef struct {
	time_t timestamp;
	RequestType request;
	unsigned int num_bytes;
} Request;

// For the highest degree of precision in measuring the byte rate each write operation could have a timestamp 
// associated with it. Needless to say, this would require saving each write request for a time period equal to
// the time period over which the byte rate is to be calculated. While this approach is expected to produce the 
// highest precision in the calculation of byte rate, it is also expected to be very computationally expensive 
// and thus inefficient from the CPU cycles' utilization.
typedef struct {
	time_t timestamp;
	unsigned int num_bytes;
} Sample;

/* Possible declaration of gauge type
struct Gauge
{
	Gauge(unsigned int time_period, unsigned int precision)
	~Gauge();
	void gauge_rate();
	...

private:

	unsigned int time_period;
	unsigned int precision;
	...
}; */

#endif