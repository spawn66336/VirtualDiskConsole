#ifndef ZP_COMPARECMD
#define ZP_COMPARECMD

#include "ConsoleCommand.h"

namespace CommandSys
{ 

class CompareCmd : public ConsoleCommand 
{
public:
	CompareCmd(void);
	virtual ~CompareCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif// ZP_COMPARECMD