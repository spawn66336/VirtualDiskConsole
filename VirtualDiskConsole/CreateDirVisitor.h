#ifndef ZP_CREATEDIRVISITOR
#define ZP_CREATEDIRVISITOR

#include "NodeVisitor.h"

namespace FileSys
{
	 
	class CreateDirVisitor : public NodeVisitor
	{
	public:
		CreateDirVisitor(void);
		virtual ~CreateDirVisitor(void);

		virtual void Visit( Node* node );
	};

}//namespace FileSys

#endif //ZP_CREATEDIRVISITOR