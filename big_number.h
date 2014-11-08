#include "doubly_linked_list.h"

using namespace std;

class big_number 
{
	public:
	
		// constructors (work like init() methods)
		big_number();//done
		big_number(int i);//done
		big_number(const big_number& m, unsigned int b);//done
		big_number(const big_number& m);//done
		big_number(const string& s, unsigned int base);//done
		
		// assignment operator
		// big_number a = 98; big_number b = 0; ... b = a;
		big_number& operator=(const big_number& m);//done
		
		// destructor (works like destr() method)
		~big_number();//done
	
		// self-assigning arithmetic operators
		big_number& operator+=(const big_number& addend);//done
		big_number& operator-=(const big_number& subtractand);//done
		big_number& operator*=(const big_number& multiplicand);//done
		big_number& operator/=(const big_number& divisor);
	
		// positive modulus
		big_number& operator%=(const big_number& divisor);
		
		// overload prefix increment
		big_number& operator++();//done
		// overload prefix decrement
		big_number& operator--();//done
		
		// input and output operators
		friend std::ostream& operator<<(std::ostream& os, const big_number& bignum);//done
		friend std::istream& operator>>(std::istream& is, big_number& bignum);//done
		
		// arithmetic operators
		friend big_number operator+(const big_number& a, const big_number& b);//done
		friend big_number operator-(const big_number& a, const big_number& b);//done
		friend big_number operator*(const big_number& a, const big_number& b);//done
		friend big_number operator/(const big_number& a, const big_number& b);//done
		friend big_number operator%(const big_number& a, const big_number& b);//done
		// hard to do without fast multiplication
		friend big_number factorial(const big_number& a);//done

		// comparison operators
		friend bool operator>(const big_number& a, const big_number& b);//done
		friend bool operator>=(const big_number& a, const big_number& b);//done
		friend bool operator<(const big_number& a, const big_number& b);//done
		friend bool operator<=(const big_number& a, const big_number& b);//done	
		friend bool operator==(const big_number& a, const big_number& b);//done
		friend bool operator!=(const big_number& a, const big_number& b);//done

	private:
	
		node* head_ptr;
		node* tail_ptr;
		unsigned int digits;
		bool positive;
		unsigned int base;
        string alpha = "0123456789abcdefghijklmnopqrstuvwxyz";
		
		// helper functions can go here
        big_number& sum(const big_number& m);//done
        big_number& diff(const big_number& m);//done
        big_number& updateDigits();//done

};
