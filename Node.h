#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include"Utils.h"


namespace zhangqi {



	/*-----------------------------抽象节点----------------------------------*/
	class Node{ //元节点
	public:
		virtual ~Node() {};
		virtual void visit() = 0;//遍历AST
		virtual void destroy() = 0;//删除每一个节点
	};
	class TreeN : public Node {  //树节点
	public:
		Node* l;
		Node* r;
		TreeN(Node* _l,Node* _r) : l(_l) , r(_r) {}
		~TreeN() { destroy(); }

		void destroy();
	};




	/*---------------------------------------------------------------------------*/




	/*---------------------具体的非终结符节点---------------------------*/


	class AddN : public TreeN {
	public:
		AddN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class SubN : public TreeN {
	public:
		SubN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class MulN : public TreeN {
	public:
		MulN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class DivN : public TreeN {
	public:
		DivN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class PowN : public TreeN {
	public:
		PowN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class ModN : public TreeN {
	public:
		ModN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};
	class RemN : public TreeN {
	public:
		RemN(Node* _l, Node* _r) : TreeN(_l, _r) {	}
		void visit();
	};




	

	//class IfN : public Node {
	//public:
	//	IfN();
	//	~IfN();
	//	void visit();
	//	void destroy();
	//private:
	//	Node* cond;		//if的条件
	//	Node* block;    //
	//};
	//class ElifN : public Node {
	//public:
	//	ElifN();
	//	~ElifN();
	//	void visit();
	//	void destroy();
	//private:
	//	Node* cond;		//elif的条件
	//};
	//class ElseN : public Node {
	//public:
	//	ElifN();
	//	~ElifN();
	//	void visit();
	//	void destroy();
	//};
	//


	/*---------------------------------------------------------------------------*/


	/*-----------------------具体的终结符节点----------------------------*/


	//字面量数字
	class NumN : public Node {
	private:
		double v;
	public:
		NumN(double _v) :v(_v) {	}
		void visit();
		void destroy() {
			//pass
		}
	};

	//字面量字符串
	class StrN : public Node {
	private:
		char s[256];
	public:
		StrN(char _s[256]);
		void visit();
		void destroy() {
			//pass
		}
	};


	//变量，属于标识符
	class VarN : public Node {
	private:
		VarType t;  //变量类型
	public:
		VarN() {	}
		void visit();
		void destroy();

	};



	/*---------------------------------------------------------------------------*/




}


#endif
