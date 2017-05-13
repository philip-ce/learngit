#include "udcommon.h"

#define BACKLOG 5

int 
main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int sfd, cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == sfd)
	{
		printf("Sockt create fail!\n");
	}
	
	if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)  // ENOENT no such file or directory
	{
		printf("Remove-%s-success!\n", SV_SOCK_PATH);
	}
	
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	if ( bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un) ) == -1)
	{
		printf("Bind fail!\n");
	}
	
	if (listen(sfd, BACKLOG) == -1)
	{
		printf("Listen fail!\n");
	}
	
	for(;;)
	{
		cfd = accept(sfd, NULL, NULL);
		if (cfd == -1)
		{
			printf("Accept fail!\n");
		}
		
		while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
		{
			if (write(STDOUT_FILENO, buf, numRead) != numRead)
			{
				printf("Write fail!\n");
			}
		}
		
		if (numRead == -1)
		{
			printf("Read fail!\n");
		}
		if (close(cfd) == -1)
		{
			printf("Close fail\n!");
		}
	}
	
	
}
