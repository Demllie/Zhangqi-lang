#include "Node.h"


namespace zhangqi {



	void TreeN::destroy() {

		auto judge = [](Node* _n) {
			if (_n != NULL) {
				if (_n->getType() != NodeType::N_Literal)	_n->destroy();
				else {
					delete _n;
				}
				_n = NULL;
			}
		};

		judge(l);
		judge(r);
	
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
		fprintf(g_output, "ld %lf\n", v);
	}


	
	void StrN::visit() {
		fprintf(g_output, "ld %s\n", s);
	}


	VarN::VarN(char* _s) {
		name = _s;
		hash = hash_bkdr(_s);
	}

	void VarN::visit() {
		fprintf(g_output, "%\n", name);
	}

	
}