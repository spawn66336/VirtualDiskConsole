#include "NodeVisitor.h"

namespace FileSys
{
	 
NodeVisitor::NodeVisitor(void):
m_lp_final_search_node(NULL)
{
}


NodeVisitor::~NodeVisitor(void)
{
	m_path_toks.Clear();
}

void NodeVisitor::SetPathToks( const Util::LinkListT<LexerSys::Token>& toks )
{
	m_path_toks = toks;
	m_curr_tok = m_path_toks.Begin();
} 

LexerSys::Token NodeVisitor::GetCurrPathToken( void ) const
{
	return *m_curr_tok;
}

bool NodeVisitor::HasNextToken( void ) const
{
	return m_curr_tok.HasNext();
}

void NodeVisitor::MoveToNextToken( void )
{
	m_curr_tok.Next();
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