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
		m_result_output = m_curr_path.Path(); 
		return;
	}else{//有一个路径
			FileSys::Node* lp_search_node = 
				SearchNodeByPath( m_paths.At(0) );
			if( lp_search_node )
			{
				if( lp_search_node->IsFolder() )
				{
					m_curr_path = lp_search_node->PathName();
					m_result_output.Empty();
				}else{
					m_result_output = "目录名无效";
				}
			}else{
				m_result_output = "系统找不到指定路径";
			} 
	} 

}

}//namespace CommandSys