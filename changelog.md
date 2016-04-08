Programming an LED Display

Changelog


<<<<<<< HEAD
V 0.1.1

	Added Message History to /logging/
	Added Error History to /logging/	
	To Do:

	Create Folder if it doesn't exist?
=======
>>>>>>> ffe8f9e79a818dc5d2b269660d407b3c13415c92
V 0.1.0

	Cleaned up Upper Case Characters

	To Do:
	
	Create Logs (Error Log, Message History)
	Create Config (So transition speed, type, upper case etc. can all be set)
	Check lower case characters and correct
	Force new line on punctuation.
	Add Arguments for Screen Variables
	Find Fix for Messages Being Too Long
	Add Displaying DateTime

V 0.0.11

	Partially Cleaned Up Code
	
	To Do:

	Finish Clean Up (Go Through Variable Names, Reduce no. of Class Variables, remove unneccessary libraries)
	Add Arguments for Screen Variables
	Find Fix for Messages Being Too Long
	Add Displaying DateTime

V 0.0.10

	Truncation should now function correctly
	Non-Mapped Characters printed as a space
	
	To Do:

	Add Arguments for Screen Variables (Possibly Config File?)
	Clean up Code
	(Find Fix for Messages Being Too Long)

V 0.0.9

	(Buggy) Single Screen Mode Messages are now truncated at ' ', '!', '?', '.'
	Working fine on Pi

	To Do:
	
	Add Arguments for Screen Variables
	Bugfix Message Truncation (Sometimes end of message is lost, break on message with no spaces)
	Massively clean up code

V 0.0.8 

	Fixed Screen Effects
	
	To Do:

	Add Arguments for Screen Variables
	Test Portability to Pi 
V 0.0.7 
	
	Screen Sizing now works. 
	Bug with A character resolved (USBDev not opened as raw output, 10 being seen as \r\n)
	
	To Do:

	Fix Screen Effects (Most Effects are fine but No Effect with multiple lines always zooms through text)
	Add Arguments for Screen Variables (screen stay etc.)
	
V 0.0.6 
	
	Many Changes Made: New non-monospace font used.
	Flags are now defined

	To Do:

	Work Out Screen Size (Currently based on old system)
	BugFix (Message starting with A breaks, has newline in it?)

V 0.0.5 
	
	Character Map nor implemented: Automatically generated
	Main function now implemented. 

	To Do:

	Fix Character Maps (Some characters dont look good)
	Define Flags for Effect Types etc.
	complete readme

V 0.0.4

	User Input is now parsed correctly.
	Character Map for A, F and Space.

	To Do:

	Complete Character Maps
	Complete readme
	Test

V 0.0.3

	Multiple Screens now display based on user input
	Parsing User Input - Not quite using the string yet, just the length
	Started Working on Character Maps

	To Do:

	Complete user control over display
	Complete character maps
V 0.0.2

	Cleaned up Main Code a bit - Now Array Defined for each screen
	Worked out How to display multiple screens - not implemented yet. See command_constructors.h

	To Do:

	Allow user some control over what is displayed
	Display Character Maps
V 0.0.1

	Worked out how to display one screen of information.
	No ability to change what is displayed
	No ability to change how it is displayed
	No Ability to display multiple screens

	To Do:

	Work out how more than one screen width is displayed
	Allow User some control over what is displayed
