#ifndef ZP_CONSOLECOMMANDFACTORY
#define ZP_CONSOLECOMMANDFACTORY
#include "ZPDependency.h"

namespace CommandSys
{ 
	class ConsoleCommand;

	class ConsoleCommandFactory : public Util::SingletonT<ConsoleCommandFactory>
	{
	public:
		ConsoleCommandFactory( void );
		virtual ~ConsoleCommandFactory( void );

		ConsoleCommand* CreateCommand( const Util::String& curr_path , const Util::String& cmd );
	};

}//namespace CommandSys

#endif //ZP_CONSOLECOMMANDFACTORY 