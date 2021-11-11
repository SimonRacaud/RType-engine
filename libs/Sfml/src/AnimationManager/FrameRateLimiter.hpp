/*
** PERSONAL PROJECT, 2021
** SINGLY
** File description:
** FrameRateLimiter
*/

#ifndef FRAMERATELIMITER_HPP
#define FRAMERATELIMITER_HPP

#include <functional>

namespace Singly
{
    template <typename functionType>
    class FrameRateLimiter
    {
        public:
            FrameRateLimiter(float frameRate, std::function<functionType> func) : _billion(1000000000), _frameRate(frameRate), _func(func)
            {
                clock_gettime(CLOCK_REALTIME, &this->_lastReference);
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
                struct timespec actual{};

                clock_gettime(CLOCK_REALTIME, &actual);
                nb_sec = actual.tv_sec - this->_lastReference.tv_sec;
                nb_nsec = actual.tv_nsec - this->_lastReference.tv_nsec;
                nb_it = (nb_sec + (nb_nsec / this->_billion)) * this->_frameRate;
                if (nb_it != 0)
                    clock_gettime(CLOCK_REALTIME, &this->_lastReference);
                return nb_it;
            }

        private:
            size_t _billion;
            float _frameRate;
            struct timespec _lastReference;
            std::function<functionType> _func;
    };
};

#endif