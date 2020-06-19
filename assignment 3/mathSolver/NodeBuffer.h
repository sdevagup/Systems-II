/*-------------------------------------------------------------------------*
 *---									---*
 *---		NodeBuffer.h						---*
 *---									---*
 *---	    This file defines a class that implements a thread-safe 	---*
 *---	buffer of pointers to math expressions.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2019 May 6		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/


class   NodeBuffer
{
  enum { SIZE   = 16 };

  Node*   array_[SIZE];
  int   inIndex_;
  int   outIndex_;
  int   numItems_;

public :

  NodeBuffer        ()
  {
    for  (int i = 0;  i < SIZE;  i++)
    {
      array_[i]	= NULL;
    }

    inIndex_ = outIndex_ = numItems_ = 0;
  }

  ~NodeBuffer       ()
  {
  }

  int   getNumItems  () const
  { return(numItems_); }

  void  putIn (Node* nodePtr)
  {
    while  (getNumItems() >= SIZE)
    {
    }

    array_[inIndex_] = nodePtr;

    inIndex_++;
    numItems_++;
    if  (inIndex_ >= SIZE)
      inIndex_ = 0;
  }

  Node*   pullOut ()
  {
    while  (getNumItems() <= 0)
    {
    }

    Node* toReturn        = array_[outIndex_];

    array_[outIndex_]	  = NULL;
    outIndex_++;
    numItems_--;
    if  (outIndex_ >= SIZE)
      outIndex_ = 0;

    return(toReturn);
  }
};
