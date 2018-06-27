#include "AnybotsEngine.h"

using namespace std;
using namespace ORUtils;
using namespace InputSource;
using namespace sensor_msgs;
using namespace message_filters;

void AnybotsEngine::initConnection(char* ip, int port)
{
	std::lock_guard<std::mutex> process_message_lock(images_mutex_);
	//set maximum message size
	const int MSG_SIZE = 100;

	//file descriptor
	int connfd = -1;

	//buffer to store message
	char data[MSG_SIZE];

	//bytes read
	int numRead = -1;

	//server address
	sockaddr_in serverAddr;

	//size of address client
	socklen_t servLen = sizeof(serverAddr);

	//connect to the server
	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	// set the structure to all zeros
	memset(&serverAddr, 0, sizeof(serverAddr));

	// set the server family
	serverAddr.sin_family = AF_INET;

	// convert the port number to network representation
	serverAddr.sin_port = htons(port);

	//  convert the IP from the presentation format (i.e. string)
	//  to the format in the serverAddr structure.
	if(!inet_pton(AF_INET, ip, &serverAddr.sin_addr))
	{
		perror("inet_pton");
		exit(1);
	}

	// connect to the server. This call will return a socket used
	// used for communications between the server and the client.
	if(connect(connfd, (sockaddr*)&serverAddr, sizeof(sockaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}
}