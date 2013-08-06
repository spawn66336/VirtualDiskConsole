#include "LexerImpl.h"

namespace Lexer_Sys
{   

	const ZPUTIL::LinkListT<Token>& LexerImpl::GetTokenList() const
	{
		ZP_ASSERT( STATE_ANALYSISED == m_state );
		return m_tokens;
	}

	void LexerImpl::Clear( void )
	{
		m_state = STATE_UNLOAD;
		m_str_buf.Clear();
		m_tokens.Clear();
	}

}//namespace Lexer_Sys