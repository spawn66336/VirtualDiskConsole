#include "ConsoleCommandFactory.h"

#include "Lexer.h"
#include "CdCmd.h"
#include "DirCmd.h"
#include "CopyCmd.h"
#include "DelCmd.h"
#include "MkdirCmd.h"
#include "RmdirCmd.h"
#include "CompareCmd.h"

namespace CommandSys
{


ConsoleCommandFactory::ConsoleCommandFactory(void)
{
}


ConsoleCommandFactory::~ConsoleCommandFactory(void)
{
}

ConsoleCommand* CommandSys::ConsoleCommandFactory::CreateCommand( const Util::String& curr_path , const Util::String& cmd )
{
	ConsoleCommand* lp_new_cmd = NULL;

	LexerSys::Lexer lex;
	lex.SetString( cmd );
	lex.Analysis(); 

	LexerSys::Token tok = lex.GetCommandToken();

	if( tok.Name() == "cd" )
	{
		lp_new_cmd = new CdCmd;
	}else if( tok.Name() == "dir" ){
		lp_new_cmd = new DirCmd;
	}else if( tok.Name() == "mkdir"){
		lp_new_cmd = new MkdirCmd;
	}else if( tok.Name() == "rmdir" ){
		lp_new_cmd = new RmdirCmd;
	}else if( tok.Name() == "copy" ){
		lp_new_cmd = new CopyCmd;
	}else if( tok.Name() == "del" ){
		lp_new_cmd = new DelCmd;
	}else if( tok.Name() == "compare" ){
		lp_new_cmd = new CompareCmd;
	}
	 
	if( lp_new_cmd )
	{
		lp_new_cmd->SetCurrPath( curr_path );
		lp_new_cmd->SetParamToks( lex.GetCommandOptions() );
		lp_new_cmd->SetPaths( lex.GetCommandPaths() ); 
	} 
	lex.Clear();

	return lp_new_cmd;
}

}//namespace CommandSys