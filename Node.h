#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include"Utils.h"


namespace zhangqi {


	//节点类型定义
	typedef enum { //N_在开头
		N_Node,
		N_Tree,
		N_Literal,
		N_Add,
		N_Sub,
		N_Mul,
		N_Div,
		N_Pow,
		N_Mod,
		N_Rem,
		N_Num,
		N_Str,
		N_Var
	}NodeType;



	/*-----------------------------抽象节点----------------------------------*/
	class Node{ //元节点
	public:
		virtual NodeType getType()const { return  NodeType::N_Node; }

		virtual ~Node() {};
		virtual void visit() = 0;//遍历AST
		virtual void destroy() = 0;//删除每一个节点,但是对于字面量结点来说没有作用
	};
	class TreeN : public Node {  //树节点
	protected:
		Node* l;
		Node* r;
	public:
		TreeN(Node* _l, Node* _r) : l(_l), r(_r){}
		virtual NodeType getType()const { return  NodeType::N_Tree; }
		virtual ~TreeN() { destroy(); }

		void destroy();
	};
	class LiteralN : public Node { //字面量节点
	public:
		virtual NodeType getType()const { return  NodeType::N_Literal; }
		virtual ~LiteralN() {}		
	};



	


	/*---------------------------------------------------------------------------*/




	/*---------------------具体的非终结符节点---------------------------*/


	class AddN : public TreeN {
	public:
		AddN(Node* _l, Node* _r) : TreeN(_l, _r) { }
		virtual NodeType getType()const { return  NodeType::N_Add; }
		void visit();
	};
	class SubN : public TreeN {
	public:
		SubN(Node* _l, Node* _r) : TreeN(_l, _r) { }
		virtual NodeType getType()const { return  NodeType::N_Sub; }
		void visit();
	};
	class MulN : public TreeN {
	public:
		MulN(Node* _l, Node* _r) : TreeN(_l, _r) {  }
		virtual NodeType getType()const { return  NodeType::N_Mul; }
		void visit();
	};
	class DivN : public TreeN {
	public:
		DivN(Node* _l, Node* _r) : TreeN(_l, _r) {  }
		virtual NodeType getType()const { return  NodeType::N_Div; }
		void visit();
	};
	class PowN : public TreeN {
	public:
		PowN(Node* _l, Node* _r) : TreeN(_l, _r) {}
		virtual NodeType getType()const { return  NodeType::N_Pow; }
		void visit();
	};
	class ModN : public TreeN {
	public:
		ModN(Node* _l, Node* _r) : TreeN(_l, _r) {}
		virtual NodeType getType()const { return  NodeType::N_Mod; }
		void visit();
	};
	class RemN : public TreeN {
	public:
		RemN(Node* _l, Node* _r) : TreeN(_l, _r) {}
		virtual NodeType getType()const { return  NodeType::N_Rem; }
		void visit();
	};




	/*---------------------------------------------------------------------------*/


	/*-----------------------具体的终结符节点----------------------------*/


	//字面量数字
	class NumN : public LiteralN {
	private:
		double v;
	public:
		NumN(double _v) :v(_v) { }
		virtual NodeType getType()const { return  NodeType::N_Num; }
		void visit();
		void destroy(){}
	};

	//字面量字符串
	class StrN : public LiteralN {
	private:
		char* s;
	public:
		StrN(char* _s) : s(_s) {  }
		virtual NodeType getType()const { return  NodeType::N_Str; }
		void visit();		
		void destroy() {}
	};


	//变量，属于标识符
	//！！！暂时全都算作变量好了！！！
	class VarN : public Node {
	private:
		VarType t;				//变量类型
		unsigned int hash;	//变量池中的索引
		char* name;             //变量名
	public:
		VarN(char* _s);
		unsigned int getHash()const { return hash; }
		virtual NodeType getType()const { return  NodeType::N_Var; }
		void visit();
		void destroy() {}
	};



	/*---------------------------------------------------------------------------*/




}


#endif
