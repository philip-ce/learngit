#include "udcommon.h"

int
main (int argc, char *argv[])
{
	struct sockaddr_un addr;
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		printf("Socket create fail!\n");
	}
	
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	if(connect(sfd, (struct sockaddr* ) &addr, sizeof(struct sockaddr_un)) == -1 )
	{
		printf("Connect fail!\n");
	}
	
	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
		if (write(sfd, buf, numRead) != numRead)
		{
			printf("Write fail!\n");
		}
	}
	
	if(numRead == -1)
	{
		printf("Read fail!\n");
	}
	
	return 0;
}
