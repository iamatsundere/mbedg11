#pragma once
#include <time.h>
#include <stdio.h>

void get_current_time() {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("%s\n", asctime(timeinfo));
}