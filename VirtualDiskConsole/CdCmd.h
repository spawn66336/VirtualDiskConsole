#ifndef ZP_CDCMD
#define ZP_CDCMD

#include "ConsoleCommand.h"

namespace CommandSys
{
	 
class CdCmd : public ConsoleCommand
{ 
public:
	CdCmd(void);
	virtual ~CdCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif// ZP_CDCMD