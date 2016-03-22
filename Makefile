

Scheduler : Job.o Scheduler.o Debug.o main.o
	g++ Job.o Scheduler.o Debug.o main.o -o Scheduler 

main.o : main.C
	g++ -std=c++0x -c main.C

Scheduler.o : Scheduler.C
	g++ -std=c++0x -c Scheduler.C

Job.o : Job.C
	g++ -std=c++0x -c Job.C 

Debug.o : Debug.C
	g++ -Wno-format-security -std=c++0x -c Debug.C

