#pragma once

/**
 * @file Clock.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-24
 */

#include <librtcos/Task.hpp>
#include <librtcos/Scheduler.hpp>
#include <librtcos/utils/MemoryPool.hpp>

namespace rtcos
{
	class Clock
	{
	public:
        class Observer
        {
        public:
            virtual ~Observer() {}

            virtual void notify() = 0;
        };

		Clock(size_t);

        void update();
        bool addAlarm(Observer*, unsigned long long delay);

    protected:
        struct Alarm
        {
            Observer* observer;
            unsigned long long tick;
        };

        void notifyObservers();
        bool isAlarmTriggered(Alarm&);
        void notifyAndDeallocate(Alarm&);

    private:
        utils::MemoryPool<Alarm> pool;
        unsigned long long tick;
	};
}