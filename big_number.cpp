#include "big_number.h"
#include "math.h"
#include "string"

using namespace std;

// default constructor, creates a 0
big_number::big_number()
{
	head_ptr = nullptr;
	tail_ptr = nullptr;
	add_node(head_ptr, tail_ptr, '0');//don't change
	positive = true;
	base = 10;
	digits = 1;
}

// int constructor; create big_number from base 10 integer
big_number::big_number(int i)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;
	digits = 0;
	base = 10;
	if (i == 0)
	{
		add_node(head_ptr, tail_ptr, '0');//don't change
		positive = true;
		digits = 1;
	}
	else
	{
		if (i >= 0)
		{
			positive = true;
		}
		else
		{
			i *= -1;
			positive = false;
		}
		base = 10;
		string rem;
		//cout << digits << endl;
		while (i > 0) //walking backwards along the list, adding the last digit of i.
		{
			rem = to_string(i%10);
			add_node(head_ptr, tail_ptr, 0);
			head_ptr->data = rem[0];
			i /= 10;
			digits++;
		}

	}

}

// copy constructor, creates a deep copy of m
big_number::big_number(const big_number& m)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;
	copy_list(m.head_ptr, head_ptr, tail_ptr);
	digits = m.digits;
	positive = m.positive;
	base = m.base;
}

// create a big_number from a string
big_number::big_number(const string& s, unsigned int b)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;
	string str = s;
	if (str[0] == '-')
	{
		positive = false;
		str.erase(0, 1);
	}
	else if (str[0] == '+')
	{
		positive = true;
		str.erase(0,1);
	}
	else
	{
		positive = true;
	}
	while (str[0] == '0' && s.length() > 1)//Remove leading 0's
	{
		str.erase(0,1);
	}
	digits = str.length();
	base = b;
	while (str.length() > 0)//set last char in s to node in list. Walk list backwards.
	{
		add_node(head_ptr, tail_ptr, 0);
		head_ptr->data = str[str.length()-1];
		str.erase(str.length()-1);
	}
}

// destructor
big_number::~big_number()
{
	clear_list(head_ptr, tail_ptr);
}

// assignment operator
big_number& big_number::operator=(const big_number& m)
{
	if (this == &m){}//protects against self assignment
	else
	{
		copy_list(m.head_ptr, head_ptr, tail_ptr);
		base = m.base;
		positive = m.positive;
		digits = m.digits;
	}
	return *this;
}

// set value to original value + b; return answer in original number's base
big_number& big_number::operator+= (const big_number& b)
{
    if (positive == b.positive)
    {
        if (*this >= b)
        this->sum(b);
    }
    else if ((!positive && !b.positive))
    {
        if (*this < b)
        {
            const big_number c(b);
            *this = c;
        }
    }
return *this;
}


// set value to original value * b; return answer in original number's base
big_number& big_number::operator*= (const big_number& b)
{
	big_number c;
	node* cursor1 = b.tail_ptr;
	node* cursor2;
	int zeros;
	int z=0;
	int prod;
	string str;
	while (cursor1 != nullptr)
	{
		zeros = z;
		cursor2 = tail_ptr;//Pointer
		while (cursor2 != nullptr)
		{
			prod = ((int)cursor1->data - 48) * ((int)cursor2->data - 48);//Pointer/Ascii math
			str = to_string(prod);
			for (int i = 0; i < zeros; i++)
			{
				str.append("0");
			}
			big_number d(str, this->base);
			c += d;
			cursor2 = cursor2->prev;//walk list backwards.
			++zeros;
		}
		cursor1 = cursor1->prev;
		++z;
	}
	*this = c;
	return *this;
}

// set value to original value - b; return answer in original number's base
big_number& big_number::operator-= (const big_number& b)
{
	return *this;
}

// set value to original value / b; return answer in original number's base
big_number& big_number::operator/= (const big_number& b)
{
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator%= (const big_number& b)
{
	return *this;
}

// prefix increment
big_number& big_number::operator++()
{
	return *this;
}

// prefix decrement
big_number& big_number::operator--()
{
	return *this;
}

bool operator >(const big_number& a, const big_number& b)
{
	if (a.positive && !b.positive)
	{
		return true;
	}
	else if (!a.positive && b.positive)
	{
		return false;
	}
	else 
	{
		if (a.digits > b.digits)
		{
			return (a.positive);
		}
		else if (a.digits < b.digits)
		{
			return (!a.positive);
		}
		else //If the two numbers are same sign and same number of digits.
		{
			node* cursor1 = a.head_ptr;
			node* cursor2 = b.head_ptr;
			for (unsigned int i = 0; i < a.digits; i++)
			{
				if (cursor1->data > cursor2->data)
				{
					return (a.positive);
				}
				else if (cursor1->data < cursor2->data)
				{
					return (!a.positive);
				}
				cursor1 = cursor1->next;
				cursor2 = cursor2->next;
			}
		}
	}
	return false;
}

bool operator >=(const big_number& a, const big_number& b)
{
	return (a > b || a == b);
}

bool operator <(const big_number& a, const big_number& b)
{
	return (!(a > b) && !(a == b));
}
			
bool operator <=(const big_number& a, const big_number& b)
{
	return (!(a > b));
}
			
bool operator==(const big_number& a, const big_number& b)
{
	if (a.digits != b.digits || a.positive != b.positive)
	{
		return false;
	}
	node* cursor1 = a.head_ptr;
	node* cursor2 = b.head_ptr;
	for (unsigned int i = 0; i < a.digits; i++)
	{
		if (cursor1->data != cursor2->data)
		{
			return false;
		}
		cursor1 = cursor1->next;
		cursor2 = cursor2->next;
	}
	return true;
}
	
bool operator!=(const big_number& a, const big_number& b)
{
	return false;
}

ostream& operator <<(ostream& out, const big_number& n)
{
	node* cursor = n.head_ptr;
	if (!n.positive)
	{
		cout << "-";
	}
	while (cursor != nullptr)
	{
		cout << cursor->data;
		cursor = cursor->next;
	}
	return out;
}

istream& operator >>(istream& in, big_number& n)
{
	clear_list(n.head_ptr, n.tail_ptr);
	string str;
	cin >> str;
	while (str.length() > 0)//set last char in s to node in list. Walk list backwards.
	{
		add_node(n.head_ptr, n.tail_ptr, 0);
		n.head_ptr->data = str[str.length()-1];
		str.erase(str.length()-1);
	}
	return in;
}

big_number operator+(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator-(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator*(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator/(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator%(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number factorial(const big_number& a)
{
	big_number answer;
	return answer;
}

//helper function: assume |*this| >= |m|
big_number& big_number::sum(const big_number& m)
{
    node* cursor = tail_ptr;
    const node* mcursor = m.tail_ptr;
    digits = 0;
    unsigned int carry = 0;    
    while(cursor != nullptr && mcursor != nullptr) 
    {
        unsigned int dig1 = alpha.find(cursor->data);
        unsigned int dig2 = alpha.find(mcursor->data);
        unsigned int result = dig1 + dig2 + carry;
        if (result >= base)
        {
            if (base <= 10) 
                cursor->data = ((result % base)) + '0';
            else
                cursor->data = result + 'a' + 10; 
            carry = 1;
        }
        else
        {
            if (base <= 10)
            {
                cursor->data = result + '0';
            }
            else
                cursor->data = result + 'a' - 10;
            carry = 0;
        }
        cursor = cursor->prev;
        mcursor = mcursor->prev;
        ++digits;
    }
    while (cursor != nullptr)
    {
        unsigned int dig1 = alpha.find(cursor->data);
        unsigned int result = dig1 + carry;
        if (result >= base)
        {
            if (base <= 10)
                cursor->data = ((result % base)) + '0';
            else
                cursor->data = result + 'a' + 10; 
            carry = 1;
        }
        else
        {
            if (base <= 10)
            {
                cursor->data = result + '0';
            }
            else
                cursor->data = result + 'a' - 10;
            carry = 0;
        }
        cursor = cursor->prev;
        ++digits;
    }
    if (carry > 0)
    {
        head_ptr->prev = new node;
        head_ptr->prev->prev = nullptr;
        head_ptr->prev->next = head_ptr;
        head_ptr->prev->data = carry + '0';
        head_ptr = head_ptr->prev;
        ++digits;
    }
    return *this;
}
/*big_number& big_number::diff(const big_number& m)
{
    node* cursor = tail_ptr;
    const node* mcursor = m.tail_ptr;
    digits = 0;
    unsigned int borrow = 0;
    while (cursor != nullptr && mcursor != nullptr)
    {
        if (borrow > 0)
        {
            if (cursor->data == '0')
            {
                cursor->data = alpha[base -1];
            }
            else
            {
                cursor->data = cursor->data - 1;
                borrow = 0;
            }
        }

        unsigned int dig1 = alpha.find(cursor->data);
        unsigned int dig2 = alpha.find(mcursor->data);

        if (dig2 > dig1 && cursor->prev != nullptr)
        { 
            borrow = base;         
        }
        unsigned int result = dig1 + borrow - dig2;
        cursor->data = alpha[result];
    }
    while (cursor != nullptr)
    {
        unsigned int dig1 = alpha.find(cursor->data);
        if (borrow > 0)
        {
            if (cursor->data == '0')
            {
                cursor->data = alpha[base-1];
            }
            else
            {
                cursor->data = cursor->data - 1;
                borrow = 0;
            }
        }
    }
   return *this;
}*/