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
		gcc FalloutTerminalWin.c -lpdcurses -static -o FalloutTerminal.exe

		The -static flag is optional, but ensures you won't need to bundle
		libpdcurses.dll with your binary.

	LINUX

		Requirements:
			- gcc
			- ncurses

		Once the above dependencies are satisfied, simply run:
		gcc FalloutTerminalLinux.c -lncurses -o FalloutTerminal
		
	OSX
		
		I don't have an OSX system to test compilation on. I would 
		reccommend installing ncurses, then attempting the Linux
		build instructions.


Plans for the Future

	ADD a config file that allows you to:
		change difficulty
		change whether skips/shortcuts are available
		launch another program after it's done
	Possible mouse support?



I DO NOT OWN THE IDEA FOR THIS GAME, NOR DO I CLAIM ANY OWNERSHIP
OF FALLOUT 3 OR FALLOUT: NEW VEGAS. THOSE COPYRIGHTS ARE THE 
PROPERTY OF BETHESDA SOFTWORKS.
