# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>

# define PORT 9876

class VGCServer
{
	private: 
		//int server_fd, new_socket;
		//ssize_t valread;

		int server_fd; 
		struct sockaddr_in address;
		int opt = 1;
		socklen_t addrlen = sizeof(address);
		char buffer[1024] = {0};
		char* hello = "Hello from server";

	public:
		VGCServer()
		{
			createSocketFD();
			setSocketOptions();
			bindSocketToAddrPort();
			//listenToSocketFD();
			//acceptConnectionRequest();

		}

		~VGCServer()
		{
			close(server_fd);
		}

		void createSocketFD()
		{
			int i = 
			(server_fd = socket(AF_INET, SOCK_STREAM, 0));

			// In case of failure
			if(i < 0)
			{
				perror("socket failed");
				exit(EXIT_FAILURE);
			}
		}

		void setSocketOptions()
		{
			int i = 
			setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
			// Setting socket options

			// In case of failure
			if(i < 0)
			{
				perror("setsockopt");
				exit(EXIT_FAILURE);
			}
		}

		void bindSocketToAddrPort()
		{
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(PORT);

			int i = 
			bind(server_fd, (struct sockaddr*)&address, sizeof(address));
			// bind a unique local name to the socket with descriptor socket

			// In case of failure
			if(i < 0)
			{
				perror("bind failed");
				exit(EXIT_FAILURE);
			}
		}

		void listenToSocketFD()
		{
			int i = 
			listen(server_fd, 3);
			// prepare the server for incomming client requests

			// In case of failure
			if(i < 0)
			{
				perror("listen failed");
				exit(EXIT_FAILURE);
			}

			std::cout << "listenToSocketFD()" << std::endl;
		}

		int acceptConnectionRequest()
		{
			std::cout << "acceptConnectionRequest() Entered..." << std::endl;

			int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
			int i = new_socket;

			// In case of failure
			if(i < 0)
			{
				perror("accept failed");
				exit(EXIT_FAILURE);
			}

			std::cout << "acceptConnectionRequest new_socket = " << new_socket << std::endl;
			return(new_socket);
		}

		char* readSocket(int new_socket)
		{
			ssize_t valread = read(new_socket, buffer, 1024-1); 
			// subtract 1 for the null terminator at the end

			//std::cout<< buffer << std::endl;
			return(buffer);
		}

		void sendMsg(int new_socket)
		{
			send(new_socket, hello, strlen(hello), 0);
		}

};

int main()
{
	std::cout << "Om Namah Shivay!!!" << std::endl;

	VGCServer vserver;

	int new_socket;

	char* buffer;

while(1)
{ 
	vserver.listenToSocketFD();
	new_socket = vserver.acceptConnectionRequest();

	buffer = 
	vserver.readSocket(new_socket);
	std::cout<< buffer << std::endl;

	std::cout << strcmp(buffer, "Jai Maa MahaKaali!!!") << std::endl;
	if(strcmp(buffer, "Jai Maa MahaKaali!!!") == 0)
	{ break; }


	vserver.sendMsg(new_socket);
}
	


	close(new_socket);


	return(0);
}
