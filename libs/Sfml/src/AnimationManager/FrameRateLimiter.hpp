/*
** PERSONAL PROJECT, 2021
** SINGLY
** File description:
** FrameRateLimiter
*/

#ifndef FRAMERATELIMITER_HPP
#define FRAMERATELIMITER_HPP

#include <functional>
#include <chrono>

namespace Singly
{
    template <typename functionType>
    class FrameRateLimiter
    {
        public:
            FrameRateLimiter(float frameRate, std::function<functionType> func) : _billion(1000000000), _frameRate(frameRate), _func(func)
            {
                _lastReference = std::chrono::steady_clock::now();
            }
            ~FrameRateLimiter() = default;

            template <typename... constructorParams> void runIt(constructorParams &&... params)
            {
                for (size_t i = this->getIterationNumber(); i; i--)
                    this->_func(std::forward<constructorParams>(params)...);
            }

        protected:
            size_t getIterationNumber()
            {
                size_t nb_it = 0;
                size_t nb_sec = 0;
                long double nb_nsec = 0;
                auto start = std::chrono::steady_clock::now();

                nb_sec = std::chrono::duration_cast<std::chrono::seconds>(start.time_since_epoch()
                    - _lastReference.time_since_epoch()).count();
               
                nb_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    start.time_since_epoch() - _lastReference.time_since_epoch()).count();
                nb_it = (nb_sec + (nb_nsec / this->_billion)) * this->_frameRate;
                if (nb_it != 0)
                    _lastReference = std::chrono::steady_clock::now();
                return nb_it;
            }

        private:
            size_t _billion;
            float _frameRate;
            std::chrono::steady_clock::time_point _lastReference;
            std::function<functionType> _func;
    };
};

#endif