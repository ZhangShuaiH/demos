/*************************************************************************
  Created Time: 2020-04-13 15:31:40
 ************************************************************************/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "timeing.h"

using namespace std;

void endian_reverse()
{
	static int il = sizeof(int);
	char ccc[il];
	int ii = 0x12345678;
	memcpy(&ccc[0], &ii, il);
	for(int i=0; i<il/2; i++)
	{
		swap(ccc[i], ccc[il-1-i]);
	}
	memcpy(&ii, &ccc[0], il);
}
void endian_reverse2()
{
	static int il = sizeof(int);
	char ccc[il];
	int ii=0x12345678;
	ii=(int)(  ((ii & 0x000000ff)<<24) | ((ii&0x0000ff00)<<8) | ((ii&0x00ff0000)>>8) | ((ii&0xff000000)>>24)  );
	memcpy(&ccc[0], &ii, il);
}

int main()
{
	int gi=1000000;
	TIMEING(for(int i=0; i<gi; i++){endian_reverse();});// O2 优化时相差不大，无优化时慢一倍
	TIMEING(for(int i=0; i<gi; i++){endian_reverse2();});
}


