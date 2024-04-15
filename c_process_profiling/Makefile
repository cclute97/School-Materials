
CXX=gcc
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

all: profiler.c 
	$(CXX) $(CXXFLAGS) -o profiler profiler.c
		
clean:
	rm -f profiler *.o *.tar
	
package:
	tar -cf Chris-Clute-ExtraCredit.tar README.md Makefile profiler.c