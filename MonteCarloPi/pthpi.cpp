#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <pthread.h>
#include <cmath>
#include <atomic>

std::atomic<int> circles(0);
int tosses_per_thread;

void *find_circles(void *param) {
    unsigned int seed = (unsigned int)(long)param;
    for(int toss = 0; toss < tosses_per_thread; toss++) {
        double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
        double distance_squared = x*x + y*y;
        if(distance_squared <= 1) {
            circles += 1;
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]){
    long long n;
    std::cout << "Enter the number of tosses: ";
    std::cin >> n;

    tosses_per_thread = n / 4;

    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, nullptr, find_circles, (void*)1);
    pthread_create(&t2, nullptr, find_circles, (void*)2);
    pthread_create(&t3, nullptr, find_circles, (void*)3);
    pthread_create(&t4, nullptr, find_circles, (void*)4);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    int remaining = n % 4;
    for (int i = 0; i < remaining; i ++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double distance_squared = x*x + y*y;
        if(distance_squared <= 1) {
            circles += 1;
        }
    }

    double pi_estimate = 4.0 * circles / (double) n;
    std::cout << "Final Estimation of Pi:     " << pi_estimate << "\n";
    std::cout << "Machine Value of Pi:        " << M_PI << "\n";

    return 0;
}