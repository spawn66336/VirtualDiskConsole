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

		/**
		* @brief 根据文件名来判断当前文件是否为二进制文件
		* @retval true 当前文件为二进制文件
		* @retval false 当前文件为文本文件
		*/
		virtual bool IsBinaryFile( void ) const;

		virtual int Copy( const void* data  , const int size );

		virtual int Read( const int offset , const int size , void* data  );

		virtual void ClearData( void );

		virtual int Size(void) const { return m_size; }

		virtual int CalcTotalSize(void){ return Size(); }

		virtual bool  Compare( const void* data , const int size  , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2    ) const;
		  
		virtual void DeleteThis(void){ delete this; } 

	private:
		bool m_binary_file;				///>是否为二进制文件
		unsigned char* m_data;		///>数据
		int	 m_size;							///>数据的大小（按字节计）
	};

	/**
	* @brief 判断当前路径的文件是否为文本文件
	*/
	extern bool IsTextFilePath( const Util::String& path );

}//namespace FileSys

#endif // ZP_FILENODE