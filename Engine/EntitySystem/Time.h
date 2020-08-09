#pragma once

namespace EntitySystem {
	class Time
	{
		long time;
	public:
	    static Time fromSeconds(float seconds)
        {
	        return Time(seconds * 1000000.f);
        }
	    Time(): time(0) {};
		Time(long time) : time(time) {};
		long asMicroseconds() { return time; }
		int asMilliseconds() { return time / 1000; }
		float asSeconds() {
			return (float)time / 1000000.f;
		}
        Time& operator+=(const Time& rhs)
        {
		    this->time += rhs.time;
            return *this; // return the result by reference
        }

        // friends defined inside class body are inline and are hidden from non-ADL lookup
        friend Time operator+(Time lhs,        // passing lhs by value helps optimize chained a+b+c
                           const Time& rhs) // otherwise, both parameters may be const references
        {
            lhs += rhs; // reuse compound assignment
            return lhs; // return the result by value (uses move constructor)
        }

        friend bool operator<(const Time& l, const Time& r)
        {
            return l.time < r.time;
        }

        friend bool operator> (const Time& lhs, const Time& rhs){ return rhs < lhs; }
        friend bool operator<=(const Time& lhs, const Time& rhs){ return !(lhs > rhs); }
        friend bool operator>=(const Time& lhs, const Time& rhs){ return !(lhs < rhs); }
		static Time Elapsed;
	};

}