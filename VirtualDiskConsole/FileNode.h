#ifndef ZP_FILENODE
#define ZP_FILENODE

#include "Node.h"

namespace FileSys
{ 

	class FileNode : public Node
	{
	public:
		FileNode(void);
		virtual ~FileNode(void);

		virtual bool IsFile( void ) const { return true; }

		virtual bool IsBinaryFile( void ) const { return m_binary_file; }

		virtual int Write( const void* data  , const int size );

		virtual int Read( const int offset , const int size , void* data  );

		virtual int Size(void) const { return m_size; }

		virtual bool  Compare( const Node* other_node , ZPUTIL::String& output)  const;

		virtual bool  Compare( const void* data , const int size , ZPUTIL::String& output  ) const;



		virtual void DeleteThis(void){ delete this; }

	protected:
		
		/**
		* @brief 判断传入的数据是否为二进制数据
		* @param data 传入数据缓冲区指针
		* @param size 数据缓冲区实际数据大小
		* @return 返回是否为二进制数据
		* @warning data数据字段禁止传入空指针，否则会触发断言
		*/
		bool IsBinaryFileData( const void* data , const int size ) const;

	private:
		bool m_binary_file;				///>是否为二进制文件
		unsigned char* m_data;		///>数据
		int	 m_size;							///>数据的大小（按字节计）
	};

}//namespace FileSys

#endif // ZP_FILENODE