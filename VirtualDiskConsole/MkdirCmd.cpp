#include "MkdirCmd.h"
#include "Lexer.h"
#include "CreateDirVisitor.h"
#include "FileSystem.h"

namespace CommandSys
{


MkdirCmd::MkdirCmd(void)
{
}


MkdirCmd::~MkdirCmd(void)
{
}

void CommandSys::MkdirCmd::Execute( void )
{
	
	if( m_params.Count() )
	{
		m_result_output = "此命令不支持参数";
		return;
	}

	for( int i = 0 ; i < m_paths.Count() ; i++ )
	{ 
			Util::LinkListT<LexerSys::Token> path_toks = m_paths.At(i);
			Util::LinkListT<LexerSys::Token> final_path_toks;

			//如果要找寻的路径不为绝对路径
			if( !LexerSys::IsAbsolutePath( path_toks ) )
			{
				final_path_toks = m_curr_path_toks;
				final_path_toks.Append( path_toks );
				final_path_toks.PopFront();
			}else{

				if( 0 == path_toks.At(0).Name().ICmp( "c:" ) )
				{
					final_path_toks = path_toks;
					final_path_toks.PopFront();
				}else{
					m_result_output = "系统找不到指定的路径";
					return;
				} 
			}

			FileSys::CreateDirVisitor visitor;
			visitor.SetPathToks( final_path_toks );
			FileSys::FileSystem::GetInstance()->Accept( &visitor ); 
			
	}//for( int i = 0 ; i < m_paths.Count() ; i++ )
}

}//namespace CommandSys