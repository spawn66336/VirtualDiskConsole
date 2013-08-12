#include "FileNode.h"

namespace FileSys
{
	 
FileNode::FileNode(void):
m_binary_file(false),
m_size(0),
m_data(NULL)
{
}


FileNode::~FileNode(void)
{
	this->ClearData();
}


bool FileNode::IsBinaryFile( void ) const
{
	return !IsTextFilePath( m_name );
}

bool FileNode::Compare( const void* data , const DWORD size , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2 ) const
{
	if( NULL == data || 0 == size )
	{
		return false;
	}

	DWORD i = 0;
	DWORD j = 0;

	while( i < m_size && j < size )
	{
		char c1 = m_data[i];
		char c2 = reinterpret_cast<const char*>(data)[j];
		if( c1 != c2 )
		{
			break;
		} 
		i++;
		j++;
	}

	//比较一致
	if( i == m_size && j == m_size )
	{
		return true;
	}

	int count1 = 16;
	int count2 = 16;
	while( i < m_size && count1 > 0 )
	{
		diff1.PushBack( m_data[i] );
		i++;
		count1--;
	}

	while( j < size && count2 > 0 )
	{
		diff2.PushBack( reinterpret_cast<const char*>(data)[j] );
		j++;
		count2--;
	}

	return false;
}

bool FileNode::Compare( const HANDLE file , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2 ) const
{
	if( INVALID_HANDLE_VALUE == file )
	{
		return false;
	}

	//获取文件大小
	LARGE_INTEGER src_file_size;  
	if( FALSE == GetFileSizeEx( file , &src_file_size ) )
	{
		return false;
	}

	//文件大小过大
	if( 0 != src_file_size.HighPart )
	{
		return false;
	}

	DWORD i = 0;
	DWORD j = 0; 
	DWORD total_cmp_bytes = 0;

	char read_buf[256] = {0};
	DWORD bytes_to_read = 256;
	DWORD read_bytes = 0;
	BOOL read_result = FALSE;

	while( i < m_size  )
	{ 
		if( j == read_bytes )
		{
			j = 0;
			read_result = ReadFile( file , read_buf , bytes_to_read , &read_bytes , NULL );
			//若文件已经读完则跳出比较循环
			if(  0 == read_bytes )
			{
				break;
			}
		} 

		char c1 = m_data[i];
		char c2 = read_buf[j];

		if( c1 != c2 )
		{
			break;
		} 
		i++; j++;
		total_cmp_bytes++;
	}
	 
	//比较一致
	if( i == m_size && total_cmp_bytes == src_file_size.LowPart  )
	{
		return true;
	}

	int count1 = 16;
	int count2 = 16;
	while( i < m_size && count1 > 0 )
	{
		diff1.PushBack( m_data[i] );
		i++;
		count1--;
	}

	while(  count2 > 0 )
	{
		if( j == read_bytes )
		{
			j = 0;
			read_result = ReadFile( file , read_buf , bytes_to_read , &read_bytes , NULL );
			//若文件已经读完则跳出比较循环
			if(  0 == read_bytes )
			{
				break;
			}
		}  
		 
		diff2.PushBack( read_buf[j] );
		j++;
		count2--;
	} 

	return false; 
}


int FileSys::FileNode::Copy( const void* data  , const DWORD size  )
{   

	ZP_SAFE_DELETE_BUFFER( m_data ); 
	m_size = 0;

	if( NULL == data || 0 == size )
	{
		return 0;
	}

	m_data = reinterpret_cast<unsigned char*>( const_cast<void*>(data) );
	m_size = size; 
	return size;
}

int FileSys::FileNode::Read( const DWORD offset , const DWORD size , void* data )
{ 
	if( NULL == data ||  size == 0 ) return 0;
	if( offset < 0 || offset >= m_size ) return 0; 
	int read_size = ( m_size - offset ) < size ? ( m_size - offset ) : size;
	memcpy( data , &m_data[offset] , sizeof( read_size ) );
	return read_size;
} 


void FileNode::ClearData( void )
{
	ZP_SAFE_DELETE_BUFFER( m_data ); 
	m_size = 0;
}


bool IsTextFilePath( const Util::String& path )
{
	if( 
		TRUE == PathMatchSpec( path.Ptr() , "*.txt") 
		|| TRUE == PathMatchSpec( path.Ptr() , "*.ini")
		|| TRUE == PathMatchSpec( path.Ptr() , "*.xml")
		|| TRUE == PathMatchSpec( path.Ptr() , "*.log")
		|| TRUE == PathMatchSpec( path.Ptr() , "*.bat")
		|| TRUE == PathMatchSpec( path.Ptr() , "*.html")
		)
	{
		return true;
	}
	return false;
}


 



}//namespace FileSys