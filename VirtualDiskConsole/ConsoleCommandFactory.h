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

		/**
		* @brief 根据用户的命令输入字符串创建命令对象
		* @param curr_path 用户的当前路径
		* @param cmd 用户输入的命令字符串
		* @return 命令对象指针
		*/
		ConsoleCommand* CreateCommand( const Util::String& curr_path , const Util::String& cmd );
	};

}//namespace CommandSys

#endif //ZP_CONSOLECOMMANDFACTORY 