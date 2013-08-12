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

		/**
		* @brief 判断该节点是否为文件
		*/
		virtual bool IsFile( void ) const { return true; }

		/**
		* @brief 根据文件名来判断当前文件是否为二进制文件
		* @retval true 当前文件为二进制文件
		* @retval false 当前文件为文本文件
		*/
		virtual bool IsBinaryFile( void ) const;

		/**
		* @brief 将传入的数据拷贝给该文件
		* @param data 欲拷贝的数据缓冲区指针，此缓冲区由该文件节点负责释放内存
		* @param size 数据缓冲区中数据大小
		* @return 返回实际拷贝的数据大小
		*/
		virtual int Copy( const void* data  , const DWORD size );

		/**
		* @brief 读取虚拟磁盘中文件数据
		* @param offset 读取偏移值（按字节计）
		* @param size 要读取数据的大小
		* @param data 读取数据存入的数据缓冲区指针
		* @return 实际读取的数据大小
		*/
		virtual int Read( const DWORD offset , const DWORD size , void* data  );

		/**
		* @brief 清空节点中附带的数据
		*/
		virtual void ClearData( void );

		/**
		* @brief 此文件节点数据的大小
		* @return 返回文件节点中文件数据的大小
		*/
		virtual DWORD Size(void) const { return m_size; }

 
		virtual DWORD CalcTotalSize(void){ return Size(); }

		virtual bool  Compare( const void* data , const DWORD size  , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2    ) const;

		virtual bool  Compare( const HANDLE file , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2  ) const;
		  
		virtual void DeleteThis(void){ delete this; } 

	private:
		bool m_binary_file;				///>是否为二进制文件
		unsigned char* m_data;		///>数据
		DWORD	 m_size;							///>数据的大小（按字节计）
	};

	/**
	* @brief 判断当前路径的文件是否为文本文件
	*/
	extern bool IsTextFilePath( const Util::String& path );

}//namespace FileSys

#endif // ZP_FILENODE