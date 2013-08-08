#ifndef ZP_PATHSEARCHVISITOR
#define ZP_PATHSEARCHVISITOR

#include "ZPDependency.h"
#include "NodeVisitor.h"


namespace FileSys
{ 
	class PathSearchVisitor : public NodeVisitor
	{
	public:
		PathSearchVisitor(void);
		virtual ~PathSearchVisitor(void);  

		virtual void Visit( Node* node );  
	}; 
}//namespace FileSys

#endif// ZP_PATHSEARCHVISITOR