// This is a temporary file to test the replacement
Ident_list: Ident_list ',' ID '[' NUM ']' {
    Enter($3, VAR, level, 0, 1, $5); 
    // 배열 변수의 오프셋은 Enter 함수 내에서 arrayBaseOffset을 기반으로 설정됨
    $$ = $1 + 1;
}
	| Ident_list ',' ID	{ Enter($3, VAR, level, $1, 0, 0); $$=$1+1; }
	| ID '[' NUM ']' {
    Enter($1, VAR, level, 0, 1, $3); 
    // 배열 변수의 오프셋은 Enter 함수 내에서 arrayBaseOffset을 기반으로 설정됨
    $$ = 1;
}
	| ID 		{ Enter($1, VAR, level, 3, 0, 0); $$ = 4; }  ;