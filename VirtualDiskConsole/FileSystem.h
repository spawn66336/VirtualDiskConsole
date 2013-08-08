#ifndef ZP_FILESYSTEM
#define ZP_FILESYSTEM

#include "ZPDependency.h"

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
		* @brief 接受节点访问者访问
		*/
		void Accept( NodeVisitor* visitor );
		
		/**
		* @brief 创建实验用文件树
		*/
		void BuildTestFileTree(void);

	private:
		Node* m_lp_root;		///>文件系统根节点	
	};

}//namespace FileSys

#endif //ZP_FILESYSTEM