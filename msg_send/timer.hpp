/*
 * Timer.h
 *
 *  Created on: Nov 19, 2014
 *      Author: laura
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdint>
   using namespace std::chrono;
class Timer
{

    public:
        Timer() : _tstart(std::chrono::steady_clock::now()){};
        ~Timer()
        {
            _tend = std::chrono::steady_clock::now();
            DisplayElapsedNanos();
        };

        void ResetTime()
        {
            _tstart = std::chrono::steady_clock::now();
        };

        void DisplayElapsedNanos()
        {
            duration<double> time_diff = _tend - _tstart;
            std::cout<<"Elapsed time: "<<duration_cast<nanoseconds>(time_diff).count()<<" ns"<<std::endl;
        }

    private:
        std::chrono::steady_clock::time_point _tstart, _tend;

};

#endif /* TIMER_H_ */
