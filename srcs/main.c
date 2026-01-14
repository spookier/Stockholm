#include "../incs/Encrypt.h"
#include "../incs/Decrypt.h"

#define VERSION "1.0"

int check_args(int argc, char **argv)
{
	if (argc >= 2)
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		{
			printf("Use --version or -v to show the version of the program.\n");
			printf("Use -reverse or -r followed by key to reverse encryption.\n");
			printf("Use --silent or -s to not produce any output.\n");

			return (0);
		}
		else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
		{
			printf("Version is %s\n", VERSION);
			return(0);
		}
		else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--reverse") == 0)
		{
			// -- reverse
		}
		else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--silent") == 0)
		{
			// --silent
		}
		else
		{
			printf("Invalid number of arguments.\nPlease run --help for more info.");
			return(-1);
		}
	}
	return(0);
}

int main(int argc, char **argv)
{
	
	if (check_args(argc, argv) == -1)
		return(-1);

	if (sodium_init() < 0)
	{
		printf("Failed to init libsodium\n");
		return (-1);
	}

	// char *pwdpath;
	//
	// pwdpath = getcwd(NULL, 0);
	// if (pwdpath == NULL)
	// {
	//     return(-1);
	// }
	//
	// printf("%s\n", pwdpath);
	// if (strcmp(pwdpath, "/home/") != 0)
	// {
	//     printf("[X] Run in /home/\n");
	//     return (-1);
	// }
	//
	
   
	char key[] = "alex";
	
	// 2. Your encryption key (32 bytes)
	unsigned char hashed_key[crypto_secretbox_KEYBYTES];

	crypto_generichash(hashed_key, sizeof(hashed_key), (unsigned char *)key, strlen(key), NULL, 0);

	
	encrypt("test_file.txt", hashed_key, 0);
	sleep(1);
	decrypt_file("test_file.txt", hashed_key, 0);    

	// free(pwdpath);
}
