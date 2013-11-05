#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SERVER_PATH "/var/tmp/server_path"

int main(int argc, char const *argv[])
{
	int client_fd;
	int addr_len;
	int nwrite;

	struct sockaddr_un server_addr;

	char filename1[] = "iridium_msg1.txt";
	if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("create socket");
		return -1;
	}

	memset(&server_addr, 0, sizeof(struct sockaddr_un));
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, SERVER_PATH);
	addr_len = offsetof(struct sockaddr_un, sun_path) + strlen(server_addr.sun_path);

	if (connect(client_fd, (struct sockaddr*)&server_addr, addr_len) < 0) {
		perror("socket connect");
		return 1;
	}

	nwrite = write(client_fd, filename1, strlen(filename1));

	close(client_fd);
	return 0;
}
