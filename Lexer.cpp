#include "Lexer.h"



namespace zhangqi {



	void Lexer::showAllToken(){


		//为了打印类型，定义一个数组 0-56
		const char* type[] = { "none","+","-","->","*","/","^","%","%%",".","..","...",",","=","==",
			"===","#","{","}","[","]","(",")","<","<<","<<<","<=","<=>",">",">>",">>>",">=","~",
			"~=","~==","?","&","&&","|","||","`",":","::","\\","~",";","\'","\"","\'\'\'","$","@","_","--","--[]","ID",
			"STR","NUM"
		};


		cout << "\ntokens>\n";
		int k = 0;
		TkType t;
		for (auto i : tks) {
			t = i->getType();

			cout << setw(4) << k++ << "> n = "
				<< setw(4) << i->getIndex() << ",rows = "
				<< setw(4) << i->getRows() << ", type = "
				<< setw(4) << type[ t ];

			if (t == TkType::_ID) {
				cout << ",name = " << setw(4) << i->getName();
			}
			else if (t== TkType::_STR) {
				cout << ",string = " << setw(4) << i->getString();
			}
			else if (t == TkType::_NUM) {
				cout << ",value = " << setw(4) << i->getNumber();
			}

			cout << endl;
		}
	}





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
			for (int i = _start; i < end; ++i) {
				cout << g_lineContent[i];
			}
			cout << endl;

			zqstring* id_name = zqstring_create(end - _start);
			zqstring_assign(_start, end, g_lineContent, id_name);
			tks.push_back(new Tk(g_rows,id_name->s,true));
			return true;
		}

		return false;
	}




	bool Lexer::FSM_Op(char _c, char _nC, char _nnC) {	//操作符状态机  



		switch (_c) {
		case '+':
			cout << "\top = " << CodeToStr(TkType::_PLUS) << endl;
			tks.push_back(new Tk(g_rows,TkType::_PLUS));
			return true;
		case '-':
			if (_nC == '>') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_ARROW) << endl;
				tks.push_back(new Tk(g_rows, TkType::_ARROW));
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_MINUS) << endl;
				tks.push_back(new Tk(g_rows, TkType::_MINUS));
			}
			return true;
		case '*':
			cout << "\top = " << CodeToStr(TkType::_STAR) << endl;
			tks.push_back(new Tk(g_rows, TkType::_STAR));
			return true;
		case '/':
			cout << "\top = " << CodeToStr(TkType::_SLASH) << endl;
			tks.push_back(new Tk(g_rows, TkType::_SLASH));
			return true;
		case '^':
			cout << "\top = " << CodeToStr(TkType::_CARET) << endl;
			tks.push_back(new Tk(g_rows, TkType::_CARET));
			return true;
		case '%':
			if (_nC == '%') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_MMOD) << endl;
				tks.push_back(new Tk(g_rows, TkType::_MMOD));
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_MOD) << endl;
				tks.push_back(new Tk(g_rows, TkType::_MOD));
			}
			return true;
		case '.':
			if (_nC == '.') {
				if (_nnC == '.') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_DDDOT) << endl;
					tks.push_back(new Tk(g_rows, TkType::_DDDOT));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_DDOT) << endl;
					tks.push_back(new Tk(g_rows, TkType::_DDOT));
				}
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_DOT) << endl;
				tks.push_back(new Tk(g_rows, TkType::_DOT));
			}
			return true;
		case ',':
			cout << "\top = " << CodeToStr(TkType::_COM) << endl;
			tks.push_back(new Tk(g_rows, TkType::_COM));
			return true;
		case '=':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_EEEQL);
					tks.push_back(new Tk(g_rows, TkType::_EEEQL));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_EEQL) << endl;
					tks.push_back(new Tk(g_rows, TkType::_EEQL));
				}
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_EQL) << endl;
				tks.push_back(new Tk(g_rows, TkType::_EQL));
			}
			return true;
		case '#':
			cout << "\top = " << CodeToStr(TkType::_HASH) << endl;
			tks.push_back(new Tk(g_rows, TkType::_HASH));
			return true;
		case '{':
			cout << "\top = " << CodeToStr(TkType::_LB) << endl;
			tks.push_back(new Tk(g_rows, TkType::_LB));
			return true;
		case '}':
			cout << "\top = " << CodeToStr(TkType::_RB) << endl;
			tks.push_back(new Tk(g_rows, TkType::_RB));
			return true;
		case '[':
			cout << "\top = " << CodeToStr(TkType::_LE) << endl;
			tks.push_back(new Tk(g_rows, TkType::_LE));
			return true;
		case ']':
			cout << "\top = " << CodeToStr(TkType::_RE) << endl;
			tks.push_back(new Tk(g_rows, TkType::_RE));
			return true;
		case '(':
			cout << "\top = " << CodeToStr(TkType::_LP) << endl;
			tks.push_back(new Tk(g_rows, TkType::_LP));
			return true;
		case ')':
			cout << "\top = " << CodeToStr(TkType::_RP) << endl;
			tks.push_back(new Tk(g_rows, TkType::_RP));
			return true;
		case '<':
			if (_nC == '<') {
				if (_nnC == '<') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_LLLESS) << endl;
					tks.push_back(new Tk(g_rows, TkType::_LLLESS));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_LLESS) << endl;
					tks.push_back(new Tk(g_rows, TkType::_LLESS));
				}
			}
			else if (_nC == '=') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_COMPARE) << endl;
					tks.push_back(new Tk(g_rows, TkType::_COMPARE));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_LESSEQL) << endl;
					tks.push_back(new Tk(g_rows, TkType::_LESSEQL));
				}
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_LESS) << endl;
				tks.push_back(new Tk(g_rows, TkType::_LESS));
			}
			return true;
		case '>':
			if (_nC == '>') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_GGGREAT) << endl;
					tks.push_back(new Tk(g_rows, TkType::_GGGREAT));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_GGREAT) << endl;
					tks.push_back(new Tk(g_rows, TkType::_GGREAT));
				}
			}
			else if (_nC == '=') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_GREATEQL) << endl;
				tks.push_back(new Tk(g_rows, TkType::_GREATEQL));
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_GREAT) << endl;
				tks.push_back(new Tk(g_rows, TkType::_GREAT));
			}
			return true;
		case '~':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
					cout << "\top = " << CodeToStr(TkType::_TILDEEQL) << endl;
					tks.push_back(new Tk(g_rows, TkType::_TILDEEQL));
				}
				else {
					g_cols++;//指针右移一位
					cout << "\top = " << CodeToStr(TkType::_TILDEQL) << endl;
					tks.push_back(new Tk(g_rows, TkType::_TILDEQL));
				}
			}
			else {
				cout << "\top = " << CodeToStr(TkType::_TILDE) << endl;
				tks.push_back(new Tk(g_rows, TkType::_TILDE));
			}
			return true;
		case '?':
			cout << "\top = " << CodeToStr(TkType::_QUE) << endl;
			tks.push_back(new Tk(g_rows, TkType::_QUE));
			return true;
		case '&':
			if (_nC == '&') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_AAMP) << endl;
				tks.push_back(new Tk(g_rows, TkType::_AAMP));

			}
			else {
				cout << "\top = " << CodeToStr(TkType::_AMP) << endl;
				tks.push_back(new Tk(g_rows, TkType::_AMP));

			}
			return true;
		case '|':
			if (_nC == '|') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_VVBAR);
				tks.push_back(new Tk(g_rows, TkType::_VVBAR));

			}
			else {
				cout << "\top = " << CodeToStr(TkType::_VBAR) << endl;
				tks.push_back(new Tk(g_rows, TkType::_VBAR));

			}
			return true;
		case '`':
			cout << "\top = " << CodeToStr(TkType::_GRAVE) << endl;
			tks.push_back(new Tk(g_rows, TkType::_GRAVE));
			return true;
		case ':':
			if (_nC == ':') {
				g_cols++;//指针右移一位
				cout << "\top = " << CodeToStr(TkType::_CCOLON) << endl;
				tks.push_back(new Tk(g_rows, TkType::_CCOLON));

			}
			else {
				cout << "\top = " << CodeToStr(TkType::_COLON) << endl;
				tks.push_back(new Tk(g_rows, TkType::_COLON));

			}
			return true;
		case '\\':
			cout << "\top = " << CodeToStr(TkType::_BSLASH) << endl;
			tks.push_back(new Tk(g_rows, TkType::_BSLASH));
			return true;
		case '!':
			cout << "\top = " << CodeToStr(TkType::_BANG) << endl;
			tks.push_back(new Tk(g_rows, TkType::_BANG));
			return true;
		case ';':
			cout << "\top = " << CodeToStr(TkType::_SEMI) << endl;
			tks.push_back(new Tk(g_rows, TkType::_SEMI));
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
						tks.push_back(new Tk(g_rows, v));
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
			auto end_string = [this](int _start) {

				int end = g_cols - 3;//结束的位置
				cout << "\tstring = ";
				for (int i = _start; i < end; ++i) {
					cout << g_lineContent[i];
				}
				cout << endl;

				zqstring* str = zqstring_create(end - _start);
				zqstring_assign(_start, end, g_lineContent, str);
				tks.push_back(new Tk(g_rows, str->s));

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

							zqstring* str = zqstring_create(size);
							zqstring_assign(0, size - 1, buf, str);
							tks.push_back(new Tk(g_rows, str->s));
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


	Node*	Lexer::factor() {
		return NULL;
	}
	Node* Lexer::term() {
		return NULL;
	}
	Node* Lexer::pow() {
		return NULL;
	}
	Node* Lexer::expr() {
		return NULL;
	}
	Node* Lexer::assign() {
		return NULL;
	}



}