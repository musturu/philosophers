# Philosophers
Introduction to multi-threading in C


## <div align='center'><h1><a name='Introduction'>Introduction</a></h1></div>

This project is a multithreaded simulation of the Dining Philosophers problem. The problem is a classic multi-process synchronization problem which was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise.

### Problem Statement

The problem consists of N philosophers sitting at a round table who do only three things: eat, think, and sleep.
There is a bowl of spaghetti on the table, but philosophers need two forks to eat it.
Each philosopher can only use the forks to their immediate right and left. 
The philosophers must find a solution that prevents them from starving.

# Project Structure

The project is structured as follows:

- `philo/srcs/`: This directory contains all the source code for the simulation that uses mutexes and threads.
- `philo_bonus/srcs/`: This directory contains all the source code for the simulation that uses Semaphores and processes.
- `Makefile`: This is used to compile the project.

## How to Run

To run the project, follow these steps:

1. Clone the repository
2. Navigate into the cloned repository: `cd <repository_directory>`
3. Compile the project: `make`

make will compile 2 executables, phil and phil_bonus, the first one is based on threads and mutexes, the latter uses semaphores and multi-process instead.
both take the same arguments which are: NUMBER_OF_PHILOSOPHERS 

1. `NUMBER_OF_PHILOSOPHERS`	defines both how many philosophers there are as well as how many forks
2. `TIME_TO_DIE`	defines how much time (milliseconds) it takes for a philosopher to starve
3. `TIME_TO_EAT`	defines how much time (milliseconds) it takes for a philosopher to eat
4. `TIME_TO_SLEEP` defines how much time (milliseconds) it takes for a philosopher to sleep
5. {OPTIONAL} `NUMBER_OF_MEALS` defines how many meals must each philosopher eat before the simulation ends

example : `./philo 5 800 200 200` (in this example the simulation should not stop) 



