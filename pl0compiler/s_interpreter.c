//#define Debug 1
#include <stdio.h>
#include <string.h>
#define cxmax 200
#define stksize 500

// 디버그 모드 활성화를 위한 전처리기 정의
#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

typedef enum { Lit, Opr, Lod, Sto, Cal, Int, Jmp, Jpc, Lda, Ldi, Sti, Out } fct;
typedef struct {
	fct f; // function code
	int l; // level
	int a; // offset
} Instruction;

int pc=0, mp=0, sp=-1;  // program, base, stacktop reg.

Instruction Code[cxmax]; // code_store indexed by pc
int s[stksize]; // data_store (stack storage) indexed by sp

// local stack frame (활성 레코드) based mp
// 	offset 0: s[mp]): SL 
// 	offset 1: s[mp+1]: DL
// 	offset 2: s[mp+2]: RA

// lod/sto l,a
//	l: level difference
//	a: offset

//	cal l,a
//	l: level difference
//	a: procedure entry pt.

int base(int l) {
	int b1;
	b1=mp; // find base l levels down
	while (l>0) {
		b1=s[b1]; --l;
	}
//	printf("base=%d\n", b1); 
	return b1;
} // end base

int odd(int a) {	
	if (a/2*2==a ) { return 0; }
	else { return 1; }
}

// 실행 추적을 위한 함수
void trace_execution(int pc, Instruction i) {
	// 명령어 실행 전에 현재 상태 출력
	DEBUG_PRINT("Executing instruction at PC=%d: ", pc);
	
	switch(i.f) {
		case Lit: DEBUG_PRINT("LIT %d\n", i.a); break;
		case Opr: 
			switch(i.a) {
				case 0: DEBUG_PRINT("OPR RET\n"); break;
				case 1: DEBUG_PRINT("OPR NEG\n"); break;
				case 2: DEBUG_PRINT("OPR ADD\n"); break;
				case 3: DEBUG_PRINT("OPR SUB\n"); break;
				case 4: DEBUG_PRINT("OPR MUL\n"); break;
				case 5: DEBUG_PRINT("OPR DIV\n"); break;
				case 6: DEBUG_PRINT("OPR ODD\n"); break;
				case 7: DEBUG_PRINT("OPR END\n"); break;
				case 8: DEBUG_PRINT("OPR EQL\n"); break;
				case 9: DEBUG_PRINT("OPR NEQ\n"); break;
				case 10: DEBUG_PRINT("OPR LSS\n"); break;
				case 11: DEBUG_PRINT("OPR GEQ\n"); break;
				case 12: DEBUG_PRINT("OPR GTR\n"); break;
				case 13: DEBUG_PRINT("OPR LEQ\n"); break;
				default: DEBUG_PRINT("OPR %d\n", i.a); break;
			}
			break;
		case Lod: DEBUG_PRINT("LOD %d,%d\n", i.l, i.a); break;
		case Sto: DEBUG_PRINT("STO %d,%d\n", i.l, i.a); break;
		case Cal: DEBUG_PRINT("CAL %d,%d\n", i.l, i.a); break;
		case Int: DEBUG_PRINT("INT %d\n", i.a); break;
		case Jmp: DEBUG_PRINT("JMP %d\n", i.a); break;
		case Jpc: DEBUG_PRINT("JPC %d\n", i.a); break;
		case Lda: DEBUG_PRINT("LDA %d,%d\n", i.l, i.a); break;
		case Ldi: DEBUG_PRINT("LDI\n"); break;
		case Sti: DEBUG_PRINT("STI\n"); break;
		case Out: DEBUG_PRINT("OUT\n"); break;
		default: DEBUG_PRINT("UNKNOWN %d\n", i.f); break;
	}
	
	// 현재 프로그램 카운터와 스택 포인터 출력
	DEBUG_PRINT("  PC=%d, SP=%d, MP=%d\n", pc, sp, mp);
}
}

// 변수 값 모니터링을 위한 함수
void monitor_variables() {
	DEBUG_PRINT("Current stack state (sp=%d, mp=%d):\n", sp, mp);
	for (int i = 0; i <= sp; i++) {
		DEBUG_PRINT("  s[%d] = %d", i, s[i]);
		// 활성 레코드 정보 출력
		if (i == mp) {
			DEBUG_PRINT(" (SL: %d)", s[i]);
		} else if (i == mp + 1) {
			DEBUG_PRINT(" (DL: %d)", s[i]);
		} else if (i == mp + 2) {
			DEBUG_PRINT(" (RA: %d)", s[i]);
		}
		DEBUG_PRINT("\n");
	}
	DEBUG_PRINT("\n");
}

void interprete() { int t;
	Instruction i; // IR reg.
	int addr=0;    

/*
// load pl0_code to Code_store 	
	while (scanf("%d %d %d %d", &addr, &i.f, &i.l, &i.a)!=EOF) {
		Code[addr]=i; // Code[addr].f, Code[addr].l, Code[addr].a
//		printf("%d   %d   %d   %d\n", addr, i.f, i.l, i.a); // pl0_code load test
	}
*/	
	printf("=== start PL0 ===\n");
	s[0]=s[1]=s[2]=0; // stack clear
	do {
		i=Code[pc++]; // fetch currrent instr.
		addr=base(i.l)+i.a; //printf("addr=%d\n", addr);
		
		// 실행 추적
		trace_execution(pc-1, i);
		
		switch (i.f) { // branch by ft. code
			case Lit: s[++sp]=i.a; break;
			case Opr: switch (i.a) {
				case 0: sp=mp-1; pc=s[sp+3]; mp=s[sp+2]; 
						break; 						// return
				case 1: s[sp]=-s[sp]; break; // negate
				case 2: --sp; s[sp]=s[sp]+s[sp+1]; break; // +
				case 3: --sp; s[sp]=s[sp]-s[sp+1]; break; // -
				case 4: --sp; s[sp]=s[sp]*s[sp+1]; break; // *
				case 5: --sp; s[sp]=s[sp]/s[sp+1]; break; // /
				case 6: s[sp]=odd(s[sp]); break; 		// odd
				case 7: pc=0; break; 					// END
				case 8: --sp; s[sp]=s[sp]==s[sp+1]; break; // =
				case 9: --sp; s[sp]=s[sp]!=s[sp+1]; break; // !=
				case 10: --sp; s[sp]=s[sp]<s[sp+1]; break; // <
				case 11: --sp; s[sp]=s[sp]>=s[sp+1]; break; // >=
				case 12: --sp; s[sp]=s[sp]>s[sp+1]; break; // >
				case 13: --sp; s[sp]=s[sp]<=s[sp+1]; break; // <=
			}; break;
			case Lod: s[++sp]=s[addr]; break;
			case Sto: s[addr]=s[sp--]; break;
			case Lda: s[++sp]=addr; break;
			case Ldi: s[sp]=s[s[sp]]; break;
			case Sti: s[s[sp-1]]=s[sp]; sp=sp-2; break;
			case Cal: s[sp+1]=base(i.l); s[sp+2]=mp; s[sp+3]=pc; mp=sp+1; pc=i.a; sp+=3; break;
			case Int: sp=sp+i.a; break;
			case Jmp: pc=i.a; break;
			case Jpc: --sp; if (s[sp+1]==0) pc=i.a;  break;
			case Out: printf("result===%d\n", s[sp--]); break;
		};
		
		// 변수 값 모니터링
		monitor_variables();
		
	} while (pc);  // loop until pc=0
	printf("=== execution result(global var. contents) ===\n");
	while (sp>2) { printf("stack:\t%d\t%d\n", sp, s[sp]); --sp;}
};

/*void main() {
	interprete();
}*/