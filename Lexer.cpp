#include "Lexer.h"



namespace zhangqi {



	//初始化跨文件变量
	Tk* curTk = NULL;




	void Lexer::showAllToken(){


		//为了打印类型，定义一个数组 0-56
		const char* type[] = { "none","+","-","->","*","/","^","%","%%",".","..","...",",","=","==",
			"===","#","{","}","[","]","(",")","<","<<","<<<","<=","<=>",">",">>",">>>",">=","~",
			"~=","~==","?","&","&&","|","||","`",":","::","\\","~",";","\'","\"","\'\'\'","$","@","_","--","--[]","ID",
			"STR","NUM"
		};


		cout << "\ntokens>\n";
		TkType t;
		for (auto i : tks) {
			t = i->getType();

			cout  << "> n = "
				<< setw(4) << i->getIndex() << ",rows = "
				<< setw(4) << i->getRows() << ", type = "
				<< setw(4) << type[ t ];

			if (t == TkType::_ID) {
				cout << ",name = " << setw(4) << i->getName();

				////检查一下标识符名字的实际长度和每个字符
				//cout<<"]]]";
				//int len = strlen(i->getName());
				//for (int k = 0; k < len; ++k)
				//	cout << i->getName()[k];
			}
			else if (t== TkType::_STR) {
				cout << ",string = " << setw(4);
				char* str= i->getString();
				int len = strlen(str);
				for (int k = 0; k < len; ++k) {  //多行字符串打印成一条
					if (str[k] == '\n')cout << "\\n";  //换行的\n和字符串中的\n实际是不同的，但是这么一弄显示就一样了
					else cout << str[k];
				}
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
#ifdef TEST_LEX
			cout << "\tid = ";
			for (int i = _start; i < end; ++i) {
				cout << g_lineContent[i];
			}
			cout << endl;
#endif

			zqstring* id_name = zqstring_create(end - _start);
			zqstring_assign(_start, end , g_lineContent, id_name);
			tks.push_back(new Tk(g_rows,id_name->s,true));
			return true;
		}

		return false;
	}




	bool Lexer::FSM_Op(char _c, char _nC, char _nnC) {	//操作符状态机  



		switch (_c) {
		case '+':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_PLUS) << endl;
#endif
			tks.push_back(new Tk(g_rows,TkType::_PLUS));
			return true;
		case '-':
			if (_nC == '>') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_ARROW) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_ARROW));
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_MINUS) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_MINUS));
			}
			return true;
		case '*':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_STAR) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_STAR));
			return true;
		case '/':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_SLASH) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_SLASH));
			return true;
		case '^':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_CARET) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_CARET));
			return true;
		case '%':
			if (_nC == '%') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_MMOD) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_MMOD));
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_MOD) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_MOD));
			}
			return true;
		case '.':
			if (_nC == '.') {
				if (_nnC == '.') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_DDDOT) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_DDDOT));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_DDOT) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_DDOT));
				}
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_DOT) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_DOT));
			}
			return true;
		case ',':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_COM) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_COM));
			return true;
		case '=':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_EEEQL);
#endif
					tks.push_back(new Tk(g_rows, TkType::_EEEQL));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_EEQL) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_EEQL));
				}
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_EQL) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_EQL));
			}
			return true;
		case '#':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_HASH) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_HASH));
			return true;
		case '{':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_LB) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_LB));
			return true;
		case '}':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_RB) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_RB));
			return true;
		case '[':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_LE) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_LE));
			return true;
		case ']':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_RE) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_RE));
			return true;
		case '(':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_LP) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_LP));
			return true;
		case ')':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_RP) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_RP));
			return true;
		case '<':
			if (_nC == '<') {
				if (_nnC == '<') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_LLLESS) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_LLLESS));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_LLESS) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_LLESS));
				}
			}
			else if (_nC == '=') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_COMPARE) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_COMPARE));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_LESSEQL) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_LESSEQL));
				}
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_LESS) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_LESS));
			}
			return true;
		case '>':
			if (_nC == '>') {
				if (_nnC == '>') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_GGGREAT) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_GGGREAT));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_GGREAT) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_GGREAT));
				}
			}
			else if (_nC == '=') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_GREATEQL) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_GREATEQL));
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_GREAT) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_GREAT));
			}
			return true;
		case '~':
			if (_nC == '=') {
				if (_nnC == '=') {
					g_cols += 2;//指针右移两位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_TILDEEQL) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_TILDEEQL));
				}
				else {
					g_cols++;//指针右移一位
#ifdef TEST_LEX
					cout << "\top = " << CodeToStr(TkType::_TILDEQL) << endl;
#endif
					tks.push_back(new Tk(g_rows, TkType::_TILDEQL));
				}
			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_TILDE) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_TILDE));
			}
			return true;
		case '?':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_QUE) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_QUE));
			return true;
		case '&':
			if (_nC == '&') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_AAMP) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_AAMP));

			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_AMP) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_AMP));

			}
			return true;
		case '|':
			if (_nC == '|') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_VVBAR);
#endif
				tks.push_back(new Tk(g_rows, TkType::_VVBAR));

			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_VBAR) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_VBAR));

			}
			return true;
		case '`':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_GRAVE) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_GRAVE));
			return true;
		case ':':
			if (_nC == ':') {
				g_cols++;//指针右移一位
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_CCOLON) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_CCOLON));

			}
			else {
#ifdef TEST_LEX
				cout << "\top = " << CodeToStr(TkType::_COLON) << endl;
#endif
				tks.push_back(new Tk(g_rows, TkType::_COLON));

			}
			return true;
		case '\\':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_BSLASH) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_BSLASH));
			return true;
		case '!':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_BANG) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_BANG));
			return true;
		case ';':
#ifdef TEST_LEX
			cout << "\top = " << CodeToStr(TkType::_SEMI) << endl;
#endif
			tks.push_back(new Tk(g_rows, TkType::_SEMI));
			return true;
		}

		return false;
	}

	void Lexer::FSM_End_Str(int _start) {											//单行字符串结束的收尾工作

		int end = g_cols - 3;//结束的位置
#ifdef TEST_LEX
		cout << "\tstring = ";
		for (int i = _start; i < end; ++i) {
			cout << g_lineContent[i];
		}
		cout << endl;
#endif

		zqstring* str = zqstring_create(end - _start);
		zqstring_assign(_start, end, g_lineContent, str);
		tks.push_back(new Tk(g_rows, str->s));

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
			if (c == ' ')continue;//有点问题！！！！
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
#ifdef TEST_LEX
						cout << "\tnum = " << v << endl;
#endif
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
							int size = strlen(buf);
							
							//输出保存的多行字符串
#ifdef TEST_LEX
							cout << "\tstring = ";							
							for (int i = 0; i < size; ++i)cout << buf[i];
							cout << endl;
#endif

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
							FSM_End_Str(start);
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
						FSM_End_Str(start);
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


	Tk* Lexer::getCurrentToken()const {
		if (tks.size() == 0)return NULL;
		//return tks.back();//返回最后一个
		return tks[tks.size() - 1];
	}


	

	//元素或者括号表达式
	Node* Lexer::factor() {

		if (curTk->getType() == TkType::_NUM) {
			double v = curTk->getNumber();
			next();
			curTk = getCurrentToken();
			return new NumN(v);
		}
		else if (curTk->getType() == TkType::_LP) {   //P是小括号，E是中括号，B是大括号
			next();
			curTk = getCurrentToken();
			Node* ans = expr();//获取括号内的answer

			//错误处理
			if (curTk->getType() != TkType::_RP) {
				cout << "词法分析出错，右括号不匹配！" << endl;
				exit(1);	return NULL;
			}

			next();//走之前移动一下
			curTk = getCurrentToken();
			return ans;

		}

		cout << "factor既不是数字也不是括号表达式！" << endl;
		return NULL;

	}




	//乘方表达式
	Node* Lexer::pow() {
		
		Node* v;
		Node* l = factor();//tmpTk左边
		Node* r;
		v = l;


		//暂时保存current token前两个token的类型和值,即前一个OP
		Tk tmpTk = *curTk;



		while (tmpTk.getType() == TkType::_CARET) { //^
			next();
			curTk = getCurrentToken();

			r = factor(); //tmpTk右边，此时curTk指向r右边的元素
			if (tmpTk.getType() == TkType::_CARET) {
				v = new PowN(v, r);
			}

			tmpTk = *curTk;//移动Op指针,向右移动两个
		}

		return v;
	}




	//乘除取余取模表达式
	Node* Lexer::term() {

		Node* v;
		Node* l = pow();//tmpTk左边
		Node* r;
		v = l;


		//暂时保存current token前两个token的类型和值,即前一个OP
		Tk tmpTk = *curTk;



		while (tmpTk.getType() == TkType::_STAR || tmpTk.getType() == TkType::_SLASH || tmpTk.getType() == TkType::_MOD || tmpTk.getType() == TkType::_MMOD) { //*   /    %    %%
			next();
			curTk = getCurrentToken();

			r = pow(); //tmpTk右边，此时curTk指向r右边的元素
			switch (tmpTk.getType()) {
			case TkType::_STAR:
				v = new MulN(v, r);
				break;
			case TkType::_SLASH:
				v = new DivN(v, r);
				break;
			case TkType::_MOD:
				v = new ModN(v, r);
				break;
			case TkType::_MMOD:      
				//除数为0的话，算的时候给个 Inf 无限就行了
				v = new RemN(v, r);
				break;
			}

			tmpTk = *curTk;//移动Op指针,向右移动两个
		}

		return v;
	}





	
	//加减表达式
	Node* Lexer::expr() {

		Node* v;
		Node* l = term();//tmpTk左边
		Node* r;
		v = l;


		//暂时保存current token前两个token的类型和值,即前一个OP
		Tk tmpTk = *curTk;



		while (tmpTk.getType() == TkType::_PLUS || tmpTk.getType() == TkType::_MINUS) { //+   - 
			next();
			curTk = getCurrentToken();

			r = term(); //tmpTk右边，此时curTk指向r右边的元素
			switch (tmpTk.getType()) {
			case  TkType::_PLUS:
				v = new AddN(v, r);
				break;
			case  TkType::_MINUS:
				v = new SubN(v, r);
				break;
			}

			tmpTk = *curTk;//移动Op指针,向右移动两个
		}

		return v;
	}



	//赋值表达式
	/*
	a = 1 + 2   二叉树赋值
	a,b = 1 , 2     多赋值
	a = b = c = 1    连续赋值
	*/
	Node* Lexer::assign() {
		return NULL;
	}



}