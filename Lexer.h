#pragma once
#ifndef _LEXER_H_
#define _LEXER_H_
#include "Node.h"



//定义一个词法分析阶段的测试宏
//#define TEST_LEX


namespace zhangqi {



	//当前token
	extern Tk* curTk;


	//词法分析器
	class Lexer{
	public:
		Lexer();
		~Lexer();


		
		void next();				//获取下一个token

		//优先级： factor > pow > term > expr > assign
		Node* factor();			//终结符或者括号表达式
		Node* pow();			//乘方
		Node* term();			//乘除、取余取模		
		Node* expr();			//加减	
		Node* assign();		//赋值


		//获取最新的token
		Tk* getCurrentToken()const;

		//打印整个tokens容器
		void showAllToken();



		

	private:
		char buf[1000] = { 0 };			//保存多行字符串
		vector<Tk*> tks;					//保存代码中所有的token

		bool FSM_End_Id(char _nC, int _start);									//标识符状态机结束判定
		bool FSM_Op(char _c, char _nC, char _nnC);						//操作符状态机
		void FSM_End_Str(int _start);													//单行字符串结束的收尾工作
	

	private:
		vector<Node*> codeL;			//语句列表

	};

	


}

#endif