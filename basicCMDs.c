/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Ultrashell.
 
     The Ultrashell is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Ultrashell is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Ultrashell.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *  @author Peter Hösch aka. BlitzBasic <peter.hoesch@infinitycoding.de>
 **/



#include <basicCMDs.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

extern int input;

/**
 * @brief the echo function
 */

int echo(int argc, char **argv)
{
	int counter;

	for(counter = 1; counter < argc; counter++)
	{
		printf("%s", argv[counter]);
		printf(" ");
	}

	printf("\n");

	return 0;
}


/**
 * @brief execs a program and returns its return value
 */

int exec(int argc, char **argv)
{
    int return_value = 0;
    pid_t pid = 0;

    if(argc < 2)
    {
        printf("exec: incorrect number of arguments\n");
        return 1;
    }
/*
    if(access(argv[1], F_OK) == -1)
    {
        printf("exec: file does not exist\n");
        return 2;
    }

    if(access(argv[1], X_OK) == -1)
    {
        printf("exec: file is not executeable\n");
        return 3;
    }
*/
    if((pid = fork()) == 0)
    {
		void *envp[] = {NULL};
        int ret = execve(argv[1], &argv[1], NULL);
		if(ret < 0)
		{
			printf("Error in execve.\n");
		}
		exit(-1);
    }
    else
    {
        waitpid(pid, &return_value, 0);
        //return_value = WEXITSTATUS(return_value);

		lseek(input, 0, SEEK_END);
    }

    return return_value;
}


/**
 * @brief this function prints the version of the shell
 */

int sver(int argc, char **argv)
{
	printf("Ultrashell v. 1.2.0 (debug)\n");

	return 0;
}


/**
 * @brief this function always returns true
 */
int cmdtrue(int argc, char **argv)
{
	return 0;
}


/**
 * @brief this function always returns false
 */

int cmdfalse(int argc, char **argv)
{
	return 1;
}


/**
 * @brief changes the working directory
 */

int cd(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("cd: incorrect number of arguments\n");
		return 1;
	}
	
	int ret = chdir(argv[1]);

	if(ret == -1)
	{
		printf("cd: %s: unable to find file or directory\n", argv[1]);
		return 2;
	}
	else if(ret == -2)
	{
		printf("cd: %s: no permission to access directory\n", argv[1]);
		return 3;
	}

	return 0;
}


/**
 * @brief prints the current working directory
 */

int pwd(int argc, char **argv)
{
	if(argc != 1)
	{
		printf("pwd: incorrect number of arguments\n");
		return 1;
	}

	char wd[80];

	if(getcwd(wd, 80) == NULL)
	{
		printf("pwd: some error has occured during calling getcwd\n");
		return 2;
	}

	printf("%s\n", wd);

	return 0;	
}


/**
 * @brief exits the shell
 */

int sexit(int argc, char **argv)
{
	printf("Exiting Ultrashell.\n");

	exit(0);

	return 0;
}

