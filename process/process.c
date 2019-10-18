#include "process.h"

void forkIt(char ** argv)
{
	int status;
	pid_t pid = fork();

	if(pid != 0)
		waitpid(pid, &status, 0);

	else
	{
		execvp(argv[0], argv);
		exit(-1);
	}// end else

}// end forkIt

void forkItBackground(char ** argv)
{
	int status;
	pid_t pid = fork();

	if(pid == 0) //child
	{
		execvp(argv[0], argv);
		exit(-1);
	}

	else //parent
	{

	}// end else
}

void setPath(char * s) {

	int len = strlen(s);

	char *appending = (char *) calloc(len, sizeof(char));
	strncpy(appending, s, 5);
	int append = 0;

	if (strcmp(appending, "$PATH") == 0) // we want to append to end of path not just overwrite
		append = 1; //check variable

	free(appending); //done with that string
	char *newPath;

	if (append)
	{
		newPath = getenv("PATH");
		char *whatGetsAdded = (char *) calloc(len, sizeof(char));
		strncpy(whatGetsAdded, s + 5, len - 5); // copies over rest of string to add to path
		strcat(newPath, whatGetsAdded);
		free(whatGetsAdded);
	}

	else
	{
		setenv("PATH", s, 1);
	}
}

int getHistCount(char * s1, char* s2) {
	char temp[100];

	char *save1;

	strcpy(temp, s1);

	strtok_r(temp, "=", &save1);

	if (strcmp(temp, "HISTCOUNT") == 0) {
		char * token = strchr(s1, '=');
		int num = atoi(token +1);
		return num;
	}

	else {
		char * token = strchr(s2, '=');
		int num = atoi(token +1);
		return num;
	}
}

int getHistFileCount(char * s1, char* s2)
{
	char temp[100];

	char *save1;

	strcpy(temp, s1);

	strtok_r(temp, "=", &save1);

	if (strcmp(temp, "HISTFILECOUNT") == 0) {
		char * token = strchr(s1, '=');
		return atoi(token + 1);
	}

	else {
		char * token = strchr(s2, '=');
		return atoi(token + 1);
	}
}


/*

	if(strcmp(appendCheck, "$PATH:") == 0)
	{

		appendedPath = getenv("PATH");
		append = 1;
		free(appendCheck);
		appendCheck = (char*)calloc(len-10, sizeof(char));
		strncpy(appendCheck, s+10, len-10); // copies over everything to be appended
		strcat(appendedPath, appendCheck);
	}



	if(strcmp(appendCheck, "$PATH:") == 0)
	{

		appendedPath = getenv("PATH");
		append = 1;
		free(appendCheck);
		appendCheck = (char*)calloc(len-10, sizeof(char));
		strncpy(appendCheck, s+10, len-10); // copies over everything to be appended
		strcat(appendedPath, appendCheck);
	}

 */