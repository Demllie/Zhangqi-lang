#include "Node.h"


namespace zhangqi {



	void TreeN::destroy() {
		if (l != NULL)l->destroy();
		if (r != NULL)r->destroy();
		l = r = NULL;
	}

	void AddN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "add");
	}
	void SubN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "sub");
	}
	void MulN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "mul");
	}
	void DivN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "div");
	}
	void PowN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "pow");
	}
	void ModN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "mod");
	}
	void RemN::visit() {
		l->visit();
		r->visit();
		fprintf(g_output, "%s\n", "rem");
	}


	void NumN::visit() {
		fprintf(g_output, "%lf\n", v);
	}


	StrN::StrN(char _s[256]) {
		
	}
	void StrN::visit() {
		
	}

	void VarN::visit() {

	}

	void VarN::destroy() {
		
	}
 

}