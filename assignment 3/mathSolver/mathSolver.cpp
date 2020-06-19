/*-------------------------------------------------------------------------*
 * 
 *---									---*
 *---		mathSolver.cpp						---*
 *---									---*
 *---	    This file defines the high-level functions of the math 	---*
 *---	generator and solver program.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2019 May 6		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//
//	Compile with:
//	$ g++ mathSolver.cpp -o mathSolver -lpthread -g
//


#include	"mathSolverHeader.h"


void*		evaluate	(void*		vPtr
				)
{
  NodeBuffer*	nodeBufferPtr	= (NodeBuffer*)vPtr; 
  
  Node* nodePtr;
  
  for(int i =0; i < NUM_PROBLEMS / 2; i++) //for each problems 
  { 
    nodePtr = nodeBufferPtr->pullOut();  //nodeBufferPtr -> pullOut() means *nodeBufferPtr.pullOut() 
    printf("%d %s = %f \n", i, nodePtr->toString().c_str(), nodePtr->eval()); 
    delete(nodePtr); 
  }

  return(NULL); 
  //  YOUR CODE HERE
}


//  PURPOSE:  To return a randomly generated Node.
Node*		makeNode	()
{
  return( (rand() % 3) ? (Node*)new ConstNode() : (Node*)new OperatorNode() );
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  NodeBuffer	nodeBuffer;
  pthread_t	consumer0;
  pthread_t	consumer1;
  int		toReturn	= EXIT_SUCCESS;
  
  // if argc < 2 then do getpid() else set atoi(argv[1])
  // (condition) ? {code for YES} : {code for NO} 
  srand( (argc < 2) ? getpid() : atoi(argv[1]) ); 
  
  //create 2 child thread  
  pthread_create(&consumer0,NULL,evaluate,&nodeBuffer);
  pthread_create(&consumer1,NULL,evaluate,&nodeBuffer); 
 
  for(int call = 0; call < NUM_PROBLEMS ; call++) //each problem 
  {
   nodeBuffer.putIn(makeNode()); //make node for each problem saving to array 
   printf("Made %d \n", call); 
  } 
  
  //wait for both child thread to finish 
  pthread_join(consumer0,NULL);
  pthread_join(consumer1,NULL); 
     
  //  YOUR CODE HERE

  return(toReturn);
}
