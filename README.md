# cputil
Generate a workload cost specific cpu usage

Usage hint:

cputil util [time]

Now there are two parameters, the first one used to specify a cpu utilization
(75 stands for 75%, 800 stands for 800% if exist more than 8 cpus in your
system). The second one is used to set the run time in seconds, this parameter
is optional if not set (default) keep running until be killed.

Example:

1. run a 75% cpu.util for 30s

$ cputil 75 30

2. run a 800% cpu.util

$ cputil 800
