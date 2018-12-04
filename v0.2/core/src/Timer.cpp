#include "Timer.h"

using namespace Strife::Core;
using namespace std;

Timer::Time::Time(const unsigned long total, const unsigned long delta)
    : total(total)
    , delta(delta) {}

Timer::Timer()
    : initial_(chrono::steady_clock::now())
    , previous_(chrono::steady_clock::now()) {}

const Timer::Time Timer::update() {
    chrono::steady_clock::time_point current = chrono::steady_clock::now();
    unsigned long total = chrono::duration_cast<chrono::milliseconds>(current - initial_).count();
    unsigned long delta = chrono::duration_cast<chrono::milliseconds>(current - previous_).count();
    previous_ = current;
    return Time(total, delta);
}