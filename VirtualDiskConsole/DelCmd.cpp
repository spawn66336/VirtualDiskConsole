#include "DelCmd.h"

namespace CommandSys
{
	 
DelCmd::DelCmd(void)
{
}


DelCmd::~DelCmd(void)
{
}

void DelCmd::Execute( void )
{
	if( m_params.Count() )
	{
		m_result_output = "本命令不支持参数";
		return;
	}

	if( m_paths.Count() == 0 )
	{
		m_result_output = "命令语法不正确";
		return;
	}
	
	//分析路径名
	if( m_paths.Count() )
	{
		for( int i = 0 ; i < m_paths.Count() ; i++ )
		{ 
			FileSys::Node*  lp_search_path_node = SearchNodeByPathTokens( m_paths.At( i ) );
			if( NULL != lp_search_path_node )
			{  
				if( lp_search_path_node->IsFile() ){ 
					lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
				}else{//若为文件夹则删除文件夹下所有文件
					lp_search_path_node->DeleteNodeByType( FileSys::Node::FILE_NODE );					 
					return;
				} 
			}else{//若有一个非法路径则直接退出
				m_result_output = "系统找不到指定的路径";
				return;
			} 
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	}//if( m_paths.Count() )
}

}//namespace CommandSys