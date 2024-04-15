
CXX=gcc
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

all: scheduler.c 
	$(CXX) $(CXXFLAGS) -o scheduler scheduler.c
		
clean:
	rm -f scheduler *.o *.zip
	
package:
	zip Chris-Clute-HW5.zip README.txt Makefile scheduler.c
