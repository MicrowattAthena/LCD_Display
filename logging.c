////////////////////////////////////////////

// Generates Log Files

////////////////////////////////////////////

#include <stdio.h>
#include <time.h>

int add_message_log(char* message)
{
	FILE *MessageFile;
	time_t rawtime;
    	struct tm * timeinfo;
	time ( &rawtime);
    	timeinfo = localtime (&rawtime);
	MessageFile=fopen("./logging/message_history.log", "a");
	fprintf(MessageFile, "Time: %s \tSuccessful Message: %s\n", asctime(timeinfo), message);
	printf("\n Message Sent: %s\n", message);
	fclose(MessageFile);
}

int add_error_log(char* message)
{
	FILE *ErrorFile;
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime);
	timeinfo = localtime (&rawtime);
	ErrorFile=fopen("./logging/error_history.log", "a");
	fprintf(ErrorFile, "Time: %s \tError Message: %s\n", asctime (timeinfo), message);
	printf("\n Error: %s\n", message);
	fclose(ErrorFile);

}
