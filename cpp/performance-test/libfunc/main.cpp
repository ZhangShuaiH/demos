/*************************************************************************
  Created Time: 2020-04-28 17:33:22
 ************************************************************************/

#include <iostream>
#include <typeinfo>
#include <sstream>
#include "../../include/timeing.h"

using namespace std;
const int SIZE=100000000;
// 除法
void division_int()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		int res = i/2;
	}
	)
}
void division_float()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		float res = i/2.0;
	}
	)
}

void division_float_con()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		float res = i/2.0f;
	}
	)
}
void division_double()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		double res = i/2.0;
	}
	)
}
void printtypeid()
{
	cout<<typeid(2.0l).name()<<endl;
	cout<<typeid(2l).name()<<endl;
	cout<<typeid(2ll).name()<<endl;
	cout<<typeid(long).name()<<endl;
	cout<<typeid(long long).name()<<endl;
}
void test_atoi()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		int res = atoi("123");	
	}			
	)
}
void test_atoi_stringstream()
{
	TIMEING(		
	stringstream ss;
	for(size_t i=0; i<SIZE; i++)
	{
		ss.str("");
		ss<<"123";
		int res;
		ss>>res;
	}
	)	
}
void test_atoi_space()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		int res = atoi("   123        ");	
	}			
	)
}
void test_atof()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		float res = atof("123");	
	}			
	)
}

void test_atof_point()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		float res = atof("12.3");	
	}			
	)
}
void test_atof_stringstream()
{
	TIMEING(		
	stringstream ss;
	for(size_t i=0; i<SIZE; i++)
	{
		//static stringstream ss;
		ss.str("");
		ss<<"12.3";
		float res;
		ss>>res;
	}
	)	
}
void test_atof_space()
{
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		float res = atof("  123  ");	
	}			
	)
}
void test_copy_string()
{
	string str = "hello world!";
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		string str2 = str;
		char c = str2[3];
	}	
	)
	
	TIMEING(
	for(size_t i=0; i<SIZE; i++)
	{
		const string str2 = str;
		char c = str2[3];
	}	
	)
}
int main()
{
  	division_int();
  	division_float();
  	division_float_con();
  	division_double();

  	cout<<endl;
  	test_atoi();
	test_atoi_stringstream();
  	test_atoi_space();

	cout<<endl;
  	test_atof();
  	test_atof_point();
	test_atof_stringstream();
  	test_atof_space();

    cout<<endl;	
	test_copy_string();

	return 0;
}
