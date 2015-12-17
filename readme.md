Programming an LED Display

Changelog

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
