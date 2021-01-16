#include"core.h"


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
		for (int i = _start; i <= _end; ++i,++k) {
			_dst[k] = _src[i];
		}
		_dst->s[k] = '\0';
	}
	//赋值,把_src数组中从_start到_end的内容赋值到_dst，从头开始
	void zqstring_assign(int _start, int _end, char* _src, zqstring* _dst) {
		int k = 0;
		for (int i = _start; i <= _end; ++i, ++k) {
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




}