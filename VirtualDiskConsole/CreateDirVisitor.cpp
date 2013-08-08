#include "CreateDirVisitor.h"
#include "Node.h"

namespace FileSys
{

	CreateDirVisitor::CreateDirVisitor(void)
	{
	}


	CreateDirVisitor::~CreateDirVisitor(void)
	{
	}

	void CreateDirVisitor::Visit( Node* node )
	{
		ZP_ASSERT( NULL != node ); 

		if( NULL != node )
		{
			if( HasNextToken() )
			{
				LexerSys::Token curr_tok = GetCurrPathToken();
				MoveToNextToken();

				if( 
					curr_tok.Type() == LexerSys::Token::DRIVE_TOKEN ||
					curr_tok.Type() == LexerSys::Token::WILDCARD_TOKEN 
					)
				{
					m_result_output_str = "文件名、目录名或卷标语法不正确";
					return;
				}

				if( curr_tok.Name() == "." )
				{ 
					node->Accept( this );
					return; 
				}else if( curr_tok.Name() == ".." ){

					//若当前节点不为根节点
					if( !node->IsRoot() )
					{
						node->Parent()->Accept( this );
						return;
					}else{
						node->Accept( this );
						return;
					}
				}

				//若遍历的节点为文件夹
				if( node->IsFolder() )
				{ 
					Node* lp_next_node = node->FindNode( curr_tok.Name() );
					if( NULL != lp_next_node )
					{ 
						lp_next_node->Accept( this );
						return;
					}else{
						node = node->CreateNode( curr_tok.Name() , Node::FOLDER_NODE );
						if( NULL != node )
						{
							node->Accept( this );
							return;
						}
					}

				} //if( node->IsFolder() )
			}//if( HasNextToken() )
		}//if( NULL != node ) 

	} 

}//namespace FileSys

