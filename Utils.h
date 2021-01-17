#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include "Core.h"





namespace zhangqi{


	/*--------------------------全局变量声明------------------------------*/
	extern char* g_file;											//文件名
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
	
	typedef enum {// _在前表示token

		//空字符
		_NONE,

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
		//字符串
		_STR,
		//数字
		_NUM

	}TkType;





	//token值定义
	typedef union {
		double v_n;
		char* v_s;	//字符串已经申请了内存，所以这里只需要传递char指针过来就行了
	}Val;




	//token
	class Tk {
	public:
		//操作符
		Tk(int _lineN, TkType _t);
		//数字
		Tk(int _lineN, double _n);
		//字符串
		Tk(int _lineN, char* _s);
		//标识符
		Tk(int _lineN, char* _name, bool _b);
		~Tk() {}

		

		void setType(TkType _t) { t = _t; }
		void setRows(int _r) { r = _r; }
		void setValue(double _n) { v.v_n = _n; }
		void setValue(char* _s) { v.v_s = _s; }




		TkType getType()const { return t; }
		int getRows()const { return r; }
		//用返回值无法区分函数，因此也无法重载
		double getNumber()const { return v.v_n; }
		char* getString()const { return v.v_s; }

		int getIndex()const { return n; }
		char* getName()const { return name; }

	private:
		static int counter;												//计数n
		int n = 0;															//第几个token,因为所有token要放入一个容器，好遍历
		int r = 1;															//行号，每个token都确定行号，这样异常信息才明确
		TkType t = TkType::_NONE;							//token类型
		char* name = NULL;										//如果是标识符的话，才有意义												
		Val v;																//如果是普通数字就可以存放数字的值，大数暂时不处理
	};

	
	/*----------------------------------------------------------------------------*/





	/*---------------------------关键字定义---------------------------------*/
	typedef enum { // _k在后表示关键字
		 IMPORT_k,				  //模块导入
		 FROM_k,				  //从什么模块中导入什么模块
		 AS_k,						  //模块名重命名

		 //分支判断
		 IF_k,
		 ELIF_k,
		 ELSE_k,
		 END_k,					      //block结束关键字

		 IN_k,							  //查看变量是否存在于数组、元组、字典、枚举中
		 FUNCTION_k,		      //函数定义关键字
		 DEF_k,					      //保留

		 WHILE_k, 				      //循环关键字，包括当型循环和直道循环
		 DO_k,						      //直到循环关键字
		 UNTIL_k,					  //while的取反，用法和while类似，条件相反
		 RETURN_k,			      //函数退出，返回变量
		 BREAK_k,				      //跳出内层循环体或者switch体
		 NEXT_k,					      //进行下一轮循环
		 EXIT_k,					      //跳出外层循环


		 //代码一般只能运行一次，但是有了下面的关键字，就能重复执行同一段代码
		 REDO_k,					  //重新开始本轮循环
		 RELOOP_k,			      //重新开始内层循环体
		 REBOOT_k,			      //重新启动当前模块

		 //true和false不是变量！
		TRUE_k,					  //数、字符串、数组、函数、元组等
		FALSE_k,				  //undefined,nil,NaN,Inf
	
		NIL_k,						  //没有赋值的数						
		NAN_k,					  //无意义的数
		INF_k,						  //无限
		UNDEFINED_k,		  //还没有定义这个变量

		LOCAL,				      //局部变量定义


		 //switch结构
		 SWITCH_k,				  //参数只能是一个变量
		  //可以是一个常数（常数这个概念通常包含字面量，即实际代码中的数字或字符串），
		  //可以是一个枚举，可以是nil,NaN,undefined,Inf
		 CASE_k,				   
		 DEFAULT_k,

		 //变量定义	  （变量包括数、函数、枚举、原型） 
		 //let和var一样
		 VAR_k,
		 LET_k,
		 CONST_k,				  //和lock类似，但是不能解锁


		 //变量锁
		 LOCK_k,						//类型和值都不能改
		 LOCK_TYPE_k,		    //类型可以改，值不能改
		 UNLOCK_k,
		 UNLOCK_TYPE_k,


		
		 //嵌入调用函数
		 INLINE_k,

		 //逻辑运算
		 AND_k,
		 OR_k,
		 NOT_k,
		 XOR_k,
		 XNOR_k,
		 NAND_k,
		 NOR_k,

		 //重命名一个block为一个变量
		 ALIAS_k,

		 //当前type实例
		 THIS_k,

		 WAIT_k,

		 //非阻塞式变量定义，只能用在when结构中
		 SET_k,
		 //触发器，小型coroutine
		 WHEN_k,

		 //自增
		 TO_k,		    
		 //自减
		 DOWNTO_k,

		 //枚举结构，枚举类型不是int，使用枚举必须是 XX::Y 这样的形式
		 ENUM_k,
		 //原型结构，可以带函数，可以直接放在别的结构体中实现 prototype 的作用
		 //用来替代class
		 TYPE_k,
		 //结构体当中的访问域定义
		 PUBLIC_k,						 //允许访问
		 PROTECTED_k,				 //允许子结构访问
		 PRIVATEk,						 //不允许直接访问

		 //文件的构造块，会首先执行这个，如果有多个，会合并
		 BIG_BEGIN_k,
		 //文件的析构块，会最后执行这……
		 BIG_END_k,

		 //复数的虚数部分，13im表示实数为0，虚数为13的复数。不存在单纯的虚数
		 IM_k,

		 //类型指定，一般是不用写类型的，如果要指定，形式是 xx:int 
		 VOID_k,
		 INT_k,
		 FLOAT_k,
		 STRING_k,

		 //命名空间。里面不能包含BEGIN{} 和END{} 块
		 NAMESPACE_k,
		 //使用命名空间
		 USING_k,
		 //导出模块，文件中可以有多个模块。但是模块中不能有BEGIN{} 和END{} 块
		 EXPORT_k,
		 //模块命名，放在一块代码的开头
		 MODULE_k,


		 //用作超大数运算和特殊进制计算
		 DEC_k,			         //DEC"123_2324_2423.3455_23E+23"
		 OCT_k,			         //OCT"70341"
		 HEX_k,			         //HEX"E_0_8_9_A"
		 BIN_k,					    //BIN"1100_0101"


		 //查看变量类型
		 TYPEOF_k,
	     //查看变量大小
		 SIZEOF_k,
		 //查看变量是否定义
		 DEFINED_k,


		 //异步线程关键字，限制函数的运行线程唯一
		 SYNCHRONIZED_k,

		 //迭代关键字
		 EACH_k
	

	}KwType;
	/*----------------------------------------------------------------------------*/



	/*---------------------------数据类型定义------------------------------*/
	/*
		Id标识符，包括var变量，kw关键字
				var变量包括num数，function函数\enum枚举,type原型等
	*/

	
	typedef enum { // _t在后表示类型
		//基本数据定义
		INT_t,
		NUM_t,						//浮点数
		COMPLEX_t,
		BOOL_t,
		STR_t,							    //一般是双引号和单引号的数据类型，三引号的预处理后也变成这样



		//大数，太大的数字也会自动转换为这种形式
		NUM10_t,							 //DEC"123_2324_2423.3455_23E+23"
		NUM8_t,								 //OCT"70341"
		NUM16_t,							 //HEX"E_0_8_9_A"
		NUM2_t,							 	 //BIN"1100_0101"

		
		FUN_t,
		ARR_t,
		DICT_t,
		ENUM_t,
		TYPE_t
	}VarType;
	/*----------------------------------------------------------------------------*/



}


#endif