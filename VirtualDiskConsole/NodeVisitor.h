#ifndef ZP_NODEVISITOR
#define ZP_NODEVISITOR

#include "ZPDependency.h"

namespace FileSys
{
	class Node;

	class NodeVisitor
	{
	public:
		NodeVisitor(void);
		virtual ~NodeVisitor(void);

		virtual void Visit( Node* node ){ };
	};

}//namespace FileSys

#endif //ZP_NODEVISITOR