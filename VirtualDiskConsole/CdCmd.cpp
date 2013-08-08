#include "CdCmd.h"
#include "PathSearchVisitor.h"
#include "FileSystem.h"
#include "Node.h"
#include "Lexer.h"

namespace CommandSys
{ 

CdCmd::CdCmd(void)
{

}
 
CdCmd::~CdCmd(void)
{
}

void CdCmd::Execute( void )
{ 
	FileSys::Node* lp_curr_path_node =	SearchCurrPathNode();
	m_curr_path = lp_curr_path_node->PathName();

	if( m_params.Count() > 0 )
	{
		m_result_output = "系统找不到指定路径";
		return;
	}

	//若有多个路径
	if( m_paths.Count() > 1  )
	{
		m_result_output = "文件名、目录名或卷标语法不正确。";
		return;
	}else if( m_paths.Count() == 0 ){ 
		m_result_output = m_curr_path; 
		return;
	}else{//有一个路径
		if( m_paths.At(0).At(0).Name() == ".." )
		{
			//若当前路径节点不为根
			if( !lp_curr_path_node->IsRoot() )
			{
				lp_curr_path_node = lp_curr_path_node->Parent();
				m_curr_path = lp_curr_path_node->PathName();
				m_result_output = m_curr_path;
			}
		}else if( m_paths.At(0).At(0).Name() == "." ){
			m_result_output = m_curr_path; 
		}else{//搜索具体路径名 
			FileSys::Node* lp_search_node = 
				SearchNodeByPathTokens( m_paths.At(0) );

			if( lp_search_node )
			{
				m_curr_path = lp_search_node->PathName();
				m_result_output.Empty();
			}else{
				m_result_output = "系统找不到指定路径";
			} 
		}
	}


}

}//namespace CommandSys