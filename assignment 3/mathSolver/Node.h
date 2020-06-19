/*-------------------------------------------------------------------------*
 *---									---*
 *---		Node.h							---*
 *---									---*
 *---	    This file defines classes for nodes used to represent math 	---*
 *---	expressions.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2019 May 6		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/


//  PURPOSE:  To distinguish among the mathematical operators.
typedef		enum		{
				  ADD_OP,
				  SUBTRACT_OP,
				  MULTIPLY_OP,
				  DIVIDE_OP,

				  NUM_OPS
				}
				operator_ty;


//  PURPOSE:  To serve as the base class for the Node classes.
class		Node
{

public :

  Node				()
				{ }

  virtual
  ~Node				()
				{ }

  virtual
  double	eval		()
				const
				= 0;

  virtual
  std::string	toString	()
  				const
				= 0;
};


//  PURPOSE:  To represent a constant.
class		ConstNode : public Node
{
  double			constant_;

public :

  ConstNode			() :
  				Node(),
				constant_((double)((rand() % MAX_VALUE) + 1) )
				{ }

  double	eval		()
  				const
				{ return(constant_); }

  std::string	toString	()
  				const
				{
				  std::ostringstream	stream;

				  stream << constant_;
				  return(stream.str());
				}

};


//  PURPOSE:  To return a randomly generated Node.
extern
Node*		makeNode	();


//  PURPOSE:  To represent an operation.
class		OperatorNode : public Node
{
  operator_ty			operator_;
  Node*				lhsPtr_;
  Node*				rhsPtr_;

public :

  OperatorNode			() :
				Node(),
				operator_((operator_ty)(rand() % NUM_OPS)),
				lhsPtr_(makeNode()),
				rhsPtr_(makeNode())
				{ }

  ~OperatorNode			()
				{
				  delete(rhsPtr_);
				  delete(lhsPtr_);
				}

  double	eval		()
				const
				{
				  double	lhs	= lhsPtr_->eval();
				  double	rhs	= rhsPtr_->eval();
				  double	result;

				  switch  (operator_)
				  {
				  case ADD_OP :
				  default :  
				    result	= lhs + rhs;
				    break;

				  case SUBTRACT_OP :
				    result	= lhs - rhs;
				    break;

				  case MULTIPLY_OP :
				    result	= lhs * rhs;
				    break;

				  case DIVIDE_OP :
				    result	= lhs / rhs;
				    break;
				  }

				  return(result);
				}

  std::string	toString	()
  				const
				{
				  std::ostringstream	stream;
				  const char*		operatorNameCPtr;

				  switch  (operator_)
				  {
				  case ADD_OP :
				  default :  
				    operatorNameCPtr	= " + ";
				    break;

				  case SUBTRACT_OP :
				    operatorNameCPtr	= " - ";
				    break;

				  case MULTIPLY_OP :
				    operatorNameCPtr	= " * ";
				    break;

				  case DIVIDE_OP :
				    operatorNameCPtr	= " / ";
				    break;
				  }

				  stream << "(" << lhsPtr_->toString() 
				  	 << operatorNameCPtr
					 << rhsPtr_->toString() << ")";

				  return(stream.str());
				}

};
