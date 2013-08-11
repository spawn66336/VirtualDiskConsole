#ifndef ZP_NODE
#define ZP_NODE

#include "ZPDependency.h"


namespace FileSys
{
	class NodeVisitor;

	class Node
	{
	public: 

		enum NodeType{
			FILE_NODE = 1, 
			FOLDER_NODE
		};

		Node();
		virtual ~Node();

		/**
		* @brief 返回节点名称
		* @return 返回名称
		*/
		Util::String Name() const { return m_name; }

		/**
		* @brief 设置节点名称
		* @param name 节点名称
		*/
		void Name( const Util::String& name ){ m_name = name; } 

		/**
		* @brief 获得当前节点的路径全名
		*/
		Util::String PathName(void) const;
		 
		/**
		* @brief 返回父节点
		* @return 父节点指针
		*/
		Node* Parent(void) const { return m_lp_parent; }

		/**
		* @brief 设置父节点指针
		* @param node 父节点指针
		*/
		void Parent( Node* node ){ m_lp_parent = node; }

		/**
		* @brief 是否为叶节点
		* @return 返回节点是否为叶节点
		*/
		bool IsLeaf( void ) const { return ( m_child_nodes.Count() == 0 ); }

		/**
		* @brief 是否为根节点
		* @return 返回节点是否为根节点
		*/
		bool IsRoot( void ) const { return m_lp_parent == NULL; }

		/**
		* @brief 是否为文件
		* @return 返回是否为文件
		*/
		virtual bool IsFile( void ) const { return false; }

		/**
		* @brief 是否为文件夹
		* @return 返回是否为文件夹
		*/
		virtual bool IsFolder( void ) const { return false; }

		/**
		* @brief 传入的节点是否为当前节点祖先
		* @return 返回是否为祖先
		* @retval true 是祖先节点
		* @retval false 不是祖先节点
		*/
		virtual bool IsAncestor( Node* node );

		/**
		* @brief 查找节点
		* @param name 要查找名称
		* @return 查找的节点
		*/
		Node* FindNode( const Util::String& name  );

		Node* FindFileNodeBySpec( const Util::String& spec );

		/**
		* @brief 创建节点
		* @param name 节点名称
		* @param type 节点类型
		* @return 返回创建的节点
		*/
		Node* CreateNode( const Util::String& name , const NodeType type );

		/**
		* @brief 删除这名称指定的节点
		* @name 要删除的节点名称
		* @return 返回是否删除成功
		* @retval  true 找到节点并删除成功
		* @retval  false	 未找到节点
		*/
		bool DeleteNode( const Util::String& name  );

		/**
		* @brief 删除该节点下属所指定类型的节点
		*/
		void DeleteNodeByType( const NodeType type );

		/**
		* @brief 销毁结点自身信息
		*/
		virtual void Destroy( void ); 
		
		/**
		* @brief 删除自身
		*/
		virtual void DeleteThis(void){ delete this; }


		/**
		* @brief 接手访问者访问
		* @param visitor 访问者
		*/
		virtual void Accept( NodeVisitor* visitor );

		virtual int Copy( const void* data  , const int size  ){ return 0; }

		virtual int Read( const int offset ,  const int size , void* data ){ return 0; } 

		virtual void ClearData( void ){ }

		/**
		* @brief 返回文件是否为二进制文件
		* @return 返回文件是否是二进制文件
		* @retval true 为二进制文件
		* @retval false 为文本文件
		*/
		virtual bool IsBinaryFile( void ) const { return false; }

		/**
		* @brief 返回节点所含数据大小
		* @return 节点所含的数据大小按字节计
		*/
		virtual int Size(void) const { return 0; }


		virtual int CalcTotalSize(void){ return 0; }


		virtual bool  Compare( const void* data , const int size , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2  ) const{ return false;}
	
		/**
		* @brief 获取文件列表打印字符串
		* @param output 为最终存放文件列表的字符串
		* @param recursive 指示是否是递归显示子目录与子文件
		*/
		virtual void GetFileListOutputString(  Util::String& output , const bool recursive = false , const bool folder_only = false  ) const;
		  
	protected:
		Util::String m_name;								///>节点名称 
		Node* m_lp_parent;										///>父节点指针
		Util::LinkListT<Node*> m_child_nodes;	///>子节点列表
	};

}//namespace FileSys

#endif//ZP_NODE