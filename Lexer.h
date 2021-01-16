#pragma once
#ifndef _LEXER_H_
#define _LEXER_H_
#include "Node.h"



namespace zhangqi {






	//词法分析器
	class Lexer{
	public:
		Lexer();
		~Lexer();


		//获取下一个token
		void next();

		//Node* factor();  //终结符或者表达式
		//Node* term();    //乘除、取余取模
		//Node* pow();     //乘方
		//Node* expr();	  //加减	
		//Node* assign(); //赋值


	

	private:
		char buf[1000] = { 0 };//保存多行字符串
	
		bool FSM_End_Id(char _nC, int _start);									//标识符状态机结束判定
		bool FSM_Op(char _c, char _nC, char _nnC);						//操作符状态机
	
	};


}

#endif