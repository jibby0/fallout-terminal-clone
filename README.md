# fallout-terminal-clone
What is fallout-terminal-clone?
	
	fallout-terminal-clone is a modest recreation of the terminal hacking system
	in Fallout 3 and Fallout: New Vegas developed with curses. It runs directly
	in your terminal or command prompt. I mostly did this as a fun and 
	interesting way to explore C.
	
Instructions

	Use WASD to move, and ENTER to choose your selected letter. Ctrl-C to quit.

Building

	WINDOWS

		Requirements:
            Have MinGW installed with the following packages:
			- mingw32-gcc
            - mingw32-pdcurses (dev and dll)

		Once MinGW is installed with support for C/C++ compilation, simply copy
		everything from src\deps\ into your MinGW folder. This will install the
		necessary PDcurses libraries.
		
		Once this is finished, you can compile by running:
            make
        In the source directory.

	LINUX

		Requirements:
			- gcc
			- ncurses

		Once the above dependencies are satisfied, simply open 
		a terminal in the source directory and run:
            make
		
	OSX
		
		Requirements:
			Xcode Tools
		
		Install ncurses on OS X as described here:
			https://gist.github.com/cnruby/960344
		
		Once this is finished, simply open 
		a terminal in the src/ directory and run:
		gcc FalloutTerminal.c -lncurses -o FalloutTerminal


TODO list:

    Custom movement keys
    Screen centering
	Possible mouse support?

Thanks to:
    /u/aftli_work for suggesting macros (before I knew what they were)


I do not own the idea for this game, nor do I claim any ownership
of Fallout 3 or Fallout: New Vegas. Those copyrights are the 
property of Bethesda Softworks.
