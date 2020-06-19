

#include	"getFileByFirstLetter.h"
#include	<ctype.h>	// isalpha()



//  PURPOSE:  To ask the user for the name and the port of the server.  The
//	server name is returned in 'url' up to length 'urlLen'.  The port
//	number is returned in '*portPtr'.  No return value.
void	obtainUrlAndPort	(int		urlLen,
                             char*		url,
                             int*		portPtr
                             )
{
    //  I.  Application validity check:
    if  ( (url == NULL)  ||  (portPtr == NULL) )
    {
        fprintf(stderr,"BUG: NULL ptr to obtainUrlAndPort()\n");
        exit(EXIT_FAILURE);
    }
    
    if   (urlLen <= 1)
    {
        fprintf(stderr,"BUG: Bad string length to obtainUrlAndPort()\n");
        exit(EXIT_FAILURE);
    }
    
    //  II.  Get server name and port number:
    //  II.A.  Get server name:
    printf("Machine name [%s]? ",DEFAULT_HOSTNAME);
    fgets(url,urlLen,stdin);
    
    char*	cPtr	= strchr(url,'\n');
    
    if  (cPtr != NULL)
        *cPtr = '\0';
    
    if  (url[0] == '\0')
        strncpy(url,DEFAULT_HOSTNAME,urlLen);
    
    //  II.B.  Get port numbe:
    char	buffer[BUFFER_LEN];
    
    printf("Port number? ");
    fgets(buffer,BUFFER_LEN,stdin);
    
    *portPtr = strtol(buffer,NULL,10);
    
    //  III.  Finished:
}


//  PURPOSE:  To attempt to connect to the server named 'url' at port 'port'.
//	Returns file-descriptor of socket if successful, or '-1' otherwise.
int	attemptToConnectToServer	(const char*	url,
                                 int		port
                                 )
{
    //  I.  Application validity check:
    if  (url == NULL)
    {
        fprintf(stderr,"BUG: NULL ptr to attemptToConnectToServer()\n");
        exit(EXIT_FAILURE);
    }
    
    
    //  II.  Attempt to connect to server:
    //  II.A.  Create a socket:
    int socketDescriptor = socket(AF_INET, // AF_INET domain
                                  SOCK_STREAM, // Reliable TCP
                                  0);
    
    //  II.B.  Ask DNS about 'url':
    struct addrinfo* hostPtr;
    int status = getaddrinfo(url,NULL,NULL,&hostPtr);
    
    if (status != 0)
    {
        fprintf(stderr,gai_strerror(status));
        return(-1);
    }
    
    //  II.C.  Attempt to connect to server:
    struct sockaddr_in server;
    // Clear server datastruct
    memset(&server, 0, sizeof(server));
    
    // Use TCP/IP
    server.sin_family = AF_INET;
    
    // Tell port # in proper network byte order
    server.sin_port = htons(port);
    
    // Copy connectivity info from info on server ("hostPtr")
    server.sin_addr.s_addr =
    ((struct sockaddr_in*)hostPtr->ai_addr)->sin_addr.s_addr;
    
    status = connect(socketDescriptor,(struct sockaddr*)&server,sizeof(server));
    
    if  (status < 0)
    {
        fprintf(stderr,"Could not connect %s:%d\n",url,port);
        return(-1);
    }
    
    //  III.  Finished:
    return(socketDescriptor);
}


//  PURPOSE:  To do the work of the application.  Gets letter from user, sends
//	it to server over file-descriptor 'fd', and either prints text of
//	returned error code, or prints returned file.  No return value.
void	communicateWithServer	(int	fd
                                 )
{
    //  I.  Application validity check:
    
    //  II.  Do work of application:
    //  II.A.  Get letter from user:
    char	buffer[BUFFER_LEN+1];
    
    do
    {
        printf("Please enter a letter to look for: ");
        fgets(buffer,BUFFER_LEN,stdin);
    }
    while  ( !isalpha(buffer[0]) );
    
    //  II.B.  Send letter to server:
    write(fd,buffer,1);
    
    //  II.C.  Get response from server:
    uint32_t	fileSize;
    
    read(fd,&fileSize,sizeof(fileSize));
    fileSize = ntohl(fileSize);
    
    //  II.D.  Interpret server response:
    switch  (fileSize)
    {
        case NO_MATCH_CODE :
            printf("No matching file found for %c\n",buffer[0]);
            break;
            
        case CANT_READ_FILE_CODE :
            printf("Matching file found for %c, but could not open\n",buffer[0]);
            break;
            
        case CANT_READ_DIR_CODE :
            printf("Server could not open .\n",buffer[0]);
            break;
            
        default :
        {
            unsigned int	totalNumBytesRead	= 0;
            int		numBytesRead;
            
            printf("The file that matches %c has size %u\n",buffer[0],fileSize);
            
            while  ( (totalNumBytesRead < fileSize)			&&
                    ( (numBytesRead = read(fd,buffer,BUFFER_LEN)) > 0)
                    )
            {
                buffer[numBytesRead]	 = '\0';
                printf("%s",buffer);
                totalNumBytesRead	+= (unsigned int)numBytesRead;
            }
        }
    }
    
    //  III.  Finished:
}


//  PURPOSE:  To do the work of the client.  Ignores command line parameters.
//	Returns 'EXIT_SUCCESS' to OS on success or 'EXIT_FAILURE' otherwise.
int	main	()
{
    char		url[BUFFER_LEN];
    int		port;
    int		fd;
    
    obtainUrlAndPort(BUFFER_LEN,url,&port);
    fd	= attemptToConnectToServer(url,port);
    
    if  (fd < 0)
        exit(EXIT_FAILURE);
    
    communicateWithServer(fd);
    close(fd);
    return(EXIT_SUCCESS);
}