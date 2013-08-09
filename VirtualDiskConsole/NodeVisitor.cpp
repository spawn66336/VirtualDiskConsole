#include "NodeVisitor.h"

namespace FileSys
{
	 
NodeVisitor::NodeVisitor(void):
m_lp_final_search_node(NULL)
{
}


NodeVisitor::~NodeVisitor(void)
{
	m_path.Clear();
}

void NodeVisitor::SetPath( const LexerSys::SearchPath& path )
{
	m_path = path; 
} 

LexerSys::Token NodeVisitor::GetCurrPathToken( void ) const
{
	LexerSys::Token tok;
    m_path.CurrToken(tok);
	return tok;
}

bool NodeVisitor::HasNextToken( void ) const
{
	return m_path.HasNext();
}

void NodeVisitor::MoveToNextToken( void )
{
	m_path.MoveToNextToken();
}

Node* NodeVisitor::GetSearchNode( void )
{
	return m_lp_final_search_node;
}

Util::String NodeVisitor::GetResultOutputString( void ) const
{
	return m_result_output_str;
}

}//namespace FileSys