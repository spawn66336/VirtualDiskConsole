#ifndef ZP_DIRCMD
#define ZP_DIRCMD

#include "ConsoleCommand.h"

namespace CommandSys
{

class DirCmd : public ConsoleCommand
{
public:
	DirCmd(void);
	virtual ~DirCmd(void);

	virtual void Execute( void );

	virtual void DeleteThis(void){ delete this; }
};

}//namespace CommandSys

#endif //ZP_DIRCMD