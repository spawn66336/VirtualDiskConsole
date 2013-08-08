#include "String.h"


namespace Util
{
	 
	StringA FormatA( const char* format , ... )
	{
		StringA str;
		va_list args;
		va_start( args , format );
		int len = _vscprintf( format , args );
		char* str_buf = NULL;
		ZP_SAFE_NEW_BUFFER( str_buf , char , len+1 );
		vsprintf_s(  str_buf , len+1, format , args );
		str = str_buf;
		ZP_SAFE_DELETE_BUFFER( str_buf );
		return str;
	}

	StringW FormatW( const wchar_t* format , ... )
	{
		StringW str;
		va_list args;
		va_start( args , format );
		int len = _vscwprintf( format , args );
		wchar_t* str_buf = NULL;
		ZP_SAFE_NEW_BUFFER( str_buf , wchar_t , len+1 );
		vswprintf(  str_buf , len+1 ,  format , args );
		str = str_buf;
		ZP_SAFE_DELETE_BUFFER( str_buf );
		return str;
	}

}//namespace ZPUTIL