#pragma once
#ifndef _CORE_H_
#define _CORE_H_
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



namespace zhangqi {


	/*---------------------------0宽数组定义------------------------------*/
	typedef struct {
		int l;
		char s[0];  //0宽数组中这个变量不会占用空间
	}zqstring;
	
	//申请一块内存
	zqstring* zqstring_create(int _len);
	//释放这块内存
	void zqstring_free(zqstring* _str);
	//赋值,把_src数组中从_start到_end的内容赋值到_dst，从头开始
	void zqstring_assign(int _start, int _end, zqstring* _src, zqstring* _dst);
	//赋值,把_src数组中从_start到_end的内容赋值到_dst，从头开始
	void zqstring_assign(int _start, int _end, char* _src, zqstring* _dst);
	//显示
	char* zqstring_show(zqstring* _self);

	/*---------------------------------------------------------------------------*/




}
#endif

