# simple_packet_sniffer
sniffer connects to the network, and can read packets passing through it

// Requirements

1) Daemon should sniffs packet
		All good, tested by Postman, 

2) IP search time complexity should be log(N) // realization permits only sinle container 
                                             // in future some kind of constructor will be added
	Hash Table was choosed as a container, so it is even better 
		You did not said anything about space complexity)

3) Statistic should be persistent through reboots
	custom Serialisation & Deserialisation was implemented 

4) CLI, another proccess that interacts with the daemon

	i need to hear opinion of experienced dev about cli

		main problem
		I cannot read input from stdin in multi-proccesing program properly (menu should take command from user)
			available solutions:
			1) reading data from file (slow)
			2) use add. lib for example progbase  Console_isKeyDown // if have no input return '\0' (conflict with task)
			3) create procces with own memory space (how to influence to another procces)
			4) simply using threads)


	so not implemented

5) CLI should support commands
	-

6) Daemon could be started independently as well as trough cli
	daemon can be started from daemon./out & cli.out

7) Build automation tool should be used(make is preferable)
	as you wish)

8) C program language is preferable to be used
	i did not like creating containers in C

9) Be kind and do not uploading include files for your IDE
	Ok, i will use .gitignore

10) It`s up to you to make choice unless otherwise specified
	I spend a lot of time for reinventing the bike

11) Clean and safe code
	Code is clean, 
	you can change log.txt data only with sudo 
	CLI control not implemented, here is main source of available security weaknesses



I work with networks at this level at first time, so i expanded this project from existing one //
This system is not sufficiently tested // my linux temp. have not acces to the internet so ...

in next version, menu, multiply interface for sniffing, deep testing of project will be added approximately 18 march

will be happy, to hear your proposition and ideas
