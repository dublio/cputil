# cputil

The **cputil** can generate a workload cost specific cpu usage.

## Usage

	cputil util [time]

	cputil -h / --help
		show help

	cputil --version
		show version

Now there are two parameters:

- The first one used to specify a cpu **utilization**
(75 stands for 75%, 800 stands for 800% if there are enough cpus in your system).

- The second one is used to set the **run time** in unit of seconds, this parameter is optional if it was not specified(default), **cputil** will keep running until be killed.

### Example

	1. run a 75% cpu.util for 30s
	$ cputil 75 30

	2. run a 800% cpu.util
	$ cputil 800
