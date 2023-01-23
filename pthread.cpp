#include <iostream>
#include <cmath>
#include <pthread.h>
#include <time.h>

using namespace std;


double total;
clock_t elapsed;
int thread_count;
int order;
int* coff = NULL;
double a, b, h;
int n, local_n;
pthread_mutex_t   mutex, bar_mutex, max_mutex;
pthread_cond_t    bar_cond;

int bar_count = 0;


void getInput();
void printOutput();
double trapezoidal(double local_a, double local_b, double local_n, double h);
double f(double x);
void mutexR(pthread_t* thread_handles);
void* mutexTrape(void* rank);
void barrier();
int main()
{
	total = 0.0;


	cout << "order( has to be from 2 till 10)" << endl;
	cin >> order;

	getInput();

	pthread_t* thread_handles;

	//locate thread handles
	thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
	mutexR(thread_handles);

	printOutput();

	return 0;
}



void getInput() {

	coff = new int[order];

	for (int i = 1; i <= order; i++)
	{
		cout << " Enter cofficient of f(x): " << i << endl;
		cin >> coff[i];
	}

	cout << "thread count" << endl;
	cin >> thread_count;

	cout << "low bound of the f(x)" << endl;
	cin >> a;

	cout << "upper bound of f(x)" << endl;
	cin >> b;

	cout << "number of trapezoids " << endl;
	cin >> n;

	h = (b - a) / n;

	local_n = n / thread_count;
}

void printOutput() {
	cout << " Thread Count: " << thread_count << " Est. Area: " << total << " Elapsed Time: " << elapsed << "ms" << endl;
}

//trapezoidal rule method
double trapezoidal(double local_a, double local_b, double local_n, double h) {
	double integ;
	double x;

	integ = (f(local_a) + f(local_b)) / 2.0;
	x = local_a;
	for (int i = 1; i <= local_n - 1; ++i) {
		x = local_a + i * h;
		integ += f(x);
	}

	integ = integ * h;
	return integ;
}


//compute f(x)
double f(double x) {
	double value = 0;

	for (int i = order; i >= 0; i--) {
		value += coff[i] * pow(x, i);
	}

	return value;
}


void mutexR(pthread_t* thread_handles) {


	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&bar_mutex, NULL);
	pthread_mutex_init(&max_mutex, NULL);
	pthread_cond_init(&bar_cond, NULL);

	//create threads 
	for (long i = 0; i < thread_count; ++i) {
		pthread_create(&thread_handles[i], NULL, mutexTrape, (void*)i);
	}

	//join threads
	for (long i = 0; i < thread_count; ++i) {
		pthread_join(thread_handles[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&bar_mutex);
	pthread_mutex_destroy(&max_mutex);
	pthread_cond_destroy(&bar_cond);


	free(thread_handles);


}

// trapezoidal rule using mutex.
void* mutexTrape(void* rank) {
	double local_a;
	double local_b;
	double my_integral;
	long my_rank = (long)rank;
	clock_t start, end, my_elapsed;



	barrier();
	start = clock();

	//a and b for thread
	local_a = a + my_rank * local_n * h;
	local_b = local_a + local_n * h;

	//integral for current thread
	my_integral = trapezoidal(local_a, local_b, local_n, h);

	//add integral to total
	pthread_mutex_lock(&mutex);
	total += my_integral;
	pthread_mutex_unlock(&mutex);

	end = clock();

	my_elapsed = ((end - start) * 1000) / CLOCKS_PER_SEC;



	pthread_mutex_lock(&max_mutex);
	if (my_elapsed > elapsed) elapsed = my_elapsed;
	pthread_mutex_unlock(&max_mutex);

	return NULL;
}


// synchronization barrier 
void barrier() {
	pthread_mutex_lock(&bar_mutex);

	++bar_count;


	if (bar_count == thread_count) {
		pthread_cond_broadcast(&bar_cond);
	}
	else {
		while (pthread_cond_wait(&bar_cond, &bar_mutex) != 0);
	}

	pthread_mutex_unlock(&bar_mutex);
}