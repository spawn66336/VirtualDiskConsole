#ifndef ZP_RMDIRCMD
#define ZP_RMDIRCMD 

#include "ConsoleCommand.h"

namespace CommandSys
{
	 
class RmdirCmd : public ConsoleCommand
{
public:
	RmdirCmd(void);
	virtual ~RmdirCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif// ZP_RMDIRCMD