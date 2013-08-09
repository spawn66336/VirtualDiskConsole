#include "CompareCmd.h"

namespace CommandSys
{
	
CompareCmd::CompareCmd(void)
{
}


CompareCmd::~CompareCmd(void)
{

}

void CompareCmd::Execute( void )
{
	if( m_params.Count() > 0 )
	{
		m_result_output = "命令不支持参数";
		return;
	}

	if( m_paths.Count() != 2 )
	{
		m_result_output = "命令语法不正确";
		return;
	}

	Util::String local_disk_filepath = m_paths.At(0).Path();
	Util::String virtual_disk_filepath = m_paths.At(1).Path();

	FileSys::Node* lp_compare_node = SearchNodeByPath( virtual_disk_filepath );
	if( NULL == lp_compare_node )
	{
		m_result_output = "虚拟磁盘中不存在此文件!";
		return;
	}else{

		//当两个文件都为文本文件时才会以字符串形式显示不同
		bool show_text_diff = ( ( !lp_compare_node->IsBinaryFile() ) 
			&& ( TRUE == PathMatchSpec( local_disk_filepath.Ptr() , "*.txt" ) ) );

		if( lp_compare_node->IsFolder() )
		{
			m_result_output = "虚拟磁盘文件路径为文件夹无法比较";
		}else{

			HANDLE file = CreateFile( local_disk_filepath.Ptr() ,GENERIC_READ , 0 , NULL , OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL, NULL  );

			//若文件打开失败
			if( INVALID_HANDLE_VALUE == file )
			{
				m_result_output = "本地磁盘文件打开失败!";
				return;
			}

			DWORD src_file_size = 0;
			src_file_size = GetFileSize( file , NULL );

			if( INVALID_FILE_SIZE != src_file_size )
			{
				DWORD bytes_read = 0;
				char* lp_read_buf = NULL;

				ZP_SAFE_NEW_BUFFER( lp_read_buf , char , src_file_size );

				ReadFile( file , lp_read_buf , src_file_size ,  &bytes_read , NULL );

				Util::VectorT<char> diff1;
				Util::VectorT<char> diff2;
				if( lp_compare_node->Compare( lp_read_buf , src_file_size , diff1 , diff2 ) )
				{
					m_result_output = "内容比较一致";
				}else{//打印不同

					if( show_text_diff )
					{//以字符串形式打印
						m_result_output.Append( Util::StringFormat( "虚拟磁盘文件\"%s\" : \n\"" ,
							lp_compare_node->Name().Ptr() ) );
						for( int i = 0 ; i < diff1.Count() ; i++ )
						{
							m_result_output.Append( Util::StringFormat("%c" , diff1.At(i) ) );
						}
						m_result_output.Append("\"\n");

						m_result_output.Append( Util::StringFormat( "本地磁盘文件\"%s\" : \n\"" ,
							local_disk_filepath.Ptr() ) );
						for( int i = 0 ; i < diff2.Count() ; i++ )
						{
							m_result_output.Append( Util::StringFormat("%c" , diff2.At(i) ) );
						}
						m_result_output.Append("\"\n");
					}else{ //以十六进制打印
						m_result_output.Append( Util::StringFormat( "虚拟磁盘文件\"%s\" : \n" ,
							lp_compare_node->Name().Ptr() ) );
						for( int i = 0 ; i < diff1.Count() ; i++ )
						{
							m_result_output.Append( Util::StringFormat(" %.2X" , (unsigned char)diff1.At(i) ) );
						}
						m_result_output.Append('\n');

						m_result_output.Append( Util::StringFormat( "本地磁盘文件\"%s\" : \n" ,
							local_disk_filepath.Ptr() ) );
						for( int i = 0 ; i < diff2.Count() ; i++ )
						{
							m_result_output.Append( Util::StringFormat(" %.2X" , (unsigned char)diff2.At(i) ) );
						}
						m_result_output.Append('\n');
					}
				}

				ZP_SAFE_DELETE_BUFFER( lp_read_buf );
			}

			CloseHandle( file );
			file = NULL;

		}
	}

}

}//namespace CommandSys