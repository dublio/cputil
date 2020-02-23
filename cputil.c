/*
 * cputil - the cpu workload generator
 *
 * Copyright (C) 2018 Weiping Zhang <zwp10758@gmail.com>
 *
 * The license below covers all files distributed with cputil unless otherwise
 * noted in the file itself.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

unsigned int util;
unsigned int thread_count;
unsigned int run_time;
struct tinfo {
	pthread_t pthread;
	unsigned int index;
	unsigned int cpu_util;
} *tinfo;

static int timeafter(struct timespec x, struct timespec y)
{
	if (y.tv_sec > x.tv_sec)
		return 1;
	if (y.tv_sec == x.tv_sec && y.tv_nsec > x.tv_sec)
		return 1;

	return 0;
}

void run_cpu_util_per_thread(unsigned int u)
{
	struct timespec start, busy_end, t;
	long busy, idle; /* ns */

	if (u > 100) {
		fprintf(stderr, "force %u to 100\n", u);
		u = 100;
	}

	/* split 1s to 2 part, busy time, idle time */
	busy = 1E7 * u;
	idle = 1E7 * (100 - u);

	clock_gettime(CLOCK_MONOTONIC, &start);

	if (busy + start.tv_nsec > 1E9) {
		busy_end.tv_sec = start.tv_sec + 1;
		busy_end.tv_nsec = start.tv_nsec + busy - 1E9;
	} else {
		busy_end.tv_sec = start.tv_sec;
		busy_end.tv_nsec = start.tv_nsec + busy;
	}

	/* busy loop */
	do {
		clock_gettime(CLOCK_MONOTONIC, &t);
	} while(!timeafter(busy_end, t));

	/* idle */
	usleep(idle / 1000);
}

void * thread_fn(void *arg)
{
	struct tinfo *tinfo = (struct tinfo *)arg;

	while (1)
		run_cpu_util_per_thread(tinfo->cpu_util);

	return NULL;
}

void print_help(void)
{
	fprintf(stderr, "cputil util [time]\n");
}

int main(int argc, char **argv)
{
	int ret;
	unsigned int i, sys_cpu_count, util_thread;

	if (argc > 3 || argc < 2) {
		print_help();
		return -1;
	}

	if (sscanf(argv[1], "%u", &util) != 1) {
		print_help();
		return -1;
	}

	if (argc == 3) {
		if (sscanf(argv[2], "%u", &run_time) != 1) {
			print_help();
			return -1;
		}
	}

	sys_cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
	/* calculate how many threads need create */
	thread_count = (util + 99) / 100;
	if (thread_count > sys_cpu_count)
		thread_count = sys_cpu_count;

	util_thread = util / thread_count;

	tinfo = malloc(thread_count * sizeof(* tinfo));
	if (!tinfo) {
		fprintf(stderr, "please input a valid target cpu utilization\n");
		return -1;
	}

	/* create thread */
	for (i = 0; i < thread_count; i++) {
		tinfo[i].pthread = 0;
		tinfo[i].index = i;
		tinfo[i].cpu_util = util_thread;
		ret = pthread_create(&tinfo[i].pthread, NULL, thread_fn,
			&tinfo[i]);
		if (ret) {
			fprintf(stderr, "create thread %u failed\n", i);
			goto destroy_thread;
		}
	}

	if (run_time)
		sleep(run_time);
	else
		while (1)
			sleep(10);
destroy_thread:
	while (i--) { 
		ret = pthread_cancel(tinfo[i].pthread);
		if (ret)
			fprintf(stderr, "cancel thread %u,%s\n", i, strerror(ret));
		ret = pthread_join(tinfo[i].pthread, NULL);
		if (ret)
			fprintf(stderr, "join thread %u,%s\n", i, strerror(ret));
	}

	free(tinfo);
}
