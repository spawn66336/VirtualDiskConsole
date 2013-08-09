#include "RmdirCmd.h"

namespace CommandSys
{

RmdirCmd::RmdirCmd(void)
{
}


RmdirCmd::~RmdirCmd(void)
{
}

void CommandSys::RmdirCmd::Execute( void )
{
	bool recursive = false;

	//分析参数
	if( m_params.Count() )
	{
		for( int i = 0 ; i < m_params.Count() ; i++ )
		{
			LexerSys::Token param_tok = m_params.At( i );

			 if( 0 == param_tok.Name().ICmp("s") ){
				recursive = true;
			}else{//非法选项
				m_result_output = Util::StringFormat("参数格式不正确-\"%s\"" , param_tok.Name().Ptr() );
				return;
			} 
		}//for( int i = 0 ; i < m_params.Count() ; i++ )
	}//if( m_params.Count() )

	//分析路径名
	if( m_paths.Count() )
	{
		for( int i = 0 ; i < m_paths.Count() ; i++ )
		{
			FileSys::Node*  lp_search_path_node = SearchNodeByPath( m_paths.At( i ) );
			if( NULL != lp_search_path_node )
			{ 
				if( lp_search_path_node->IsFile() || lp_search_path_node->Parent()->IsRoot() )
				{
					m_result_output = "目录名无效";
					return;
				}

				if( lp_search_path_node->IsLeaf() || recursive ){

					FileSys::Node* lp_curr_path_node =	SearchCurrPathNode(); 
					//待删除的节点不可为当前路径节点祖先
					if( lp_search_path_node != lp_curr_path_node 
						&& !lp_curr_path_node->IsAncestor( lp_search_path_node )  )
					{
						lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
					}else{
						m_result_output = "有子文件夹正在被使用,无法删除该目录!";
						return;
					} 
				}else{
					m_result_output = "目录不是空的";
					return;
				} 
			}else{//若有一个非法路径则直接退出
				m_result_output = "系统找不到指定的路径";
				return;
			}
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	} 

}

}//namespace CommandSys