#ifndef ZP_MKDIRCMD
#define ZP_MKDIRCMD
 
#include "ConsoleCommand.h"

namespace CommandSys
{
	 
class MkdirCmd : public ConsoleCommand
{
public:
	MkdirCmd(void);
	virtual ~MkdirCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys
#endif //ZP_MKDIRCMD