
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/socket.h>	// For socket()
#include	<netinet/in.h>	// For sockaddr_in and htons()
#include	<netdb.h>	// For getaddrinfo()
#include	<errno.h>	// For errno var
#include	<sys/stat.h>	// For open(), read(),write(), stat()
#include	<fcntl.h>	// and close()


/*---		Definition of constants:                                    ---*/

#define		BUFFER_LEN		256
#define		NO_MATCH_CODE		((uint32_t) -1)
#define		CANT_READ_FILE_CODE	((uint32_t) -2)
#define		CANT_READ_DIR_CODE	((uint32_t) -3)
#define		DEFAULT_HOSTNAME	"localhost.localdomain"

