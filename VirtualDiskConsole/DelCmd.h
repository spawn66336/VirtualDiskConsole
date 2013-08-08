#ifndef ZP_DELCMD
#define ZP_DELCMD

#include "ConsoleCommand.h"

namespace CommandSys
{ 

class DelCmd : public ConsoleCommand
{
public:
	DelCmd(void);
	virtual ~DelCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif// ZP_DELCMD