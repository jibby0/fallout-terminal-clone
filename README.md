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
            MinGW installed with the following packages:
			- mingw32-gcc
            - mingw32-pdcurses (dev and dll)

		Once the above dependencies are satisfied, simply open 
		a command prompt in the source directory and run:
            make

        If you get an error about gcc not being found, you most
        likely didn't add MinGW tools to your path. Either do
        that, or change the line:
    CC = gcc
        to read:
    CC = C:\MinGW\bin
        (assuming you installed MinGW in that location)

	LINUX

		Requirements:
			- gcc
			- ncurses

		Once the above dependencies are satisfied, simply open 
		a terminal in the source directory and run:
            make
		
	OSX
		
		Requirements:
			Xcode Tools (just run xcode-select --install)
		
		Once this is finished, simply open 
		a terminal in the source directory and run:
            make


TODO list:

    Custom movement keys
    Screen centering
	Possible mouse support?


Bugs:

    Fallout 3 doesn't seem to play nice with the launching. But I haven't
    tested this much. You may just be better off putting this program in a
    batch file.


Thanks to:

    /u/aftli_work for suggesting macros (before I knew what they were)


I do not own the idea for this game, nor do I claim any ownership
of Fallout 3 or Fallout: New Vegas. Those copyrights are the 
property of Bethesda Softworks.
