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
			- mingw-g++ (C/C++ support for MinGW)

		Once MinGW is installed with support for C/C++ compilation, simply copy
		everything from src\deps\ into your MinGW folder. This will install the
		necessary PDcurses libraries.
		
		Once this is finished, you can compile by running:
		gcc FalloutTerminal.c -lpdcurses -o FalloutTerminal.exe

		Make sure you include pdcurses.dll (found in src\dep\bin)
		with your binary.

	LINUX

		Requirements:
			- gcc
			- ncurses

		Once the above dependencies are satisfied, simply open 
		a terminal in the src/ directory and run:
		gcc FalloutTerminalU.c -lncurses -o FalloutTerminal
		
	OSX
		
		Requirements:
			Xcode Tools
		
		Install nurses on OS X as described here:
			https://gist.github.com/cnruby/960344
		
		Once this is finished, simply open 
		a terminal in the src/ directory and run:
		gcc FalloutTerminal.c -lncurses -o FalloutTerminal


Plans for the Future

	ADD a config file that allows you to:
		change difficulty
		change whether skips/shortcuts are available
		launch another program after it's done
	Possible mouse support?



I do not own the idea for this game, nor do I claim any ownership
of Fallout 3 or Fallout: New Vegas. Those copyrights are the 
property of Bethesda Softworks.

The included PDCurses dependencies are listed as Public Domain,
and can be found at http://pdcurses.sourceforge.net/
