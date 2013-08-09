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
			Util::String path = m_paths.At(i).Path();
			FileSys::Node*  lp_search_path_node = SearchNodeByPath( path );
			if( NULL != lp_search_path_node )
			{  
				if( lp_search_path_node->IsFile() ){ 
					lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
				}else{//若为文件夹则删除文件夹下所有文件
					lp_search_path_node->DeleteNodeByType( FileSys::Node::FILE_NODE );					 
					return;
				} 
			}else{//若找不到所指定文件 

				int last_back_slash_i = path.FindLastOf('\\');
				Util::String parent_path = path.SubString( 0 , 
					path.Length() - ( path.Length() - last_back_slash_i ) );
				
				Util::String filename = path.SubString( last_back_slash_i+1 , path.Length() - last_back_slash_i-1);

				 lp_search_path_node = SearchNodeByPath( parent_path );

				 if( NULL != lp_search_path_node )
				 {
						FileSys::Node* lp_del_node = NULL;
						while( NULL != 
							( lp_del_node = lp_search_path_node->FindFileNodeBySpec( filename ) ) )
						{
							lp_search_path_node->DeleteNode( lp_del_node->Name() );
						}

				 }else{
					 m_result_output = "系统找不到指定的路径";
					 return; 
				 }
			} 
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	}//if( m_paths.Count() )
}

}//namespace CommandSys