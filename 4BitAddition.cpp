
/*
there are two parts in the main functions:
	part one:  first packing four integers into two unsigned char which then with the passed to the add_2_4bit ints() which return us an unsigned char. which and pointer to two ints(ans1 and ans2) then get passed to unpack(). after unpack the values in ans1 and ans2 are the sum of the the intial ints(Ans1 = 1st + 3rd int, Ans2 = 2nd +4th int).
	part two: first pack two ints togehter into an unsigned char and then get another a nother unsigned char "x2" using method div_4_bit_ints() which take first unsigned char as a parametere. then it unpack x2 into 2 ints and print it. 
******they both have three examples
there are seven additional methods:
	1.pack(): it takes two ints a and b as parameters and returns a unsigned char which is a int a and b packed.
	2.unpack(): it takes an unsigned char(which is constant) and two pointers to ints as parameters and then unpack the char a into two ints and store them into the pointers given.
	3.add_2_4bit_ints() takes an two unsigned chars(a and b) as paramters.Then it excecutes unpack method twice  and get int x1,x2,x3 and x4, then it add x1 , x3 and x2 , x4 which then it pack and return a unsigned char.
	4.Add(): takes two ints as parameters and return the sum of them.
	5.subtract(): takes two ints (a,b) as parameters and return a-b.
	6.divide(): takes the pointers to two ints and return the int part of first int divided by second int.
	7. div_4bit_int(): it takes an unsigned char x as parameters. then it unpack char x into two ints(num , divisor) then  find the intger and fractional part of num/deivisor and pack them into an unsigned char and return it.
*/


#include <iostream>
using namespace std;

unsigned char pack(int a, int b) { 
	char x = (a << 4);
	char x2;
	if (b < 0) {
		x2 = (b ^ 240);
	}
	else {
		x2 = b;
	}
	return(x | x2);
}

void unpack(unsigned char const x, int* a, int* b) {
	*a = (x >> 4);
	char x1 = (x & 15);
	if ((x1&(1<<3))!=0) {
		*b = (x1 | -2);
	}
	else {
		*b = x1;
	}

	

}

unsigned char add_2_4bit_ints(unsigned char a, unsigned char b) {
	int x1, x2,x3,x4;
	unpack(a, &x1, &x2);
	unpack(b, &x3, &x4);
	while (x3 != 0) {
		int carry = x1 & x3;
		x1 = x1 ^ x3;
		x3 = carry << 1;
	}
	while (x4 != 0) {
		int carry = x2 & x4;
		x2 = x2 ^ x4;
		x4 = carry << 1;
	}
	

	return pack(x1, x2);
}

unsigned int Add(unsigned int a, unsigned int b)
{
	unsigned int carry = a & b;
	unsigned int result = a ^ b;
	while (carry != 0)
	{
		unsigned int shiftedcarry = carry << 1;
		carry = result & shiftedcarry;
		result ^= shiftedcarry;
	}
	return result;
}

int subtract(int x, int y)
{
	while (y != 0)
	{
		int borrow = (~x) & y;
		x = x ^ y;
		y = borrow << 1;
	}
	return x;
}

int divide(int* num, int* divisor) {
	int sum = 0, count = 0;
	while (*num >= *divisor) {
		sum = Add(sum, *divisor);
		*num = subtract(*num, *divisor);
		count++;
	}
	return count;
}

unsigned char div_4bit_int(unsigned char x) {
	int num, divisor,a,b;
	unpack(x, &num, &divisor);
	a = divide(&num,&divisor);
	num = num << 3;
	b =divide(&num,&divisor) ;
	return pack(a, b);


}

int main()
{	

	
//this code is for add_2_4bit_ints()
	cout << "**This is the add_2_bit_int part**" << endl;
	unsigned char x, y, ans;
	int ans1, ans2;
	
	//Example 1
	cout << "Example 1" << endl;
	cout <<"6 -2"<< endl;
	x = pack(6, -2);
	cout <<"1  7"<< endl;
	y = pack(1, 7);
	cout << "----" << endl;
	ans = add_2_4bit_ints(x, y);
	unpack(ans, &ans1, &ans2);
	cout <<  ans1 << "  " << ans2 << endl;
	cout <<  endl;
	
	//Example 2
	cout << "Example 2" << endl;
	cout <<"5 -1"<< endl;
	x = pack(5, -1);
	cout <<"3  5"<< endl;
	y = pack(3, 5);
	cout << "----" << endl;
	ans = add_2_4bit_ints(x, y);
	unpack(ans, &ans1, &ans2);
	cout << ans1 << "  " << ans2 << endl;
	cout <<  endl;
	
	//Example 3
	cout << "Example 3" << endl;
	cout <<"4  2"<< endl;
	x = pack(4, 2);
	cout <<"-1 3"<< endl;
	y = pack(-1, 3);
	cout << "----" << endl;
	ans = add_2_4bit_ints(x, y);
	unpack(ans, &ans1, &ans2);
	cout << ans1 << "  " << ans2 << endl;
	cout <<  endl;
	
	


	//this code is for div_4bit_int
	cout << "**This is the div_4_bit_int part**" << endl;
	int integer_part, fractional_part;
	unsigned char x1,x2;

	
	//Example 1
	cout << "Example 1" << endl;
	x1 = pack(7, 3);
	x2=div_4bit_int(x1);
	unpack(x2, &integer_part, &fractional_part);
	cout << integer_part << "  " << fractional_part << endl<<endl;
	
	//Example 2
	cout << "Example 2" << endl;
	x1 = pack(5, 4);
	x2=div_4bit_int(x1);
	unpack(x2, &integer_part, &fractional_part);
	cout << integer_part << "  " << fractional_part << endl << endl;


	//Example 3
	cout << "Example 3" << endl;
	x1 = pack(6, 2);
	x2=div_4bit_int(x1);
	unpack(x2, &integer_part, &fractional_part);
	cout << integer_part << "  " << fractional_part << endl << endl;
	


}

