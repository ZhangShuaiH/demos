/*************************************************************************
  Created Time: 2020-04-13 15:44:34
 ************************************************************************/
#ifndef TIMEING_H
#define TIMEING_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define TIMEING(statement) { \
	struct timeval t1,t2; \
	gettimeofday(&t1, NULL); \
	statement; \
	gettimeofday(&t2, NULL); \
	long dif = (t2.tv_sec - t1.tv_sec)*1000000 + (t2.tv_usec - t1.tv_usec); \
	printf("%d us\n", dif); \
}
//void demo()
//{
//	TIMEING(slee(1));
//}

#endif
