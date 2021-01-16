#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include <stack>
#include <exception>
using namespace std;



/*------------------------------工具宏------------------------------------*/
//除此之外少用宏

//代码转字符串
#define CodeToStr(x)  #x
//输出布尔
#define BoolToStr(x)  (x?"true":"false")
//最多循环嵌套层数										   
#define MaxLoopDepth  10
//最大函数递归深度
#define MaxRecursionDepth   500


/*---------------------------------------------------------------------------*/


namespace zhangqi{


	/*--------------------------全局变量声明------------------------------*/
	extern char g_file[50];										//文件名
	extern int g_lineNumber  ;								//行号，从1开始
	extern char  g_lineContent[500];						//一行的完整内容
	extern int  g_lineSize;										//g_lineContent中非空的大小
	extern int g_cols;												//列数
	extern int g_rows;											//行数
	extern FILE* g_output;									//字节码文件


	/*---------------------------------------------------------------------------*/


	/*--------------------------Token定义-----------------------------------*/
	/*
	token枚举，因为词法分析阶段不进行运算，所以
	不给这些符号赋予具体运算的意思。而且有些符号
	有多种运算功能！

	下面的符号大致按照键盘英文命名

	*/
	typedef enum  {

		//OP
		_PLUS,							// +
		_MINUS,							// -
		_ARROW,						// ->
		_STAR,							// *
		_SLASH,						    // / 
		_CARET,						    // ^
		_MOD,							    // %
		_MMOD,							// %%
		_DOT,								// .
		_DDOT,							// ..
		_DDDOT,						    //  ...
		_COM,							    // ,
		_EQL,							    // =
		_EEQL,							// ==
		_EEEQL,						    // ===
		_HASH,							// #
		_LB,								    // {
		_RB,								// }
		_LE,								    // [
		_RE,								// ]
		_LP,								    // (
		_RP,								// )
		_LESS,							// <
		_LLESS,						    // <<
		_LLLESS,						// <<<
		_LESSEQL,						// <=
		_COMPARE,					// <=>
		_GREAT,						    // >
		_GGREAT,						// >>
		_GGGREAT,					// >>>
		_GREATEQL,					// >=
		_TILDE,							// ~
		_TILDEQL,						// ~=
		_TILDEEQL,					// ~==
		_QUE,								// ?
		_AMP,							    //&
		_AAMP,							//&&
		_VBAR,							// |
		_VVBAR,						    // ||
		_GRAVE,						    // `
		_COLON,						    // :
		_CCOLON,					    // ::
		_BSLASH,						// '\'
		_BANG,							// !
		_SEMI,							    // ;


		//STR
		_QT,								    // '
		_DQT,								// "
		_QQQT,							// '''
	
		
		//USING IN VARIABLES
		_DOLLAR,						// $
		_AT,                                 // @
		_UNDER,						    // _			CAN USED IN NUMBER AS WELL

		
		//ANNOTATION
	    _DDASH,						    // --
		_DDASHKET,				    // --[  ]				


		//标识符
		_ID,


	}TkType;




	class Tk {
	public:
		Tk(double _v) {
			v = _v;			
		}
		~Tk() {

		}

		void setType(TkType _t) { t = _t; }
		TkType getType()const { return t; }
		int getLineNumber()const { return lineN; }
		double getValue()const{ return v;}

	private:
		int lineN;	//行号，每个token都确定行号，这样异常信息才明确
		TkType t;	  //token类型
		double v=0; //如果是普通数字就可以存放数字的值，大数暂时不处理
	};




	/*----------------------------------------------------------------------------*/

	/*---------------------------关键字定义---------------------------------*/
	typedef enum {		
		 _IMPORT,				  //模块导入
		 _FROM,					  //从什么模块中导入什么模块
		 _AS,						  //模块名重命名

		 //分支判断
		 _IF,
		 _ELIF,
		 _ELSE,
		 _END,					      //block结束关键字

		 _IN,							  //查看变量是否存在于数组、元组、字典、枚举中
		 _FUNCTION,		      //函数定义关键字
		 _DEF,					      //保留

		 _WHILE,				      //循环关键字，包括当型循环和直道循环
		 _DO,						  //直到循环关键字
		 _UNTIL,					  //while的取反，用法和while类似，条件相反
		 _RETURN,			      //函数退出，返回变量
		 _BREAK,				  //跳出内层循环体或者switch体
		 _NEXT,					  //进行下一轮循环
		 _EXIT,					  //跳出外层循环


		 //代码一般只能运行一次，但是有了下面的关键字，就能重复执行同一段代码
		 _REDO,					  //重新开始本轮循环
		 _RELOOP,			      //重新开始内层循环体
		 _REBOOT,			      //重新启动当前模块

		 //true和false不是变量！
		 _TRUE,					  //数、字符串、数组、函数、元组等
		 _FALSE,				      //undefined,nil,NaN,Inf
	
		 _NIL,						  //没有赋值的数						
		 _NAN,						  //无意义的数
		 _INF,						  //无限
		 _UNDEFINED,		  //还没有定义这个变量

		 _LOCAL,				      //局部变量定义


		 //switch结构
		 _SWITCH,				  //参数只能是一个变量
		  //可以是一个常数（常数这个概念通常包含字面量，即实际代码中的数字或字符串），
		  //可以是一个枚举，可以是nil,NaN,undefined,Inf
		 _CASE,				   
		 _DEFAULT,

		 //变量定义	  （变量包括数、函数、枚举、原型） 
		 //let和var一样
		 _VAR,
		 _LET,
		 _CONST,				  //和lock类似，但是不能解锁


		 //变量锁
		 _LOCK,						//类型和值都不能改
		 _LOCK_TYPE,		    //类型可以改，值不能改
		 _UNLOCK,
		 _UNLOCK_TYPE,


		
		 //嵌入调用函数
		 _INLINE,

		 //逻辑运算
		 _AND,
		 _OR,
		 _NOT,
		 _XOR,
		 _XNOR,
		 _NAND,
		 _NOR,

		 //重命名一个block为一个变量
		 _RENAME,

		 //当前type实例
		 _THIS,

		 _WAIT,

		 //非阻塞式变量定义，只能用在when结构中
		 _SET,
		 //触发器，小型coroutine
		 _WHEN,

		 //自增
		 _TO,		    
		 //自减
		 _DOWNTO,

		 //枚举结构，枚举类型不是int，使用枚举必须是 XX::Y 这样的形式
		 _ENUM,
		 //原型结构，可以带函数，可以直接放在别的结构体中实现 prototype 的作用
		 //用来替代class
		 _TYPE,
		 //结构体当中的访问域定义
		 _PUBLIC,						 //允许访问
		 _PROTECTED,				 //允许子结构访问
		 _PRIVATE,						 //不允许直接访问

		 //文件的构造块，会首先执行这个，如果有多个，会合并
		 _BEGIN_,
		 //文件的析构块，会最后执行这……
		 _END_,

		 //复数的虚数部分，13im表示实数为0，虚数为13的复数。不存在单纯的虚数
		 _IM,

		 //类型指定，一般是不用写类型的，如果要指定，形式是 xx:int 
		 _VOID,
		 _INT,
		 _FLOAT,
		 _STRING,

		 //命名空间。里面不能包含BEGIN{} 和END{} 块
		 _NAMESPACE,
		 //使用命名空间
		 _USING,
		 //导出模块，文件中可以有多个模块。但是模块中不能有BEGIN{} 和END{} 块
		 _EXPORT,
		 //模块命名，放在一块代码的开头
		 _MODULE,


		 //用作超大数运算和特殊进制计算
		 _DEC_,			         //DEC"123_2324_2423.3455_23E+23"
		 _OCT_,			         //OCT"70341"
		 _HEX_,			         //HEX"E_0_8_9_A"
		 _BIN_,			         //BIN"1100_0101"


		 //查看变量类型
		 _TYPEOF,
	     //查看变量大小
		 _SIZEOF,
		 //查看变量是否定义
		 _DEFINED,


		 //异步线程关键字，限制函数的运行线程唯一
		 _SYNCHRONIZED,

		 //迭代关键字
		 _EACH,
	

	}KwType;
	/*----------------------------------------------------------------------------*/

	/*---------------------------数据类型定义------------------------------*/
	/*
		Id标识符，包括var变量，kw关键字
				var变量包括num数，function函数\enum枚举,type原型等
	*/

	typedef enum {
		//基本数据定义
		_INTEGER,
		_NUMBER,
		_COMPLEX,
		_BOOL,
		_STR,							    //一般是双引号和单引号的数据类型，三引号的预处理后也变成这样

		//大数，太大的数字也会自动转换为这种形式
		_NUM10,
		_NUM8,
		_NUM2,
		_NUM16,


		_FUN,
		_ARR,
		_TUPLE,
		_DICT,
		_ENU,
		_TYP,
	}VarType;


	/*----------------------------------------------------------------------------*/



}


#endif