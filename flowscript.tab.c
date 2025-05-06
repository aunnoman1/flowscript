/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "flowscript.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Add ast.h here for ast_root definition
#include "codegen.h" // Include codegen header

int yylex(void);
void yyerror(const char *s);

ASTNode *ast_root = NULL; // Global pointer to the root of the AST

#line 84 "flowscript.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "flowscript.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_FOR = 7,                        /* FOR  */
  YYSYMBOL_EACH = 8,                       /* EACH  */
  YYSYMBOL_RANGE = 9,                      /* RANGE  */
  YYSYMBOL_PRINT = 10,                     /* PRINT  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_OR = 12,                        /* OR  */
  YYSYMBOL_NOT = 13,                       /* NOT  */
  YYSYMBOL_BUILTIN_DOUBLE = 14,            /* BUILTIN_DOUBLE  */
  YYSYMBOL_BUILTIN_ADD = 15,               /* BUILTIN_ADD  */
  YYSYMBOL_PIPE = 16,                      /* PIPE  */
  YYSYMBOL_ASSIGN = 17,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 20,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 21,                    /* DIVIDE  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NEQ = 23,                       /* NEQ  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 28,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 29,                    /* RBRACE  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_statements = 33,                /* statements  */
  YYSYMBOL_statement = 34,                 /* statement  */
  YYSYMBOL_assignment_statement = 35,      /* assignment_statement  */
  YYSYMBOL_pipeline_statement = 36,        /* pipeline_statement  */
  YYSYMBOL_expression = 37,                /* expression  */
  YYSYMBOL_term = 38,                      /* term  */
  YYSYMBOL_factor = 39,                    /* factor  */
  YYSYMBOL_function_call_like = 40,        /* function_call_like  */
  YYSYMBOL_opt_arg_list = 41,              /* opt_arg_list  */
  YYSYMBOL_arg_list = 42,                  /* arg_list  */
  YYSYMBOL_if_statement = 43,              /* if_statement  */
  YYSYMBOL_opt_else_clause = 44,           /* opt_else_clause  */
  YYSYMBOL_for_statement = 45,             /* for_statement  */
  YYSYMBOL_range_expression = 46           /* range_expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   309

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    64,    64,    65,    69,    70,    74,    75,    76,    77,
      82,    90,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   110,   114,   115,   116,   117,
     121,   126,   129,   133,   136,   142,   143,   147,   149,   153,
     157,   160,   163,   166,   174,   175,   179,   195
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "IDENTIFIER",
  "IF", "ELSE", "FOR", "EACH", "RANGE", "PRINT", "AND", "OR", "NOT",
  "BUILTIN_DOUBLE", "BUILTIN_ADD", "PIPE", "ASSIGN", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "EQ", "NEQ", "LT", "GT", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "COMMA", "$accept", "program", "statements",
  "statement", "assignment_statement", "pipeline_statement", "expression",
  "term", "factor", "function_call_like", "opt_arg_list", "arg_list",
  "if_statement", "opt_else_clause", "for_statement", "range_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-24)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -24,   -16,    47,   -23,   -22,    47,   -17,   -14,    47,
      28,   -24,    39,   -24,   -24,    -5,   -24,   -24,   -24,   -24,
     -24,    15,    47,    47,     6,   122,    47,    20,   265,     9,
      47,   197,   -24,   -24,    83,    83,    54,    83,    83,    83,
      83,    83,    83,    83,    83,    30,   265,    92,    11,   -24,
      86,    39,   107,   -24,   214,   -24,   231,   -24,   -24,   -24,
       6,   280,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,    32,    47,   -24,    16,    47,   -24,   -24,    47,    47,
      47,    47,    27,   -24,    50,   248,   137,   152,   167,   182,
      47,    35,   -24,   -24,    39,    39,    39,    39,    37,   265,
      39,    38,    41,    43,    46,   -24,    52,    50,    50,    50,
      50,   -24,   -24,   -24,   -24,   -24
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     4,     6,     7,    11,    12,    25,    28,     8,
       9,     0,     0,    35,    27,     0,     0,     0,    23,     0,
       0,     0,     1,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,    37,     0,    36,
       0,     0,     0,    34,     0,    31,     0,    29,    21,    22,
       0,     0,    24,    13,    14,    15,    16,    17,    18,    19,
      20,     0,     0,    30,     0,     0,    33,    32,     0,     0,
       0,     0,     0,    38,    44,     0,     0,     0,     0,     0,
       0,     0,    39,    47,     0,     0,     0,     0,     0,    11,
       0,     0,     0,     0,     0,    46,     0,    44,    44,    44,
      44,    45,    42,    43,    41,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -24,   -24,   -12,   -24,   -24,     1,    -1,   257,   -24,    -9,
     -24,     4,   -24,   199,   -24,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      48,    49,    19,    92,    20,    21
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      33,    22,    25,    26,    27,    28,    34,    35,    31,    29,
      23,    36,    30,    37,    38,    39,    40,    41,    42,    43,
      44,    46,    47,     1,    24,    52,    54,    62,    32,    56,
       5,    45,    23,     6,     7,     8,    55,    71,    73,    74,
      82,    62,     1,     2,     3,    84,     9,    53,     4,     5,
       1,    24,     6,     7,     8,    90,    91,     5,    60,    61,
       6,     7,     8,   100,     5,     9,   105,   107,     7,     8,
     108,    47,   109,     9,    85,   110,    83,    86,    87,    88,
      89,   111,   101,   102,   103,   104,     1,    24,   106,    99,
      60,    98,     0,     5,     0,     0,     5,     7,     8,     0,
       7,     8,     0,    34,    35,     0,     0,     0,    50,     9,
      37,    38,    39,    40,    41,    42,    43,    44,    34,    35,
       0,     0,    72,    50,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    34,    35,     0,     0,    75,    50,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    34,    35,
      51,     0,     0,    50,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    34,    35,    94,     0,     0,    50,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    34,    35,
      95,     0,     0,    50,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    34,    35,    96,     0,     0,    50,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    34,    35,
      97,     0,     0,    50,     0,    37,    38,    39,    40,    41,
      42,    43,    44,     0,    57,    34,    35,     0,     0,     0,
      50,     0,    37,    38,    39,    40,    41,    42,    43,    44,
       0,    76,    34,    35,     0,     0,     0,    50,     0,    37,
      38,    39,    40,    41,    42,    43,    44,     0,    77,    34,
      35,     0,     0,     0,    50,     0,    37,    38,    39,    40,
      41,    42,    43,    44,     0,    93,    34,    35,     0,     0,
       0,    50,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    58,    59,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    78,    79,    80,    81,   112,   113,   114,   115
};

static const yytype_int8 yycheck[] =
{
      12,    17,     3,    26,    26,     6,    11,    12,     9,    26,
      26,    16,    26,    18,    19,    20,    21,    22,    23,    24,
      25,    22,    23,     3,     4,    26,    27,    36,     0,    30,
      10,    16,    26,    13,    14,    15,    27,     7,    27,    51,
       8,    50,     3,     4,     5,    29,    26,    27,     9,    10,
       3,     4,    13,    14,    15,    28,     6,    10,     4,     5,
      13,    14,    15,    28,    10,    26,    29,    29,    14,    15,
      29,    72,    29,    26,    75,    29,    72,    78,    79,    80,
      81,    29,    94,    95,    96,    97,     3,     4,   100,    90,
       4,    90,    -1,    10,    -1,    -1,    10,    14,    15,    -1,
      14,    15,    -1,    11,    12,    -1,    -1,    -1,    16,    26,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      -1,    -1,    30,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    11,    12,    -1,    -1,    30,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      28,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    11,    12,    28,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      28,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    11,    12,    28,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      28,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    27,    11,    12,    -1,    -1,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    27,    11,
      12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    27,    11,    12,    -1,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    34,    35,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    22,    23,    24,    25,   107,   108,   109,   110
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    13,    14,    15,    26,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    43,
      45,    46,    17,    26,     4,    37,    26,    26,    37,    26,
      26,    37,     0,    33,    11,    12,    16,    18,    19,    20,
      21,    22,    23,    24,    25,    16,    37,    37,    41,    42,
      16,    28,    37,    27,    37,    27,    37,    27,    38,    38,
       4,     5,    40,    38,    38,    38,    38,    38,    38,    38,
      38,     7,    30,    27,    33,    30,    27,    27,    22,    23,
      24,    25,     8,    42,    29,    37,    37,    37,    37,    37,
      28,     6,    44,    27,    28,    28,    28,    28,    36,    37,
      28,    33,    33,    33,    33,    29,    33,    29,    29,    29,
      29,    29,    44,    44,    44,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    34,    34,    34,    34,
      35,    36,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    38,    39,    39,    39,    39,
      40,    40,    40,    40,    40,    41,    41,    42,    42,    43,
      43,    43,    43,    43,    44,    44,    45,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     3,
       4,     3,     4,     4,     3,     0,     1,     1,     3,     6,
       9,     9,     9,     9,     0,     4,     7,     6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 64 "flowscript.y"
                              { ast_root = (yyvsp[0].node); }
#line 1219 "flowscript.tab.c"
    break;

  case 3: /* program: %empty  */
#line 65 "flowscript.y"
                              { ast_root = NULL; }
#line 1225 "flowscript.tab.c"
    break;

  case 4: /* statements: statement  */
#line 69 "flowscript.y"
                              { (yyval.node) = ast_new_statements_list((yyvsp[0].node), NULL); }
#line 1231 "flowscript.tab.c"
    break;

  case 5: /* statements: statement statements  */
#line 70 "flowscript.y"
                              { (yyval.node) = ast_new_statements_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1237 "flowscript.tab.c"
    break;

  case 6: /* statement: assignment_statement  */
#line 74 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1243 "flowscript.tab.c"
    break;

  case 7: /* statement: pipeline_statement  */
#line 75 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1249 "flowscript.tab.c"
    break;

  case 8: /* statement: if_statement  */
#line 76 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1255 "flowscript.tab.c"
    break;

  case 9: /* statement: for_statement  */
#line 77 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1261 "flowscript.tab.c"
    break;

  case 10: /* assignment_statement: IDENTIFIER ASSIGN expression  */
#line 82 "flowscript.y"
                                 {
        ASTNode* var_node = ast_new_identifier((yyvsp[-2].sval));
        (yyval.node) = ast_new_assignment(var_node, (yyvsp[0].node));
        free((yyvsp[-2].sval)); // Free the sval from IDENTIFIER token
    }
#line 1271 "flowscript.tab.c"
    break;

  case 11: /* pipeline_statement: expression  */
#line 90 "flowscript.y"
                              { (yyval.node) = ast_new_expression_statement((yyvsp[0].node)); }
#line 1277 "flowscript.tab.c"
    break;

  case 12: /* expression: term  */
#line 94 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1283 "flowscript.tab.c"
    break;

  case 13: /* expression: expression PLUS term  */
#line 95 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(PLUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1289 "flowscript.tab.c"
    break;

  case 14: /* expression: expression MINUS term  */
#line 96 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(MINUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1295 "flowscript.tab.c"
    break;

  case 15: /* expression: expression MULTIPLY term  */
#line 97 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(MULTIPLY, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1301 "flowscript.tab.c"
    break;

  case 16: /* expression: expression DIVIDE term  */
#line 98 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(DIVIDE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1307 "flowscript.tab.c"
    break;

  case 17: /* expression: expression EQ term  */
#line 99 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1313 "flowscript.tab.c"
    break;

  case 18: /* expression: expression NEQ term  */
#line 100 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1319 "flowscript.tab.c"
    break;

  case 19: /* expression: expression LT term  */
#line 101 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1325 "flowscript.tab.c"
    break;

  case 20: /* expression: expression GT term  */
#line 102 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1331 "flowscript.tab.c"
    break;

  case 21: /* expression: expression AND term  */
#line 103 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1337 "flowscript.tab.c"
    break;

  case 22: /* expression: expression OR term  */
#line 104 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1343 "flowscript.tab.c"
    break;

  case 23: /* expression: NOT expression  */
#line 105 "flowscript.y"
                               { (yyval.node) = ast_new_binary_op(NOT, (yyvsp[0].node), NULL); /* Using binary_op for unary, right child is NULL */ }
#line 1349 "flowscript.tab.c"
    break;

  case 24: /* expression: expression PIPE function_call_like  */
#line 106 "flowscript.y"
                                         { (yyval.node) = ast_new_pipeline((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1355 "flowscript.tab.c"
    break;

  case 25: /* term: factor  */
#line 110 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1361 "flowscript.tab.c"
    break;

  case 26: /* factor: NUMBER  */
#line 114 "flowscript.y"
                              { (yyval.node) = ast_new_number((yyvsp[0].ival)); }
#line 1367 "flowscript.tab.c"
    break;

  case 27: /* factor: IDENTIFIER  */
#line 115 "flowscript.y"
                                { (yyval.node) = ast_new_identifier((yyvsp[0].sval)); free((yyvsp[0].sval)); /* IDENTIFIER used as a value */ }
#line 1373 "flowscript.tab.c"
    break;

  case 28: /* factor: function_call_like  */
#line 116 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1379 "flowscript.tab.c"
    break;

  case 29: /* factor: LPAREN expression RPAREN  */
#line 117 "flowscript.y"
                                { (yyval.node) = (yyvsp[-1].node); /* Pass through the inner expression node */ }
#line 1385 "flowscript.tab.c"
    break;

  case 30: /* function_call_like: IDENTIFIER LPAREN opt_arg_list RPAREN  */
#line 121 "flowscript.y"
                                          {
        // $1 is sval (char*) from IDENTIFIER token
        (yyval.node) = ast_new_function_call_user((yyvsp[-3].sval), (yyvsp[-1].node));
        free((yyvsp[-3].sval)); // Free the sval
    }
#line 1395 "flowscript.tab.c"
    break;

  case 31: /* function_call_like: BUILTIN_DOUBLE LPAREN RPAREN  */
#line 126 "flowscript.y"
                                   {
        (yyval.node) = ast_new_function_call_builtin(BUILTIN_ID_DOUBLE, NULL);
    }
#line 1403 "flowscript.tab.c"
    break;

  case 32: /* function_call_like: BUILTIN_ADD LPAREN expression RPAREN  */
#line 129 "flowscript.y"
                                           {
        ASTNode* arg_list = ast_new_arg_list_item((yyvsp[-1].node), NULL); // Single argument
        (yyval.node) = ast_new_function_call_builtin(BUILTIN_ID_ADD, arg_list);
    }
#line 1412 "flowscript.tab.c"
    break;

  case 33: /* function_call_like: PRINT LPAREN expression RPAREN  */
#line 133 "flowscript.y"
                                     { // Explicit print(expr)
        (yyval.node) = ast_new_print_statement((yyvsp[-1].node), 0 /* not implicit */);
    }
#line 1420 "flowscript.tab.c"
    break;

  case 34: /* function_call_like: PRINT LPAREN RPAREN  */
#line 136 "flowscript.y"
                          { // Implicit print() from pipe
        (yyval.node) = ast_new_print_statement(NULL, 1 /* implicit */);
    }
#line 1428 "flowscript.tab.c"
    break;

  case 35: /* opt_arg_list: %empty  */
#line 142 "flowscript.y"
                              { (yyval.node) = NULL; }
#line 1434 "flowscript.tab.c"
    break;

  case 36: /* opt_arg_list: arg_list  */
#line 143 "flowscript.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1440 "flowscript.tab.c"
    break;

  case 37: /* arg_list: expression  */
#line 147 "flowscript.y"
                              { (yyval.node) = ast_new_arg_list_item((yyvsp[0].node), NULL); }
#line 1446 "flowscript.tab.c"
    break;

  case 38: /* arg_list: expression COMMA arg_list  */
#line 149 "flowscript.y"
                                { (yyval.node) = ast_new_arg_list_item((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1452 "flowscript.tab.c"
    break;

  case 39: /* if_statement: IF expression LBRACE statements RBRACE opt_else_clause  */
#line 153 "flowscript.y"
                                                           {
        (yyval.node) = ast_new_if_statement((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1460 "flowscript.tab.c"
    break;

  case 40: /* if_statement: expression PIPE IF GT expression LBRACE statements RBRACE opt_else_clause  */
#line 157 "flowscript.y"
                                                                                {
        (yyval.node) = ast_new_piped_if_statement((yyvsp[-8].node), GT, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1468 "flowscript.tab.c"
    break;

  case 41: /* if_statement: expression PIPE IF LT expression LBRACE statements RBRACE opt_else_clause  */
#line 160 "flowscript.y"
                                                                                {
        (yyval.node) = ast_new_piped_if_statement((yyvsp[-8].node), LT, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1476 "flowscript.tab.c"
    break;

  case 42: /* if_statement: expression PIPE IF EQ expression LBRACE statements RBRACE opt_else_clause  */
#line 163 "flowscript.y"
                                                                                {
        (yyval.node) = ast_new_piped_if_statement((yyvsp[-8].node), EQ, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1484 "flowscript.tab.c"
    break;

  case 43: /* if_statement: expression PIPE IF NEQ expression LBRACE statements RBRACE opt_else_clause  */
#line 166 "flowscript.y"
                                                                                 {
        (yyval.node) = ast_new_piped_if_statement((yyvsp[-8].node), NEQ, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1492 "flowscript.tab.c"
    break;

  case 44: /* opt_else_clause: %empty  */
#line 174 "flowscript.y"
                                  { (yyval.node) = NULL; }
#line 1498 "flowscript.tab.c"
    break;

  case 45: /* opt_else_clause: ELSE LBRACE statements RBRACE  */
#line 175 "flowscript.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1504 "flowscript.tab.c"
    break;

  case 46: /* for_statement: range_expression PIPE FOR EACH LBRACE pipeline_statement RBRACE  */
#line 179 "flowscript.y"
                                                                    {
        // $6 is pipeline_statement which is an expression_statement node
        // The body_block for ast_new_for_statement should be a statements_list node
        // For now, let's assume the body_block in ast_new_for_statement can take a single statement node.
        // If ast_new_for_statement expects a NODE_STATEMENTS for body_block,
        // then we should wrap $6: ast_new_statements_list($6, NULL)
        // Assuming ast.h for_stmt.body_block can be a single statement node for now or a list.
        // Let's check ast.h: for_stmt { ASTNode *range_node; ASTNode *body_block; }
        // body_block should be a NODE_STATEMENTS. Our pipeline_statement is NODE_EXPRESSION_STATEMENT.
        // So, we should wrap it.
        ASTNode* body_as_statement_list = ast_new_statements_list((yyvsp[-1].node), NULL);
        (yyval.node) = ast_new_for_statement((yyvsp[-6].node), body_as_statement_list);
    }
#line 1522 "flowscript.tab.c"
    break;

  case 47: /* range_expression: RANGE LPAREN expression COMMA expression RPAREN  */
#line 195 "flowscript.y"
                                                    {
        (yyval.node) = ast_new_range_expression((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1530 "flowscript.tab.c"
    break;


#line 1534 "flowscript.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 200 "flowscript.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    // Consider adding yylloc information if available for better error reporting
}

// Main function updated to use AST
int main(void) {
    printf("Starting parse...\n");
    if (yyparse() == 0) {
        printf("Parse successful!\n");
        if (ast_root) {
            printf("AST generated. Printing AST...\n");
            ast_print(ast_root, 0); // Print the AST
            
            printf("Generating LLVM IR...\n");
            codegen_generate(ast_root, "output.ll"); // Generate LLVM IR

            printf("Freeing AST...\n");
            ast_free(ast_root);
        } else {
            printf("AST is NULL (empty input).\n");
        }
    } else {
        printf("Parse failed.\n");
    }
    return 0;
}

// To compile and run (example, add ast.c):
// bison -d flowscript.y  -> flowscript.tab.c, flowscript.tab.h
// flex flowscript.l      -> lex.yy.c
// gcc flowscript.tab.c lex.yy.c ast.c -o flowscript_parser -lfl
// ./flowscript_parser < your_script.fs
