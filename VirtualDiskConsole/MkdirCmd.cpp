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

	if( 0 == m_paths.Count() )
	{
		m_result_output = "命令语法不正确";
		return;
	}

	for( int i = 0 ; i < m_paths.Count() ; i++ )
	{ 
			LexerSys::SearchPath path = m_paths.At(i);
			LexerSys::SearchPath final_path;

			//如果要找寻的路径不为绝对路径
			if( !path.IsAbsolutePath() )
			{
				final_path = m_curr_path;
				final_path.Append( path ); 
			}else{

				if( 0 == path.At(0).Name().ICmp( "c:" ) )
				{
					final_path = path; 
				}else{
					m_result_output = "系统找不到指定的路径";
					return;
				} 
			}

			FileSys::CreateDirVisitor visitor;
			visitor.SetPath( final_path );
			FileSys::FileSystem::GetInstance()->Accept( &visitor ); 
			
	}//for( int i = 0 ; i < m_paths.Count() ; i++ )
}

}//namespace CommandSys