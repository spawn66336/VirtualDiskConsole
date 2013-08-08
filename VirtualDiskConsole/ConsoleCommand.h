#ifndef ZP_CONSOLECOMMAND
#define ZP_CONSOLECOMMAND
#include "ZPDependency.h"
#include "Token.h"
#include "Node.h"

namespace CommandSys
{

class ConsoleCommand
{
public:
	ConsoleCommand(void);
	virtual ~ConsoleCommand(void);

	void SetCurrPath( const Util::String& curr_path ); 

	void SetParamToks( const Util::LinkListT<LexerSys::Token>& params );

	void AddPath( const Util::LinkListT<LexerSys::Token>& path );

	void SetPaths( const Util::LinkListT<Util::LinkListT<LexerSys::Token>>& paths );

	virtual void Execute( void ){} 

	Util::String GetResultOutput( void );

	Util::String GetCurrPath(void);

	virtual void DeleteThis(void){ delete this; }

protected:

	FileSys::Node* SearchCurrPathNode(void);

	FileSys::Node* SearchNodeByPathTokens( 
		const Util::LinkListT<LexerSys::Token>& path_toks );

protected: 
	Util::String	m_curr_path;													///>当前路径
	Util::LinkListT<LexerSys::Token> m_curr_path_toks;				///>当前路径符号列表
	Util::LinkListT<LexerSys::Token> m_params;							///>参数列表
	Util::LinkListT<Util::LinkListT<LexerSys::Token>> m_paths;	///>路径列表
	Util::String m_result_output;													///>输出结果字符串
};

}//namespace CommandSys

#endif//ZP_CONSOLECOMMAND