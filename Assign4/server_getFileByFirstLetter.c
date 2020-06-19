
#include	"getFileByFirstLetter.h"
#include	<signal.h>		// For sigaction()
#include	<wait.h>		// For waitpid()
#include	<dirent.h>		// For opendir(), readdir(), closedir()
#define         LINE_LEN          256
const int	LO_LEGAL_PORT	= 1025;
const int	HI_LEGAL_PORT	= 65535;
const int	ERROR_FD	= -1;
const int	NUM_CLIENTS_TO_SERVE
				= 4;

void		sigChildHandler	(int	sig
				)
{
  //  I.  Application validity check:

  int status;
  pid_t childId;

  while ( (childId = waitpid(-1,&status,WNOHANG)) > 0)
    {
     // printf("Child %d finished.\n",childId);
    printf ("\n");
    }

  //  III.  Finished:
}


//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//	to the OS telling this server when a client process has connect()-ed
//	to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor
				(int		port,
				 const char*	progName
				)
{
  //  I.  Application validity check:
  if  (progName == NULL)
  {
    fprintf(stderr,"BUG: NULL ptr to getServerFileDescriptor().\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  YOUR CODE HERE
  // Create a socket

  // Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
				SOCK_STREAM, // Reliable TCP
				0);

  // We'll fill in this datastruct
  struct sockaddr_in socketInfo;
  // Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));

  // Use std TCP/IP
  socketInfo.sin_family = AF_INET;

  // Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  // Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;

  // Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		    );

  if  (status < 0)
    {
      fprintf(stderr,"Could not bind to port %d\n",port);
      exit(EXIT_FAILURE);
      

    }

  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor /* <-- CHANGE THAT */);
}


//  PURPOSE:  To install 'sigChildHandler()' as the signal simple handler for
//	the 'SIGCHLD' signal.  Tells OS to restarts system calls if receives
//	'SIGCHLD'.
void	installSigChildHandler	()
{
  //  I.  Application validity check:

  //  II.  Install 'sigChildHandler()' as the 'SIGCHLD' handler:
  //  YOUR CODE HERE
  struct sigaction act;
  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NOCLDSTOP | SA_RESTART;;
  act.sa_handler = sigChildHandler;
  // Handle with simpleHandler()
  sigaction(SIGCHLD,&act,NULL);
  //  III.  Finished:
}


//  PURPOSE:  To ask the user which port to attempt to monopolize, and to return
//	entered port number.
int		getPort		()
{
  //  I.  Application validity check:

  //  II.  Get port number
  int	port;

  do
  {
    char	buffer[BUFFER_LEN];

    printf("Please enter port number to monopolize [%d-%d]: ",
	   LO_LEGAL_PORT,HI_LEGAL_PORT
	  );
    fgets(buffer,BUFFER_LEN,stdin);
    port = strtol(buffer,NULL,10);
  }
  while  ( (port < LO_LEGAL_PORT)  ||  (port > HI_LEGAL_PORT) );

  //  III.  Finished:
  return(port);
}



//  PURPOSE:  To do the work of handling the client.  Communication with the
//	client take place using file-descriptor 'fd'.  No return value.
void		handleClient	(int	fd
				)
{
  //  I.  Application validity check:
  if  (fd < 0)
  {
    fprintf(stderr,"BUG: Illegal file descriptor to handleClient()\n");
    exit(EXIT_FAILURE);
  }

    
    
    
   
    char	letter[1];
    read(fd,&letter,1);
   
 
    
    
    
    const char*	dirName	= (".");
    DIR*		dirPtr	= opendir(dirName);
    struct dirent*	entryPtr;
    
    uint32_t  fileSize;
    
    if (dirPtr == NULL) {
        printf ("Cannot open directory\n");
        fileSize = htonl(CANT_READ_DIR_CODE);
        write(fd,&fileSize,sizeof(fileSize));
        exit(CANT_READ_DIR_CODE);
    }
    
    //////////////////////////////////////////////////////////////
    
    struct stat		statBuffer;
    int filestat = 0;
    int fdesc = -1;
    
    while ((entryPtr = readdir(dirPtr)) != NULL) {
       
        
        if(entryPtr->d_name[0] == letter[0]){
           
            fdesc = open(entryPtr->d_name,O_RDONLY);
            stat(entryPtr,&statBuffer);
            
            if(fdesc < 0){
                printf("The Server canot open YouCantOpenMe.txt\n");
                printf("Cannot read file %s.\n",entryPtr->d_name);
                fileSize = htonl(CANT_READ_FILE_CODE);
                write(fd,&fileSize,sizeof(fileSize));
                exit(CANT_READ_FILE_CODE);
            }
            filestat = 1;
            break;
        }
    }
    
    
    
    while  ( (entryPtr = readdir(dirPtr)) != NULL )
    {
        char	filePath[256];
   
        stat(filePath,&statBuffer);
       
        if  ( entryPtr->d_name[0] == letter[0] && S_ISDIR(statBuffer.st_mode)) {
            printf("\n No Matching File\n");
            fileSize = htonl(CANT_READ_FILE_CODE);
            write(fd,&fileSize,sizeof(fileSize));
            exit(CANT_READ_FILE_CODE);
        
        
    }

    
        
    
    
    
    
    if(filestat == 0){
        printf("No file Begins with X\n");
        printf("No matching file\n");
        fileSize = htonl(NO_MATCH_CODE);
        write(fd,&fileSize,sizeof(fileSize));
        exit(NO_MATCH_CODE);
    }else{
        
        
        
        
        
        
        
        
        
        off_t fsize;
        fsize = lseek(fdesc, 0, SEEK_END);
        fileSize = htonl(fsize); //Default Case
        write(fd,&fileSize,sizeof(fileSize));
        char	buffer[BUFFER_LEN];
        
        unsigned int	totalNumBytesRead	= 0;
        int numBytesRead;
        
        fsize = lseek(fdesc, 0, SEEK_SET);
        while  ( (totalNumBytesRead < fileSize)			&&
                ( (numBytesRead = read(fdesc,buffer,BUFFER_LEN)) > 0)
                )
        {
            buffer[numBytesRead]	 = '\0';
            
            totalNumBytesRead	+= (unsigned int)numBytesRead;
            printf("%s",buffer);
            write(fd,buffer,numBytesRead);
            
          
          
            
            
        }
            printf("Dir begins with D,but it is not a file.\n",entryPtr->d_name, totalNumBytesRead);
            printf("No matching file");
       
    }
    
        
        
        
        
              closedir (dirPtr);
    
    
    
  //  III.  Finished:
}


//  PURPOSE:  To serve the clients using file-descriptor 'listenFd' to tell
//	when a client has connected.  Each client is handled by its own child
//	process.  Both the parent and the child processes close unnecesary
//	file-descriptorors.  Serves 'NUM_CLIENTS_TO_SERVE' clients, then quits.
//	No return value.
void	       	doServer  	(int  	 	listenFd
				)
{
  //  I.  Application validity check:
  if  (listenFd < 0)
  {
    fprintf(stderr,"Illegal file-descriptor to doServer()\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Do the work of the server:
  int	i;

  for  (i = 0;  i < NUM_CLIENTS_TO_SERVE;  i++)
  {
    // Accept connection to client
    int clientDescriptor = accept(listenFd,NULL,NULL);

  if  (fork() == 0)
    {
      close(listenFd);
      handleClient(clientDescriptor);
      exit(EXIT_SUCCESS);
    }

    close(clientDescriptor);

  }

  //  III.  Finished:
}


//  PURPOSE:  To oversee the main work of the server.  Ignores 'argc' but
//	uses 'argv[0]' as the name of the program.  Returns 'EXIT_SUCCESS' to
//	OS on success or 'EXIT_FAILURE' otherwise.
int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int	port		= getPort();
  int	socketFd	= getServerFileDescriptor(port,argv[0]);

  installSigChildHandler();
  doServer(socketFd);

  //  III.  Finished:
  return(EXIT_SUCCESS);
}
  
