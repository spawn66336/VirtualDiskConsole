#ifndef ZP_FILESYSTEM
#define ZP_FILESYSTEM

#include "ZPDependency.h"

#define FILESYSTEM_CAPACITY  (1<<30)

namespace FileSys
{
	class Node;
	class NodeVisitor;

	class FileSystem : public Util::SingletonT<FileSystem>
	{
	public:
		FileSystem(void);
		virtual ~FileSystem(void);

		/**
		* @brief 获取文件系统根节点
		* @return 根节点
		*/
		Node* Root(void) const { return m_lp_root; }

		/**
		* @brief 返回文件系统的总共使用了多少内存(按字节计)
		*/
		DWORD TotalSize(void);

		/**
		* @brief 返回文件系统的最大容量
		*/
		DWORD Capacity( void ) const;

		/**
		* @brief 查看磁盘空间是否足够容纳size个字节
		*/
		bool HasEnoughSpace( const DWORD size );

		/**
		* @brief 接受节点访问者访问
		*/
		void Accept( NodeVisitor* visitor );
		
		/**
		* @brief 创建实验用文件树
		*/
		void BuildTestFileTree(void);

	private:
		Node* m_lp_root;		///>文件系统根节点	
		int m_capacity;			///>文件系统最大容量
	};

}//namespace FileSys

#endif //ZP_FILESYSTEM