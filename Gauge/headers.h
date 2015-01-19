
/* Designed and written by Mikhail Jacques
Email: jacques.mikhail@gmail.com
GitHub: https://github.com/MikhailJacques
LinkedIn: https://www.linkedin.com/in/mikhailjacques
*/

#ifndef __headers_h__
#define __headers_h__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>

#define DEBUG 0
#define NUM_ITERATIONS 30
#define MAX_NUM_READERS 10
#define MAX_NUM_WRITERS 10
#define MAX_TIME_PERIOD 60
#define MIN_PRECISION 1000
#define ONE_THOUSAND_MILLISECONDS 1000

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#endif