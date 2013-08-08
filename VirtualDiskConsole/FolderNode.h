#ifndef ZP_FOLDERNODE
#define ZP_FOLDERNODE

#include "Node.h"

namespace FileSys
{
	 
class FolderNode : public Node
{
public:
	FolderNode(void);
	virtual ~FolderNode(void);

	bool IsFolder( void ) const { return true; }
};

}//FileSys

#endif//ZP_FOLDERNODE