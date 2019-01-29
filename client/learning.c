 When you compile your program under UNIX, the name of your executable is usually a.out. The ./ part is there because the current directory is not commonly placed on the default execution path 
 
 
 argc is the count of argument. argv is short for argument variable. It will contain all arguments passed on the command line. argv[1] contains the first argument so atoi(argv[1]) will convert the first argument to an int
 
 
 
 su     # Need privilege to set real-time scheduling policies
