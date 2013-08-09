#include "CopyCmd.h"


namespace CommandSys
{
	 
CopyCmd::CopyCmd( void )
{

}
 
CopyCmd::~CopyCmd( void )
{

}

void CommandSys::CopyCmd::Execute( void )
{
	if( m_params.Count() > 0 )
	{
		m_result_output = "命令不支持参数";
		return;
	}

	if( m_paths.Count() == 0 )
	{
		m_result_output = "命令语法不正确";
		return;
	}

	if( m_paths.Count() != 2 )
	{
		m_result_output = "命令语法不正确";
		return;
	}
	 
	LexerSys::SearchPath src_path = m_paths.At(0);
	LexerSys::SearchPath dst_path = m_paths.At(1);

	//测试目标路径是否是一个文件夹
	BOOL src_path_is_folder = PathIsDirectory( src_path.Path().Ptr() ); 
	Util::String src_path_origin = src_path.Path();
	Util::String src_path_without_filespec = src_path_origin;

	FileSys::Node* lp_search_node = SearchNodeByPathTokens( dst_path );

	if( TRUE == src_path_is_folder )
	{
		//未找到目标节点
		if( lp_search_node == NULL )
		{
			m_result_output = "拷贝的目的文件夹不存在";
			return;
		}else{
			//找到目标节点但是是一个文件
			if( lp_search_node->IsFile() )
			{
				m_result_output = "由于拷贝源路径指向文件夹，所以目的路径必须是文件夹";
				return;
			} 
		}
		//截掉最后的文件名
		src_path_without_filespec = src_path_origin.SubString( 0 , 
			src_path_origin.Length() - ( src_path_origin.Length() -src_path_origin.FindLastOf('\\') ) );

	}//if( TRUE == src_path_is_folder )
	 

	WIN32_FIND_DATA find_data;
	memset( &find_data , 0 , sizeof(find_data) );
	HANDLE handle_findfile = FindFirstFile( src_path.Path().Ptr() , &find_data );
	if( INVALID_HANDLE_VALUE == handle_findfile )
	{
		m_result_output = "本地磁盘路径输入有误";
		return;
	}  

	//查找本地磁盘的路径所指定的文件并将文件名放入
	Util::QueueT<Util::String>  copy_filenames; 
	do{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
		{
			copy_filenames.Enqueue( find_data.cFileName );  
		}
	} while( FindNextFile( handle_findfile , &find_data ));
	  
	FindClose( handle_findfile );
	handle_findfile = NULL;
	   

	m_result_output = Util::StringFormat( "总共拷贝了%d个文件\n", 
													copy_filenames.Size() ); 
	while( copy_filenames.Size() )
	{
		m_result_output.Append( copy_filenames.Front() );
		m_result_output.Append('\n'); 
		copy_filenames.Dequeue();
	}



}


}//namespace CommandSys