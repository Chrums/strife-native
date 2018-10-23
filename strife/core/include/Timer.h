#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace Strife {
    namespace Core {
        
        class Timer {
        public:
        
            struct Time {
            public:
                
                const unsigned long total;
                const unsigned long delta;
                
                Time(unsigned long total, unsigned long delta);
                
            };
            
            Timer();
            ~Timer() = default;
            
            const Time update();
            
        private:
            
            std::chrono::steady_clock::time_point initial_;
            std::chrono::steady_clock::time_point previous_;
            
        };
        
    }
}

#endif