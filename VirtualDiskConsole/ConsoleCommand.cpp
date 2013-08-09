#include "ConsoleCommand.h"
#include "Lexer.h"
#include "Node.h"
#include "PathSearchVisitor.h"
#include "FileSystem.h"

namespace CommandSys
{

ConsoleCommand::ConsoleCommand(void)
{ 
}


ConsoleCommand::~ConsoleCommand(void)
{ 
} 

void ConsoleCommand::SetCurrPath( const Util::String& curr_path )
{
	m_curr_path.Path( curr_path );
} 

 
void ConsoleCommand::SetParamToks( const Util::LinkListT<LexerSys::Token>& params )
{
	m_params = params;
}

void ConsoleCommand::AddPath( const LexerSys::SearchPath& path )
{
	m_paths.PushBack( path );
}

void ConsoleCommand::SetPaths( const Util::LinkListT<LexerSys::SearchPath>& paths )
{
	m_paths = paths;
} 

Util::String ConsoleCommand::GetResultOutput( void )
{
	return m_result_output;
}

Util::String ConsoleCommand::GetCurrPath( void )
{
	return m_curr_path.Path();
}

FileSys::Node* ConsoleCommand::SearchNodeByPath(  const LexerSys::SearchPath& path   )
{ 

	LexerSys::SearchPath final_path;
	//如果要找寻的路径不为绝对路径
	if( !path.IsAbsolutePath() )
	{
		final_path = m_curr_path;
		final_path.Append( path );
	}else{//若为绝对路径
		final_path = path; 
	}

	FileSys::PathSearchVisitor visitor;
	visitor.SetPath( final_path ); 
	FileSys::FileSystem::GetInstance()->Accept( &visitor );
	return visitor.GetSearchNode();
}

FileSys::Node* ConsoleCommand::SearchCurrPathNode( void )
{
	return SearchNodeByPath( m_curr_path );
}

 


}// CommandSys