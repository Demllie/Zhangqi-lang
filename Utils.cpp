#include "Utils.h"



namespace zhangqi {

	/*--------------------------全局变量定义------------------------------*/
	char* g_file ;														//文件名
	int g_lineNumber = 1;											//行号，从1开始
	char  g_lineContent[500]	 ;									//一行的完整内容
	int  g_lineSize=0;													//g_lineContent中非空的大小
	int g_cols = 1;														//列数
	int g_rows  = 1;													//行数
	FILE* g_output = NULL;										//字节码文件
	/*---------------------------------------------------------------------------*/


	int Tk::counter = 0;

	//操作符
	Tk::Tk(int _lineN, TkType _t) {
		t = _t;
		r = _lineN;
		n = counter++;
	}
	//数字
	Tk::Tk(int _lineN, double _n) {
		t = TkType::_NUM;
		r = _lineN;
		n = counter++;
		v.v_n = _n;
	}
	//字符串
	Tk::Tk(int _lineN, char* _s)  { 
		t = TkType::_STR;
		r = _lineN;
		n = counter++; 
		v.v_s = _s;
	}
	//标识符
	Tk::Tk(int _lineN, char* _name, bool _b) { 
		t = TkType::_ID;
		r = _lineN;
		name = _name;
		n = counter++;
	}


}