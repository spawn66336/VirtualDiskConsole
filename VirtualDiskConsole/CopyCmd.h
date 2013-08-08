#ifndef ZP_COPYCMD
#define ZP_COPYCMD

#include "ConsoleCommand.h"

namespace CommandSys
{ 

class CopyCmd : public ConsoleCommand
{
public:
	CopyCmd(void);
	virtual ~CopyCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif// ZP_COPYCMD