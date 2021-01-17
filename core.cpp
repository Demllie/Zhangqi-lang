#include"Core.h"


namespace zhangqi {


	//申请一块内存
	zqstring* zqstring_create(int _len) {
		zqstring* s = (zqstring*)malloc(sizeof(zqstring) + _len);
		s->l = _len;
		return s;
	}
	//释放这块内存
	void zqstring_free(zqstring* _str) {
		_str->l = 0;
		free(_str->s);
		_str = NULL;
	}
	//赋值,把_src数组中从_start到_end的内容赋值到_dst，从头开始
	void zqstring_assign(int _start, int _end, zqstring* _src, zqstring* _dst) {
		int k = 0;
		for (int i = _start; i < _end; ++i,++k) {
			_dst[k] = _src[i];
		}
		_dst->s[k] = '\0';
	}
	//赋值,把_src数组中从_start到_end的内容赋值到_dst，从头开始
	void zqstring_assign(int _start, int _end, char* _src, zqstring* _dst) {
		int k = 0;
		for (int i = _start; i < _end; ++i, ++k) {
			_dst->s[k] = _src[i];
		}
		_dst->s[k] = '\0';
	}
	//显示
	char* zqstring_show(zqstring* _self) {
		//加一个结束标志再返回
		_self->s[_self->l] = '\0';
		return _self->s;
	}




	//输入变量的名字，返回的哈希值如果有重复，则前后变量应该是局部和全局的关系，按先后顺序使用即可
	//如果在局部作用域内定义一个重复的，那么直接按新变量处理即可，后面的的变量都是这个新的！！！
	unsigned int hash_bkdr(char* _name) {
		//unsigned int大小4个字节
		unsigned int seed = 131;//31  131  1313  13131  131313 etc..
		unsigned int hash = 0;
		for (int i = 0;_name[i]!='\0'; ++i) {  //++i在汇编下有三条指令，而i++有四条
			hash = hash * seed + _name[i];
		}
		return (hash & 0x7FFFFFFF); //7个F

	}



}