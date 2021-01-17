#include "Lexer.h"
using namespace zhangqi;


/*
统计代码行数
CTRL+SHIFT+F

^(?!(\s*\*))(?!(\s*\-\-\>))(?!(\s*\<\!\-\-))(?!(\s*\n))(?!(\s*\*\/))(?!(\s*\/\*))(?!(\s*\/\/\/))(?!(\s*\/\/))(?!(\s*\}))(?!(\s*\{))(?!(\s(using))).*$


使用正则表达式匹配
文件类型		*.cpp;*.h
*/
int main(void) {

	FILE* file = NULL;
	int a = fopen_s(&file, "test.txt", "r");
	if (a != 0) {
		cout << "文件test.txt打不开!" << endl;
		return 1;
	}
	int b = fopen_s(&g_output, "output.txt", "w+");
	if (b != 0) {
		cout << "文件output.txt打不开!" << endl;
		return 1;
	}




	char* flag;
	Lexer lex;
	Node* root=NULL;



#ifdef TEST_LEX
	cout << "program>" << endl;
#endif


	while (  (flag = fgets(g_lineContent, 500, file))   !=NULL ){  //最后一行为空的话会读不到
		g_lineSize = strlen(g_lineContent);

		//词法分析阶段的测试宏
#ifdef TEST_LEX
		cout << setw(4) <<g_rows ++  << ">" << g_lineContent;		
#endif

		g_cols = 1;//初始化列数
		while (g_cols < g_lineSize + 1) {  //词法分析一整行的token

			lex.next();//每次返回表示获取了一个token
			curTk = lex.getCurrentToken();
			if (curTk == NULL) {
				cout << "空行" << endl;
				break;
			}
			root = lex.expr();;//获取AST抽象语法树
			root->visit();

		}
	}

	
	delete root;//删除抽象语法树
	return 0;
}
