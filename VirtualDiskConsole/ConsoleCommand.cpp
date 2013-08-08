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
	m_curr_path = curr_path;
	m_curr_path_toks.Clear();
	LexerSys::AnalysisPath( curr_path , m_curr_path_toks );
} 

 
void ConsoleCommand::SetParamToks( const Util::LinkListT<LexerSys::Token>& params )
{
	m_params = params;
}

void ConsoleCommand::AddPath( const Util::LinkListT<LexerSys::Token>& path )
{
	m_paths.PushBack( path );
}

void ConsoleCommand::SetPaths( const Util::LinkListT<Util::LinkListT<LexerSys::Token>>& paths )
{
	m_paths = paths;
} 

Util::String ConsoleCommand::GetResultOutput( void )
{
	return m_result_output;
}

Util::String ConsoleCommand::GetCurrPath( void )
{
	return m_curr_path;
}

FileSys::Node* ConsoleCommand::SearchNodeByPathTokens( 
	const Util::LinkListT<LexerSys::Token>& path_toks   )
{
	const Util::LinkListT<LexerSys::Token>& curr_path_toks = m_curr_path_toks;
	Util::LinkListT<LexerSys::Token> curr_path_toks_copy = curr_path_toks;
	curr_path_toks_copy.PopFront();

	Util::LinkListT<LexerSys::Token> final_path_toks;
	//如果要找寻的路径不为绝对路径
	if( !LexerSys::IsAbsolutePath( path_toks ) )
	{
		final_path_toks = curr_path_toks_copy;
		final_path_toks.Append( path_toks );
	}else{
		final_path_toks = path_toks;
		final_path_toks.PopFront();
	}

	FileSys::PathSearchVisitor visitor;
	visitor.SetPathToks( final_path_toks ); 
	FileSys::FileSystem::GetInstance()->Accept( &visitor );
	return visitor.GetSearchNode();
}

FileSys::Node* ConsoleCommand::SearchCurrPathNode( void )
{
	return SearchNodeByPathTokens( m_curr_path_toks );
}

 


}// CommandSys