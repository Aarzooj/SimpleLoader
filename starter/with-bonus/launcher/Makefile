#Compile the launch.c by linking it with the lib_simpleloader.so
all:
	gcc -m32 -o launch launch.c -L/home/anushka_04/OS-Assignment1/starter/with-bonus/bin -Wl,-rpath,/home/anushka_04/OS-Assignment1/starter/with-bonus/bin -l_simpleloader

#Provide the command for cleanup
clean:
	-@rm -f launch