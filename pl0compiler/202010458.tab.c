/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "202010458.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_interpreter_debug.c"
FILE *fp;
void yyerror(char*);
int yylex();

#define CONST 	0
#define VAR 	1
#define PROC 	2
#define IDENT 	3  /* CONST + VAR */

#define TBSIZE 100	// symbol table size
#define LVLmax 20		// max. level depth
#define HASHSIZE 7
#define MAX_OFFSET 100

struct {
	// symbol table
	char name[20];	/*변수 이름*/
	int type;		/* 0-CONST	1-VARIABLE	2-PROCEDURE */
	int lvl;	/*변수의 level*/
	int offst;	/*offset 값*/
	int dimension;	/*0-var	1-array*/
	int length;		/*배열 길이*/
	int link;		/*backward chain에 쓸 link*/
	int param_count; /*매개변수 개수 (PROCEDURE에만 사용)*/
	int line;       /*선언된 행 번호*/
	} table[TBSIZE];



int hashBucket[HASHSIZE]; // 해시 버켓
int leveltable[LVLmax]; // 레벨 테이블
int arrayBaseOffset = MAX_OFFSET;
	
int block[LVLmax]; 	// Data for Set/Reset symbol table
typedef struct { // address format
	int l;
	int a;
	} Addr;

int Lookup(char *, int);  // lookup sym name for type, 
		      // if found setup LDiff/OFFSET and return 1 else return 0
void Enter(char *, int, int, int, int, int); // symbol insert
void SetBlock();
void ResetBlock();
void DisplayTable(); // symbol table dump
int GenLab(char *);	// label 생성(번호와 label) 및 현재 코드주소 저장
void EmitLab(int);	// label 출력 및 forward jump 주소 확정
void EmitLab1(int);	// label 출력 및 backward jump 주소 저장
void EmitPname(char *label);	// procedure 이름 출력
void Emit1(char *, fct, int, int);  // INT, LOD, LIT, STO 코드생성
void Emit2(char *, int, char *);  // CAL 코드생성
void Emit3(char *, fct, int);	// jmp, jpc 코드 생성
void Emit(char *, int);	// opr 코드생성
void EmitOut(char *, fct); // Out 코드 생성
int HashFunction(char *);
void InitializeSymbolTable();

int ln=1, cp=0;
int lev=0;
int tx=0; // stack smbol table top pt.
int level=0; // block nesting level
int cdx=0; // code addr
int LDiff=0, OFFSET=0; // nesting level diff, offset(상대주소)
int Lno=0;
int avail=0; // 해시 구조에서 현재 사용할 테이블 index
char Lname[10]; // 생성된 label
int Lab[20]; // 새로 생성된 label 에 대한 코드주소 저장(테이블)


/* Line 189 of yacc.c  */
#line 148 "202010458.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TCONST = 258,
     TVAR = 259,
     TPROC = 260,
     TCALL = 261,
     TBEGIN = 262,
     TIF = 263,
     TTHEN = 264,
     TWHILE = 265,
     TDO = 266,
     TEND = 267,
     ODD = 268,
     NE = 269,
     LE = 270,
     GE = 271,
     ASSIGN = 272,
     TWRITE = 273,
     ID = 274,
     NUM = 275,
     UM = 276
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 77 "202010458.y"

	char ident[50];	// id lvalue
	int number;	// num lvalue
	


/* Line 214 of yacc.c  */
#line 212 "202010458.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 224 "202010458.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      23,    24,    28,    26,    25,    27,    31,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      34,    33,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    21,     2,    22,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,     8,    13,    17,    18,    22,
      28,    32,    36,    37,    44,    48,    53,    55,    58,    59,
      60,    65,    69,    70,    78,    82,    85,    89,    90,    96,
      97,    98,   105,   111,   114,   116,   117,   121,   123,   126,
     130,   134,   138,   142,   146,   150,   154,   158,   161,   164,
     166,   170,   174,   176,   181,   183,   185
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    31,    -1,    -1,    -1,    39,    41,
      40,    50,    -1,    42,    44,    46,    -1,    -1,     3,    43,
      32,    -1,    43,    25,    19,    33,    20,    -1,    19,    33,
      20,    -1,     4,    45,    32,    -1,    -1,    45,    25,    19,
      21,    20,    22,    -1,    45,    25,    19,    -1,    19,    21,
      20,    22,    -1,    19,    -1,    46,    47,    -1,    -1,    -1,
      49,    48,    38,    32,    -1,     5,    19,    32,    -1,    -1,
      19,    21,    57,    22,    51,    17,    57,    -1,    19,    17,
      57,    -1,     6,    19,    -1,     7,    55,    12,    -1,    -1,
       8,    56,    52,     9,    50,    -1,    -1,    -1,    10,    53,
      56,    54,    11,    50,    -1,    18,    19,    21,    57,    22,
      -1,    18,    19,    -1,     1,    -1,    -1,    55,    32,    50,
      -1,    50,    -1,    13,    57,    -1,    57,    33,    57,    -1,
      57,    14,    57,    -1,    57,    34,    57,    -1,    57,    35,
      57,    -1,    57,    16,    57,    -1,    57,    15,    57,    -1,
      57,    26,    58,    -1,    57,    27,    58,    -1,    26,    58,
      -1,    27,    58,    -1,    58,    -1,    58,    28,    59,    -1,
      58,    29,    59,    -1,    59,    -1,    19,    21,    57,    22,
      -1,    19,    -1,    20,    -1,    23,    57,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    95,    96,    95,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     111,   112,   113,   113,   126,   127,   128,   129,   129,   131,
     132,   131,   134,   144,   145,   146,   148,   149,   152,   153,
     154,   155,   156,   157,   158,   159,   177,   195,   196,   206,
     208,   228,   253,   254,   265,   277,   282
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TCONST", "TVAR", "TPROC", "TCALL",
  "TBEGIN", "TIF", "TTHEN", "TWHILE", "TDO", "TEND", "ODD", "NE", "LE",
  "GE", "ASSIGN", "TWRITE", "ID", "NUM", "'['", "']'", "'('", "')'", "','",
  "'+'", "'-'", "'*'", "'/'", "UM", "'.'", "';'", "'='", "'<'", "'>'",
  "$accept", "Program", "Block", "@1", "$@2", "Dcl", "ConstDcl",
  "Constdef_list", "VarDcl", "Ident_list", "ProcDef_list", "ProcDef",
  "$@3", "ProcHead", "Statement", "$@4", "@5", "@6", "@7",
  "Statement_list", "Condition", "Expression", "Term", "Factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    91,    93,    40,    41,    44,    43,    45,    42,    47,
     276,    46,    59,    61,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    39,    40,    38,    41,    42,    42,    43,
      43,    44,    44,    45,    45,    45,    45,    46,    46,    48,
      47,    49,    51,    50,    50,    50,    50,    52,    50,    53,
      54,    50,    50,    50,    50,    50,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      58,    58,    58,    59,    59,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     4,     3,     0,     3,     5,
       3,     3,     0,     6,     3,     4,     1,     2,     0,     0,
       4,     3,     0,     7,     3,     2,     3,     0,     5,     0,
       0,     6,     5,     2,     1,     0,     3,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       3,     3,     1,     4,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     7,     1,     2,     0,     4,    12,     0,
       0,     0,     0,    18,     0,     0,     8,    34,     0,     0,
       0,    29,     0,     0,     5,    16,     0,     6,    10,     0,
      25,    37,     0,     0,    54,    55,     0,     0,     0,    27,
       0,    49,    52,     0,    33,     0,     0,     0,     0,    11,
       0,    17,    19,     0,    26,     0,    38,     0,     0,    47,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    24,     0,     0,    14,     0,     3,
       9,    36,     0,    56,     0,    40,    44,    43,    45,    46,
      39,    41,    42,    50,    51,     0,     0,    22,    15,     0,
      21,     0,    53,    28,     0,    32,     0,     0,    20,    31,
       0,    13,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,    11,     7,     8,    10,    13,    26,
      27,    51,    79,    52,    24,   106,    61,    43,    95,    32,
      39,    40,    41,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -31
static const yytype_int8 yypact[] =
{
     -31,    10,   -14,    20,   -31,   -31,    16,   -31,    52,    17,
     -23,    68,    58,   -31,    59,    64,   -31,   -31,    65,    12,
      92,   -31,    69,    31,   -31,    74,   -18,    89,   -31,    70,
     -31,   -31,   -11,   -15,    76,   -31,   -15,    73,    73,   -31,
      75,     0,   -31,    92,    77,   -15,   -15,    84,    87,   -31,
      88,   -31,   -31,    93,   -31,    12,    15,   -15,    37,     0,
       0,   105,   -15,   -15,   -15,    73,    73,   -15,   -15,   -15,
      73,    73,   -31,   -15,    15,    33,    94,    96,    90,   -31,
     -31,   -31,    40,   -31,    39,    15,    15,    15,     0,     0,
      15,    15,    15,   -31,   -31,   109,    46,   -31,   -31,   101,
     -31,    91,   -31,   -31,    39,   -31,   107,   103,   -31,   -31,
     -15,   -31,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,    47,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -19,   -31,   -31,   -31,   -31,   -31,
      85,   -30,   -12,    11
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -36
static const yytype_int8 yytable[] =
{
      31,    54,    15,    56,    34,    35,    58,    48,    36,    16,
       4,    37,    38,    17,    49,    74,    75,     5,    18,    19,
      20,    55,    21,     6,   -35,    59,    60,    82,    70,    71,
      22,    23,    85,    86,    87,     9,    81,    90,    91,    92,
      17,    65,    66,    96,   -35,    18,    19,    20,    45,    21,
      14,   -35,    46,    88,    89,    97,    12,    22,    23,    65,
      66,    83,   102,    65,    66,   103,    65,    66,   105,    17,
     -35,   -35,    65,    66,    18,    19,    20,    25,    21,    28,
     112,    93,    94,    29,    30,   109,    22,    23,    44,    62,
      63,    64,    34,    35,    50,    47,    36,    57,    73,   -35,
     -35,    65,    66,    53,    76,    33,    77,    78,    67,    68,
      69,    34,    35,    80,    84,    36,    98,    99,    37,    38,
     104,   107,   100,   108,   110,   111,   101,     0,    72
};

static const yytype_int8 yycheck[] =
{
      19,    12,    25,    33,    19,    20,    36,    25,    23,    32,
       0,    26,    27,     1,    32,    45,    46,    31,     6,     7,
       8,    32,    10,     3,    12,    37,    38,    57,    28,    29,
      18,    19,    62,    63,    64,    19,    55,    67,    68,    69,
       1,    26,    27,    73,    32,     6,     7,     8,    17,    10,
      33,    12,    21,    65,    66,    22,     4,    18,    19,    26,
      27,    24,    22,    26,    27,    84,    26,    27,    22,     1,
      31,    32,    26,    27,     6,     7,     8,    19,    10,    20,
     110,    70,    71,    19,    19,   104,    18,    19,    19,    14,
      15,    16,    19,    20,     5,    21,    23,    21,    21,    31,
      32,    26,    27,    33,    20,    13,    19,    19,    33,    34,
      35,    19,    20,    20,     9,    23,    22,    21,    26,    27,
      11,    20,    32,    32,    17,    22,    79,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    39,     0,    31,     3,    41,    42,    19,
      43,    40,     4,    44,    33,    25,    32,     1,     6,     7,
       8,    10,    18,    19,    50,    19,    45,    46,    20,    19,
      19,    50,    55,    13,    19,    20,    23,    26,    27,    56,
      57,    58,    59,    53,    19,    17,    21,    21,    25,    32,
       5,    47,    49,    33,    12,    32,    57,    21,    57,    58,
      58,    52,    14,    15,    16,    26,    27,    33,    34,    35,
      28,    29,    56,    21,    57,    57,    20,    19,    19,    48,
      20,    50,    57,    24,     9,    57,    57,    57,    58,    58,
      57,    57,    57,    59,    59,    54,    57,    22,    22,    21,
      32,    38,    22,    50,    11,    22,    51,    20,    32,    50,
      17,    22,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 94 "202010458.y"
    {  Emit("END", 7); printf("\n ==== valid syntax ====\n"); ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 95 "202010458.y"
    { Emit3("JMP", Jmp, (yyval.number)=GenLab(Lname) ); ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 96 "202010458.y"
    { EmitLab((yyvsp[(1) - (2)].number)); Emit1("INT", Int, 0, (yyvsp[(2) - (2)].number)); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 97 "202010458.y"
    { DisplayTable(); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 98 "202010458.y"
    { (yyval.number)=(yyvsp[(2) - (3)].number); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 101 "202010458.y"
    { Enter((yyvsp[(3) - (5)].ident), CONST, level, (yyvsp[(5) - (5)].number), 0, 0);	 ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 102 "202010458.y"
    { Enter((yyvsp[(1) - (3)].ident), CONST, level, (yyvsp[(3) - (3)].number), 0, 0); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 103 "202010458.y"
    { (yyval.number)=(yyvsp[(2) - (3)].number);	 ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 104 "202010458.y"
    { (yyval.number)=3; ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 105 "202010458.y"
    {	Enter((yyvsp[(3) - (6)].ident), VAR, level, arrayBaseOffset, 1, (yyvsp[(5) - (6)].number)); (yyval.number) = (yyvsp[(1) - (6)].number) + 1;	;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 106 "202010458.y"
    { Enter((yyvsp[(3) - (3)].ident), VAR, level, (yyvsp[(1) - (3)].number), 0, 0); (yyval.number)=(yyvsp[(1) - (3)].number)+1; ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 107 "202010458.y"
    {	Enter((yyvsp[(1) - (4)].ident), VAR, level, arrayBaseOffset, 1, (yyvsp[(3) - (4)].number)); (yyval.number)=1;	;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 108 "202010458.y"
    { Enter((yyvsp[(1) - (1)].ident), VAR, level, 3, 0, 0); (yyval.number)=4; ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 111 "202010458.y"
    { SetBlock(); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 111 "202010458.y"
    { Emit("RET", 0); ResetBlock(); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 112 "202010458.y"
    { Enter((yyvsp[(2) - (3)].ident), PROC, level, cdx, 0, 0); EmitPname((yyvsp[(2) - (3)].ident)); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 113 "202010458.y"
    {
    if (Lookup((yyvsp[(1) - (4)].ident), VAR)) {
        // 인덱스 Expression(`i`)이 이미 평가되어 스택에 푸시됨
        // 배열의 기본 주소를 로드하고, 인덱스를 더함
        Emit1("LDA", Lda, LDiff, OFFSET); // base address 푸시 (100)
        Emit("ADD", 2); // base + i 계산, 스택에 푸시
    }
;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 120 "202010458.y"
    {
    if (Lookup((yyvsp[(1) - (7)].ident), VAR)) {
        // 할당할 값 Expression(`expr`)이 이미 평가되어 스택에 푸시됨
        Emit1("STI", Sti, 0, 0);           // `expr` 값을 `base + i` 주소에 저장
    }
;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 126 "202010458.y"
    { Lookup((yyvsp[(1) - (3)].ident), VAR); Emit1("STO", Sto, LDiff, OFFSET); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 127 "202010458.y"
    { 	Lookup((yyvsp[(2) - (2)].ident), PROC); Emit2("CAL", LDiff, (yyvsp[(2) - (2)].ident));	 ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 129 "202010458.y"
    { 	Emit3("JPC", Jpc, (yyval.number)=GenLab(Lname));	 ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 130 "202010458.y"
    { 	EmitLab((yyvsp[(3) - (5)].number));	 ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 131 "202010458.y"
    { EmitLab1((yyval.number)=GenLab(Lname) ); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 132 "202010458.y"
    { Emit3("JPC", Jpc, (yyval.number)=GenLab(Lname)); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 133 "202010458.y"
    { Emit3("JMP", Jmp, (yyvsp[(2) - (6)].number)); EmitLab((yyvsp[(4) - (6)].number)); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 134 "202010458.y"
    {
    	if (Lookup((yyvsp[(2) - (5)].ident), VAR)) {
        	Emit1("LDA", Lda, LDiff, OFFSET);
			Emit("ADD", 2);
        	Emit1("LDI", Ldi, 0, 0);
        	EmitOut("OUT", Out);
	    } else {
        	fprintf(stderr, "Error: '%s' is not declared as an array.\n", (yyvsp[(2) - (5)].ident));
    	}
;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 144 "202010458.y"
    { Lookup((yyvsp[(2) - (2)].ident),VAR); Emit1("LOD", Lod, LDiff, OFFSET); EmitOut("OUT",Out); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 145 "202010458.y"
    {  yyerrok; ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 152 "202010458.y"
    { 	Emit("ODD",6);	 ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 153 "202010458.y"
    {  Emit("EQL",8);	;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 154 "202010458.y"
    {  Emit("NE", 9);    ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 155 "202010458.y"
    { 	Emit("LSS",10);	 ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 156 "202010458.y"
    { 	Emit("GTR",12);	;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 157 "202010458.y"
    { 	Emit("GEQ", 11);	;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 158 "202010458.y"
    { 	Emit("LEQ", 13);	;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 159 "202010458.y"
    { 
    // 상수 + 상수인 경우 최적화
    if (Code[cdx-2].f == Lit && Code[cdx-1].f == Lit) {
        int val1 = Code[cdx-2].a;
        int val2 = Code[cdx-1].a;
        cdx -= 2; // 이전 두 명령어 제거
        // 덧셈 최적화: 0 + x = x, x + 0 = x
        if (val1 == 0) {
            Emit1("LIT", Lit, 0, val2); // 0 + x = x
        } else if (val2 == 0) {
            Emit1("LIT", Lit, 0, val1); // x + 0 = x
        } else {
            Emit1("LIT", Lit, 0, val1 + val2); // 일반적인 덧셈
        }
    } else {
        Emit("ADD", 2);
    }
;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 177 "202010458.y"
    {
    // 상수 - 상수인 경우 최적화
    if (Code[cdx-2].f == Lit && Code[cdx-1].f == Lit) {
        int val1 = Code[cdx-2].a;
        int val2 = Code[cdx-1].a;
        cdx -= 2; // 이전 두 명령어 제거
        // 뺄셈 최적화: x - 0 = x, 0 - x = -x
        if (val2 == 0) {
            Emit1("LIT", Lit, 0, val1); // x - 0 = x
        } else if (val1 == 0) {
            Emit1("LIT", Lit, 0, -val2); // 0 - x = -x
        } else {
            Emit1("LIT", Lit, 0, val1 - val2); // 일반적인 뺄셈
        }
    } else {
        Emit("SUB", 3);
    }
;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 196 "202010458.y"
    { 
        // 단항 마이너스 최적화: 상수인 경우 직접 계산
        if (Code[cdx-1].f == Lit) {
            int val = Code[cdx-1].a;
            cdx -= 1; // 이전 명령어 제거
            Emit1("LIT", Lit, 0, -val); // 최적화된 결과 푸시
        } else {
            Emit("NEG", 1);
        }
    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 208 "202010458.y"
    {
    // 상수 * 상수인 경우 최적화
    if (Code[cdx-2].f == Lit && Code[cdx-1].f == Lit) {
        int val1 = Code[cdx-2].a;
        int val2 = Code[cdx-1].a;
        cdx -= 2; // 이전 두 명령어 제거
        // 곱셈 최적화: 0 * x = 0, x * 0 = 0, 1 * x = x, x * 1 = x
        if (val1 == 0 || val2 == 0) {
            Emit1("LIT", Lit, 0, 0); // 0 * 어떤 수든 0
        } else if (val1 == 1) {
            Emit1("LIT", Lit, 0, val2); // 1 * x = x
        } else if (val2 == 1) {
            Emit1("LIT", Lit, 0, val1); // x * 1 = x
        } else {
            Emit1("LIT", Lit, 0, val1 * val2); // 일반적인 곱셈
        }
    } else {
        Emit("MUL", 4);
    }
;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 228 "202010458.y"
    {
    // 상수 / 상수인 경우 최적화
    if (Code[cdx-2].f == Lit && Code[cdx-1].f == Lit) {
        int val1 = Code[cdx-2].a;
        int val2 = Code[cdx-1].a;
        // 0으로 나누는 경우 처리
        if (val2 == 0) {
            fprintf(stderr, "Error: Division by zero at line %d, column %d\n", ln, cp);
            // 일반적인 DIV 명령어로 처리하여 런타임에 오류 발생시키기
            Emit("DIV", 5);
        } else {
            cdx -= 2; // 이전 두 명령어 제거
            // 나눗셈 최적화: 0 / x = 0 (x != 0), x / 1 = x
            if (val1 == 0) {
                Emit1("LIT", Lit, 0, 0); // 0 / 어떤 수든 0 (단, 0으로 나누는 경우는 이미 위에서 처리됨)
            } else if (val2 == 1) {
                Emit1("LIT", Lit, 0, val1); // x / 1 = x
            } else {
                Emit1("LIT", Lit, 0, val1 / val2); // 일반적인 나눗셈
            }
        }
    } else {
        Emit("DIV", 5);
    }
;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 254 "202010458.y"
    { 
		if (Lookup((yyvsp[(1) - (4)].ident), VAR)) {
		    // 인덱스 Expression(`i`)이 이미 평가되어 스택에 푸시됨
		    // 배열의 기본 주소를 로드하고, 인덱스를 더함
		    Emit1("LDA", Lda, LDiff, OFFSET); // base address 푸시 (100)
		    Emit("ADD", 2); // base + i 계산, 스택에 푸시
		    
		    // 중복된 LDA, ADD 명령어 제거를 위한 최적화 (간단한 형태)
		    // 실제로는 더 복잡한 최적화가 필요하지만, 기본적인 형태만 구현
		}
	;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 265 "202010458.y"
    { 
        /* ID lookup 결과로 LOD 또는 LIT 코드 생성 */
        if (Lookup((yyvsp[(1) - (1)].ident), VAR)) {
            Emit1("LOD", Lod, LDiff, OFFSET);
        } else if (Lookup((yyvsp[(1) - (1)].ident), CONST)) {
            // CONST인 경우 LIT 명령어로 직접 값 푸시
            Emit1("LIT", Lit, 0, OFFSET);
        } else {
            // 심볼이 없는 경우 오류 처리
            fprintf(stderr, "Error: Undefined symbol '%s'\n", (yyvsp[(1) - (1)].ident));
        }
	;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 277 "202010458.y"
    { 
        // 중복된 LIT 명령어 제거를 위한 최적화
        // 이전 명령어가 LIT이고, 현재도 LIT인 경우 병합하지 않음 (스택에 순차적으로 푸시해야 함)
        Emit1("LIT", Lit, 0, (yyvsp[(1) - (1)].number)); 
    ;}
    break;



/* Line 1464 of yacc.c  */
#line 1953 "202010458.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 284 "202010458.y"

#include "lex.yy.c"
void yyerror(char* s) {
	fprintf(stderr, "Error at line %d, column %d: %s\n", ln, cp, s);
}
int Lookup(char *name, int type) {
	// 심볼 검색후 찾으면 LDiff(level diff)와 OFFSET(상대주소)를 지정하고 1을 리턴
	// 없으면 0을 리턴
    int hashIndex = HashFunction(name);  // 해시 값 계산
    int idx = hashBucket[hashIndex];    // 해당 해시 버킷의 첫 번째 심볼 인덱스
    LDiff = -1; OFFSET = -1;

    // Backward Chain을 따라 검색
    while (idx != -1) {
        if (strcmp(table[idx].name, name) == 0) {  // 이름 일치
            LDiff = level - table[idx].lvl;       // 레벨 차이 계산
            OFFSET = table[idx].offst;           // 오프셋 설정
            if (table[idx].type == type) {       // 타입 일치 여부 확인
                return 1;  // 심볼 찾음
            } else {
                return 0;  // 이름은 같지만 타입 불일치
            }
        }
        idx = table[idx].link;  // 다음 노드로 이동
    }

    return 0;  // 심볼을 찾지 못함
}

void InitializeSymbolTable() {
    for (int i = 0; i < HASHSIZE; i++) {
        hashBucket[i] = -1;  // -1로 초기화하여 비어 있음을 나타냄
    }
	for (int i = 0; i < LVLmax; i++) {
        leveltable[i] = -1;  // 각 레벨의 시작 인덱스 초기화
    }
}


int HashFunction(char *name){
	unsigned int hash = 0;
	while (*name) {
        hash = (hash * 31) + *name;  // 31은 적당한 소수로, 충돌을 줄이는 데 유용
        name++;
    }
    return hash % HASHSIZE;
}

void Enter(char *name, int type, int lvl, int offst, int dimension, int length) {
    int hashIndex = HashFunction(name); // 해시 버켓 인덱스
    int idx = hashBucket[hashIndex];   // 해시 버켓에 담겨있는 심볼 테이블 인덱스

    // 현재 레벨의 첫 심볼 인덱스 기록
    if (leveltable[level] == -1) {
        leveltable[level] = avail;
    }

    // 중복 심볼 검사
    while (idx != -1) {
        if (strcmp(table[idx].name, name) == 0 && table[idx].lvl == lvl) {
            fprintf(stderr, "Error: Duplicate symbol '%s' at level %d. Previous declaration was at line %d\n", 
                    name, lvl, table[idx].line);
            return;  // 중복 심볼 발견 시 추가하지 않고 종료
        }
        idx = table[idx].link;  // 다음 연결된 노드
    }

    // 심볼 테이블에 심볼 정보 저장
    strcpy(table[avail].name, name);
    table[avail].type = type;
    table[avail].lvl = lvl;
    table[avail].dimension = dimension;
    table[avail].length = (dimension == 1) ? length : 0;
    table[avail].line = ln;  // 현재 행 번호 저장
    
    // 배열일 경우 오프셋 처리 개선
    if (dimension == 1) {
        table[avail].offst = arrayBaseOffset;
        arrayBaseOffset += length;  // 배열 크기만큼 오프셋 증가
        fprintf(stderr, "Info: Array '%s' declared with offset %d and length %d\n", 
                name, table[avail].offst, length);
    } else {
        table[avail].offst = offst;
    }

    // PROCEDURE인 경우 매개변수 개수 초기화
    if (type == PROC) {
        table[avail].param_count = 0;
    }

    // Backward Chain 설정
    table[avail].link = hashBucket[hashIndex];  // 이전 심볼과 연결
    hashBucket[hashIndex] = avail;             // 현재 심볼을 버킷의 맨 앞에 추가

    ++avail;  // 다음 사용 가능한 인덱스로 이동
}


void SetBlock() {
	block[level++]=avail;
	}

void ResetBlock() { 
	int idx=block[--level];
	if(idx !=-1){
		for(int i = idx; i <avail;i++){
			int hashIndex = HashFunction(table[i].name);
			if(hashBucket[hashIndex]==i){
				hashBucket[hashIndex]=table[i].link;
			}
		}
		avail=idx;
		leveltable[level]=-1;
	}
	}

void DisplayTable() {
	int idx=avail;
	printf("\n======== sym tbl contents ==========\n");
	
    while (--idx>=0) { // 역순으로 출력
        printf("%s  %d  %d  %d	", 
               table[idx].name, 
               table[idx].type, 
               table[idx].lvl,
			   table[idx].link);

        if (table[idx].dimension == 0) {
            printf("OFFSET: %d\n", table[idx].offst);
        } else {
            printf("ARRAY ADDRESS: %d | LENGTH: %d\n", 
                	table[idx].offst, 
                   table[idx].length);
        }
    }
    printf("---------------------------------------------------\n");
}



int GenLab(char *label) {
	Lab[Lno]=cdx;	// save code addr. for backward jump
	sprintf(label, "LAB%d", Lno);
	return Lno++;
}
void EmitLab(int label) {	// resolve forward jump label
	Code[Lab[label]].a=cdx; // fixed up forward jump label
	printf("LAB%d\n", label);
}
void EmitLab1(int label) {
	Lab[label]=cdx; /* GenLab() 에서 시행 */
	printf("LAB%d\n", label);
}
void EmitPname(char *label) {
	printf("%s\n", label);
}
void Emit1(char *code, fct op, int ld, int offst) {   // INT, LOD, LIT, STO 코드생성, ld: level_diff.
	Instruction i;
	printf("%d	%s	%d	%d\n", cdx, code, ld, offst);
	i.f=op; i.l=ld; i.a=offst;
	Code[cdx++]=i;
}
void Emit2(char *code, int ld, char *name) {	// CAL 코드생성, ld: level_diff., OFFSET:code_addr.
	Instruction i;
	printf("%d	%s	%d	%s\n", cdx, code, ld, name);
	i.f=Cal; i.l=ld; i.a=OFFSET; // ld: level_diff.
	Code[cdx++]=i;
}
void Emit3(char *code, fct op, int label) {  // jmp, jpc 코드생성
	Instruction i;
	printf("%d	%s	LAB%d\n", cdx, code, label);
	i.f=op; i.l=0; i.a=Lab[label]; 	// fixed up backward jump
	Code[cdx++]=i;
}
void Emit(char *code, int op) {	// Opr 코드생성
	Instruction i;
	printf("%d	%s\n", cdx, code);
	i.f=Opr; i.l=0; i.a=op;
	Code[cdx++]=i;
}
void EmitOut(char *code, fct op) {
    Instruction i;
    printf("%d\t%s\n", cdx, code); 
    i.f = op; i.l = 0; i.a = 0;
	Code[cdx++] = i;
}

void main() {
	InitializeSymbolTable();
	if (yyparse()) return;
	printf("===== Binary Code =====\n");
	fp=fopen("pl0.code", "w");
	for (int i=0; i<=cdx; i++) {
		printf("%d	%d	%d	%d\n", i, Code[i]);
		fprintf(fp, "%d	%d	%d	%d\n", i, Code[i]);
	}
	fclose(fp);
	printf("------------------------------\n");
	interprete();
}

