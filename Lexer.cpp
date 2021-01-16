#include "Lexer.h"



namespace zhangqi {





	Lexer::Lexer() {


	}
	Lexer::~Lexer() {

	}



	

	bool Lexer::FSM_End_Id(char _nC, int _start ) {			//标识符状态机结束判定
		if (	!(
				(_nC <= 'Z' && _nC >= 'A') || (_nC <= 'z' && _nC >= 'a') ||
				(_nC == '_' || _nC == '@' || _nC == '$') ||
				(_nC <= '9' && _nC >= '0')
				)) {

			int end = g_cols - 1;//结束的位置
			cout << "\tid = ";
			for (int i = _start; i < end; ++i)cout << g_lineContent[i];
			cout << endl;
			return true;
		}

		return false;
	}




	bool Lexer::FSM_Op(char _c, char _nC, char _nnC) {	//操作符状态机  


		switch (_c) {
		case '+':
			cout << "\top = " << CodeToStr(TkType::_PLUS) << endl;
			return true;
		case '-':
			if (_nC == '>') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_ARROW) << endl;
			}
			else cout << "\top = " << CodeToStr(TkType::_MINUS) << endl;
			return true;
		case '*':
			cout << "\top = " << CodeToStr(TkType::_STAR) << endl;
			return true;
		case '/':
			cout << "\top = " << CodeToStr(TkType::_SLASH) << endl;
			return true;
		case '^':
			cout << "\top = " << CodeToStr(TkType::_CARET) << endl;
			return true;
		case '%':
			if (_nC == '%') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_MMOD) << endl;
			}
			else cout << "\top = " << CodeToStr(TkType::_MOD) << endl;
			return true;
		case '.':
			if (_nC == '.') {
				if (_nnC == '.') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_DDDOT) << endl;
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_DDOT) << endl;
				}
			}
			else cout << "\top = " << CodeToStr(TkType::_DOT) << endl;
			return true;
		case ',':
			cout << "\top = " << CodeToStr(TkType::_COM) << endl;
			return true;
		case '=':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_EEEQL);
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_EEQL) << endl;
				}
			}
			else	cout << "\top = " << CodeToStr(TkType::_EQL) << endl;
			return true;
		case '#':
			cout << "\top = " << CodeToStr(TkType::_HASH) << endl;
			return true;
		case '{':
			cout << "\top = " << CodeToStr(TkType::_LB) << endl;
			return true;
		case '}':
			cout << "\top = " << CodeToStr(TkType::_RB) << endl;
			return true;
		case '[':
			cout << "\top = " << CodeToStr(TkType::_LE) << endl;
			return true;
		case ']':
			cout << "\top = " << CodeToStr(TkType::_RE) << endl;
			return true;
		case '(':
			cout << "\top = " << CodeToStr(TkType::_LP) << endl;
			return true;
		case ')':
			cout << "\top = " << CodeToStr(TkType::_RP) << endl;
			return true;
		case '<':
			if (_nC == '<') {
				if (_nnC == '<') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_LLLESS) << endl;
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_LLESS) << endl;
				}
			}
			else if (_nC == '=') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_COMPARE) << endl;
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_LESSEQL) << endl;
				}
			}
			else cout << "\top = " << CodeToStr(TkType::_LESS) << endl;
			return true;
		case '>':
			if (_nC == '>') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_GGGREAT) << endl;
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_GGREAT) << endl;
				}
			}
			else if (_nC == '=') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_GREATEQL) << endl;
			}
			else cout << "\top = " << CodeToStr(TkType::_GREAT) << endl;
			return true;
		case '~':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_TILDEEQL) << endl;
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_TILDEQL) << endl;
				}
			}
			else cout << "\top = " << CodeToStr(TkType::_TILDE) << endl;
			return true;
		case '?':
			cout << "\top = " << CodeToStr(TkType::_QUE) << endl;
			return true;
		case '&':
			if (_nC == '&') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_AAMP) << endl;

			}
			else cout << "\top = " << CodeToStr(TkType::_AMP) << endl;
			return true;
		case '|':
			if (_nC == '|') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_VVBAR);
			}
			else cout << "\top = " << CodeToStr(TkType::_VBAR) << endl;
			return true;
		case '`':
			cout << "\top = " << CodeToStr(TkType::_GRAVE) << endl;
			return true;
		case ':':
			if (_nC == ':') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_CCOLON) << endl;
			}
			else cout << "\top = " << CodeToStr(TkType::_COLON) << endl;
			return true;
		case '\\':
			cout << "\top = " << CodeToStr(TkType::_BSLASH) << endl;
			return true;
		case '!':
			cout << "\top = " << CodeToStr(TkType::_BANG) << endl;
			return true;
		case ';':
			cout << "\top = " << CodeToStr(TkType::_SEMI) << endl;
			return true;
		}

		return false;
	}








	void Lexer::next() {


		char c,nC,nnC;
		double v = 0;
		int nums=0;//小数部分的数字个数	
		int start = 0;
		

		static int flag_syn = 0;	//选择了一个状态机，就要忽略其他状态机 
		/*
		1:多行注释状态机
		2:数字状态机-整数部分
		3:标识符状态机
		4:数字状态机-小数部分
		5:多行字符串状态机
		6:单引号字符串状态机
		7:双引号字符串状态机
		*/

	

		
		
		while (g_cols < g_lineSize + 1) {  //列数从1开始

			//获取第g_cols列字符
			c = g_lineContent[(g_cols++) - 1];
			//向前看一个
			nC = g_lineContent[g_cols - 1];
			//向前看两个
			nnC = g_lineContent[g_cols];


			/*-----------------------------注释状态机----------------------------------*/
			if (flag_syn == 0) {
				if (c == '-' && nC == '-') {
					if (nnC == '[') { //多行注释
						g_cols = g_lineSize + 1;//列指针移动到末尾
						flag_syn = 1;
						return;
					}
					else { //单行注释
						g_cols = g_lineSize + 1;//列指针移动到末尾
						return;
					}
				}
			}
			else if (flag_syn == 1) {
				if (c == ']')
					flag_syn = 0;
				return;
			}
			/*-------------------------------------------------------------------------------*/



			/*------------------------------数字状态机----------------------------------*/
			if (flag_syn == 0 || flag_syn == 2 || flag_syn == 4) {
				if (c <= '9' && c >= '0') {
					if (flag_syn == 0)
						flag_syn = 2;

					//整数部分
					if (flag_syn == 2) {
						v = v * 10 + c - '0';
						if (nC == '.') {
							flag_syn = 4;
							g_cols++;//指针右移一位
							nC = g_lineContent[g_cols - 1];
						}
					}
					//小数部分
					else if (flag_syn == 4) {
						double tmp = c - '0';
						nums++;
						for (int i = 0; i < nums; ++i)  //小数部分计算
							tmp *= 0.1;

						v = v + tmp;
					}

					//结束判定
					if (!(nC <= '9' && nC >= '0')) {
						flag_syn = 0;
						cout << "\tnum = " << v << endl;
						return;
					}
				}
			}

			/*-------------------------------------------------------------------------------*/




			/*-----------------------------标识符状态机--------------------------------*/
			if (flag_syn == 0 || flag_syn == 3) {
				if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_' || c == '@' || c == '$') {
					if (flag_syn == 0) {
						start = g_cols - 2;//开始的位置
						flag_syn = 3;
					}
					if (flag_syn == 3 && FSM_End_Id(nC, start)) {
						flag_syn = 0;
						return;
					}
				}
				else if (c <= '9' && c >= '0') {
					if (flag_syn == 3 && FSM_End_Id(nC, start)) {
						flag_syn = 0;
						return;
					}
				}
			}

			/*-------------------------------------------------------------------------------*/


			/*------------------------字符串状态机------------------------------------*/
			auto end_string = [](int _start) {
				int end = g_cols - 3;//结束的位置
				cout << "\tstring = ";
				for (int i = _start; i < end; ++i)cout << g_lineContent[i];
				cout << endl;
			};
		


			if (flag_syn == 0 || flag_syn == 5 || flag_syn == 6 || flag_syn == 7) {
				if (c == '\'') {
					if (nC == '\'' && nnC == '\'') {  //三引号字符串
						if (flag_syn == 0) {
							g_cols += 3;//指针右移两3位
							flag_syn = 5;
						}
						else if (flag_syn == 5) {
							g_cols += 2;//指针右移2位
							flag_syn = 0;
							
							//输出保存的多行字符串
							cout << "\tstring = ";
							int size = strlen(buf);
							for (int i = 0; i < size; ++i)cout << buf[i];
							cout << endl;
							return;
						}
					}
					else {//单引号字符串
						if (flag_syn == 0) {
							flag_syn = 6;
							start = g_cols - 1;//开始的位置
						}
						else if (flag_syn == 6) {
							flag_syn = 0;
							end_string(start);
							return;
						}
					}

					
				}
				else if (c == '\"') {  //双引号字符串
					if (flag_syn == 0) {
						flag_syn = 7;
						start = g_cols - 1;//开始的位置
					}
					else if (flag_syn == 7) {
						flag_syn = 0;
						end_string(start);
						return;
					}
				}
				else { //在字符串当中
					if (flag_syn == 5) {
						//把多行字符串保存下来
						buf[strlen(buf)] = c;
					}
				}
			}
			/*-------------------------------------------------------------------------------*/


			/*-----------------------操作符状态机--------------------------------------*/
			if (flag_syn == 0) {
				if (FSM_Op(c, nC, nnC))return;
			}
			/*-------------------------------------------------------------------------------*/



		}

	}


	//Node*	Lexer::factor() {
	//	return NULL;
	//}
	//Node* Lexer::term() {
	//	return NULL;
	//}
	//Node* Lexer::pow() {
	//	return NULL;
	//}
	//Node* Lexer::expr() {
	//	return NULL;
	//}
	//Node* Lexer::assign() {
	//	return NULL;
	//}



}