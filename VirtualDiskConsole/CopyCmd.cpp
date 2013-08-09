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
	Util::String final_src_path = src_path_origin;

	Util::String dst_path_origin = dst_path.Path();
	if( !dst_path.IsAbsolutePath() )
	{
		dst_path_origin = m_curr_path.Path() + dst_path.Path();
	}
	Util::String final_dst_path = dst_path_origin;

	FileSys::Node* lp_search_node = SearchNodeByPath( dst_path );

	if( TRUE == src_path_is_folder )
	{
		//未找到目标文件夹结点
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
			} //if( lp_search_node->IsFile() )
		}  
	}else{//若为单文件拷贝 

		//截掉最后的文件名
		final_src_path = src_path_origin.SubString( 0 , 
			src_path_origin.Length() - ( src_path_origin.Length() - src_path_origin.FindLastOf('\\') ) );
	}
	 

	WIN32_FIND_DATA find_data;
	memset( &find_data , 0 , sizeof(find_data) );
	HANDLE handle_findfile = FindFirstFile( src_path.Path().Ptr() , &find_data );
	if( INVALID_HANDLE_VALUE == handle_findfile )
	{
		m_result_output = "本地磁盘路径输入有误";
		return;
	}  

	//查找本地磁盘的路径所指定的文件并将文件路径放入列表
	Util::LinkListT<Util::String>  copy_src_paths; 
	Util::LinkListT<Util::String>  copy_src_filenames;
	do{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
		{
			copy_src_filenames.PushBack( find_data.cFileName );
			copy_src_paths.PushBack( final_src_path + "\\" + find_data.cFileName );  
		}
	} while( FindNextFile( handle_findfile , &find_data ));

	FindClose( handle_findfile );
	handle_findfile = NULL;
	  
	Util::LinkListT<FileSys::Node*> dst_file_nodes;
	if( lp_search_node )
	{
		if( lp_search_node->IsFile() )
		{
			dst_file_nodes.PushBack( lp_search_node );
		}else{//若为文件夹,则需创建文件结点
			Util::LinkListT<Util::String>::Iterator it = copy_src_filenames.Begin();
			while( it != copy_src_filenames.End() )
			{
				FileSys::Node* lp_new_node = lp_search_node->CreateNode( *it , FileSys::Node::FILE_NODE );
				dst_file_nodes.PushBack( lp_new_node );
				it.Next();
			}
		}
	}else{//若目标路径结点不存在

		//搜索该目标文件的上级文件夹
		final_dst_path = dst_path_origin.SubString( 0 , 
			dst_path_origin.Length() - ( dst_path_origin.Length() - dst_path_origin.FindLastOf('\\') ) );

		lp_search_node = SearchNodeByPath( final_dst_path );

		if( NULL == lp_search_node )
		{
			m_result_output = "拷贝的目标路径文件夹不存在!";
			return;
		}

		 int j = dst_path_origin.FindLastOf('\\');
		Util::String dst_filename = dst_path_origin.SubString(  j+1  , dst_path_origin.Length()-j-1 );
		dst_filename.Trim();
		if( dst_filename.IsEmpty() )
		{
			m_result_output = "拷贝的目标路径文件夹不存在!";
			return;
		}

		FileSys::Node* lp_new_node = lp_search_node->CreateNode( dst_filename , FileSys::Node::FILE_NODE );
		dst_file_nodes.PushBack( lp_new_node );
	}
	 

	//逐一拷贝文件
	Util::LinkListT<Util::String>::Iterator path_it = copy_src_paths.Begin();
	Util::LinkListT<FileSys::Node*>::Iterator dst_it = dst_file_nodes.Begin();
	while( 
		dst_it != dst_file_nodes.End() &&
		path_it != copy_src_paths.End() 
		)
	{

		HANDLE file = CreateFile( (*path_it).Ptr() , GENERIC_READ , 0 , NULL , OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL, NULL );

		//若文件打开失败
		if( INVALID_HANDLE_VALUE == file )
		{
			m_result_output.Append( Util::StringFormat("文件\"%s\"打开失败! \n", (*path_it).Ptr() ) );
			dst_it.Next();
			path_it.Next();
			continue;
		}
		 
		DWORD src_file_size = 0;
		src_file_size = GetFileSize( file , NULL );

		if( INVALID_FILE_SIZE != src_file_size )
		{
			DWORD bytes_read = 0;
			char* lp_read_buf = NULL;

			ZP_SAFE_NEW_BUFFER( lp_read_buf , char , src_file_size );

			ReadFile( file , lp_read_buf , src_file_size ,  &bytes_read , NULL );

			(*dst_it)->Copy( lp_read_buf , bytes_read );

			ZP_SAFE_DELETE_BUFFER( lp_read_buf );
		}

		CloseHandle( file );
		file = NULL;

		m_result_output.Append( *path_it );
		m_result_output.Append('\n');  

		dst_it.Next();
		path_it.Next();
	}

	m_result_output.Append( Util::StringFormat( "总共拷贝了%d个文件\n", 
		copy_src_paths.Count() ) ); 
	copy_src_paths.Clear(); 
}


}//namespace CommandSys