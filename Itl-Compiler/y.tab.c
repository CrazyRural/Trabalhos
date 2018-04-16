/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintatica.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <stack>

#define YYSTYPE Atributos

using namespace std;

struct Atributos{
	string nomeVariavel;
	string labelTemp;
	string traducao;
	string tipo;
	string valor;
	string varTamString;
	int tamanho;
	int tamanho2;
	int tamanhoMax;
	int tamanhoMax2;
	struct{
		string nome;
		string cabecalho;
		string escopo;
		string retorno;
		string traducao;
		map<string,string> parametros;
	}funcao;
};

typedef	std::map<string,Atributos> MapaDeVariaveis;

struct Contexto{
	MapaDeVariaveis mapa;
	bool interrompivel;
	string rotuloInicio;
	string rotuloFim;
};


typedef std::stack<Contexto> PilhaContexto;

typedef	std::map<string,string> Tipos;
static Tipos tipos;

static PilhaContexto pilhaDeContextos;

void empilhaMapa(bool interrompivel, string rotuloInicio, string rotuloFim){

	Contexto c;
	c.interrompivel = interrompivel;
	c.rotuloInicio = rotuloInicio;
	c.rotuloFim = rotuloFim;
	pilhaDeContextos.push(c);

}

void desempilhaMapa(){

	pilhaDeContextos.pop();
	
}

int yylex(void);

string MSG_ERRO = "\nErrore:\n";
string MSG_ERRO_TIPO = "\nErrore:\nTipo errato per variabile";
string MSG_ERRO_NDECLARADA = "\nErrore:\nVariabile non dichiarata";
string MSG_ERRO_DECLARADA = "\nErrore:\nVariabile già dichiarata";
string MSG_ERRO_INICIALIZADA = "\nErrore:\nvariabile non inizializzata";
string MSG_ERRO_CONTEXTONAOINTERROMPIVEL = "\nErrore:\ncontesto non interrompibile";
string MSG_ERRO_TIPO_INDEFINIDO = "\nErrore:\nil tipo di variable non è definito";
string MSG_ERRO_MUITOS_ELEMENTOS_VETOR = "\nErrore\nPiù elementi inseriti di quelli consentiti";

void yyerror(string);


static int ctdDInt = 0, ctdDFloat = 0, ctdDChar = 0, ctdDBool = 0, ctdDString = 0, ctdDUndef = 0, ctdDStringTam = 0;
static int ctdDIntP = 0, ctdDFloatP = 0, ctdDCharP = 0, ctdDStringP = 0, ctdDBoolP = 0, count = 0;
static string switchPar, sFimIFs, sFSwitch, retornoR, ultimoTipo, function;
static int nCL = 0;
static int contaPot = 0;
static int fazCasting;
static int tipoGeral;
static int ctdLinhas = 1;
static int tamanhoVetor = 0;
static int tamanhoMatriz = 0;
static map<string, string> parametroAux;

void indicaErro(string MSG){

	std::cout<<MSG<<" (linea "<<ctdLinhas<<")\n"<<std::endl;

}

void contaLinha(){
	ctdLinhas++;
}

int tabelaDeTipos(string tipo1, string tipo2){

	if(tipo1 == "int" && tipo2 == "int"){
		return 0;
	}
	else if(tipo1 == "float" && tipo2 == "float"){
		return 3;
	}
	else if(tipo1 == "int" && tipo2 == "float"){
		return 1;
	}
	else{
		return 2;
	}
}

void adicionaVariavelContexto(Atributos a){

	pilhaDeContextos.top().mapa[a.nomeVariavel] = a;

}

static int nI = 0, nF = 0, nC = 0, nB = 0, nS = 0, nU = 0, nST = 0, nIP = 0, nFP = 0, nCP = 0, nSP = 0, nBP = 0;

string geraLabelTemp(string tipo){

	if(tipo == "intP"){
		ctdDIntP += 1;
		nIP++;
		return "TMP_INT_P" + to_string(nIP);
	}
	if(tipo == "int"){
		ctdDInt += 1;
		nI++;
		return "TMP_INT_" + to_string(nI);
	}

	if(tipo == "floatP"){
		ctdDFloatP += 1;
		nFP++;
		return "TMP_FLOAT_P" + to_string(nFP);
	}
	if(tipo == "float"){		
		ctdDFloat += 1;
		nF++;
		return "TMP_FLOAT_" + to_string(nF);
	}

	if(tipo == "charP"){
		ctdDCharP += 1;
		nCP++;
		return "TMP_CHAR_P" + to_string(nCP);
	}
	if(tipo == "char"){
		ctdDChar += 1;
		nC++;
		return "TMP_CHAR_" + to_string(nC);
	}


	if(tipo == "stringP"){
		ctdDStringP += 1;
		nSP++;
		return "TMP_STRING_P" + to_string(nSP);
	}
	if(tipo == "string"){
		ctdDString += 1;
		nS++;
		return "TMP_STRING_" + to_string(nS);
	}
	if(tipo == "string_tam"){
		ctdDStringTam += 1;
		nST++;
		return "TMP_STRING_TAM_" + to_string(nST);
	}

	if(tipo == "boolP"){
		ctdDBoolP += 1;
		nBP++;
		return "TMP_BOOL_P" + to_string(nBP);
	}
	if(tipo == "bool"){
		ctdDBool += 1;
		nB++;
		return "TMP_BOOL_" + to_string(nB);
	}
	if(tipo == "undefined"){
		ctdDUndef += 1;
		nU++;
		return "TMP_UNDEF_" + to_string(nU);
	}
}

string geraLabelFinal(){
	int i = 1;
	string declaracao = ""; 

	if(ctdDInt > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDInt){
			declaracao = declaracao + "TMP_INT_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_INT_" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDStringTam > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDStringTam){
			declaracao = declaracao + "TMP_STRING_TAM_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_STRING_TAM_" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDFloat > 0){
		declaracao = declaracao + "\tfloat ";
		while(i < ctdDFloat){
			declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_FLOAT_" + to_string(i) + ";\n";		
	}
	i = 1;
	if(ctdDChar > 0){
		declaracao = declaracao + "\tchar ";
		while(i < ctdDChar){
			declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_CHAR_" + to_string(i) + ";\n";		
	}
	i = 1;
	if(ctdDString > 0){			
		while(i <= ctdDString){
			declaracao = declaracao + "\tchar * TMP_STRING_" + to_string(i) + ";\n";
			i++;
		}				
	}
	i = 1;
	if(ctdDBool > 0){
		declaracao = declaracao + "\tint ";
		while(i < ctdDBool){
			declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_BOOL_" + to_string(i) + ";\n";		
	}
	i = 1;
	if(ctdDIntP > 0){
		declaracao = declaracao + "\tint * ";
		while(i < ctdDIntP){
			declaracao = declaracao + "TMP_INT_P" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_INT_P" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDFloatP > 0){
		declaracao = declaracao + "\tfloat * ";
		while(i < ctdDFloatP){
			declaracao = declaracao + "TMP_FLOAT_P" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_FLOAT_P" + to_string(i) + ";\n";
	}

	i = 1;
	if(ctdDCharP > 0){
		declaracao = declaracao + "\tchar * ";
		while(i < ctdDCharP){
			declaracao = declaracao + "TMP_CHAR_P" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_CHAR_P" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDStringP > 0){
		declaracao = declaracao + "\tchar * ";
		while(i < ctdDStringP){
			declaracao = declaracao + "TMP_STRING_P" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_STRING_P" + to_string(i) + ";\n";
	}
	i = 1;
	if(ctdDBoolP > 0){
		declaracao = declaracao + "\tint * ";
		while(i < ctdDBoolP){
			declaracao = declaracao + "TMP_BOOL_P" + to_string(i) + ", ";
			i++;
		}
		declaracao = declaracao + "TMP_BOOL_P" + to_string(i) + ";\n";
	}
	return declaracao + "\n";
}


static int nRotulo = 0;

string geraRotulo(){

	nRotulo++;
	return "ROTULO_" + to_string(nRotulo);

}

void atualizarPilhaContextos(Atributos a){

	PilhaContexto pilhaAux;
	bool achou = 0;
	string variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].nomeVariavel;
	if(variavel != ""){
		pilhaDeContextos.top().mapa[a.nomeVariavel] = a;
	}
	else if(pilhaDeContextos.size() > 1){

		pilhaAux.push(pilhaDeContextos.top());
		
		pilhaDeContextos.pop();

		do{

			variavel = pilhaDeContextos.top().mapa[a.nomeVariavel].nomeVariavel;
			
			if(variavel != ""){
				
				achou = 1;
				pilhaDeContextos.top().mapa[a.nomeVariavel] = a;				

			}
			
			pilhaAux.push(pilhaDeContextos.top());
			pilhaDeContextos.pop();
			

		}while(!pilhaDeContextos.empty() || !achou);
		
		//Retornando os contextos para a pilhaDeContextos...

		while(!pilhaAux.empty()){
			
			pilhaDeContextos.push(pilhaAux.top());
			pilhaAux.pop();

		}

	}

}

Contexto retornarContextoDaVariavel(string nomeVariavel){
	Contexto c;
	string variavel = pilhaDeContextos.top().mapa[nomeVariavel].labelTemp;
	if(variavel != ""){
		c = pilhaDeContextos.top();
		return c;
	}
	else if(pilhaDeContextos.size() > 1){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		copiaPilha.pop();
		do{

			c = copiaPilha.top();
			variavel = c.mapa[nomeVariavel].labelTemp;
			if(variavel != ""){
				
				return c;
			}
			copiaPilha.pop();

		}while(copiaPilha.size() >= 1);

	}

	return c;

}

//'e' de encontrar - PARA SABER SE A VARIAVEL JA FOI DECLARADA 
//'d' de declarar - PARA SABER SE PODE DECLARAR 

bool verificaNosContextosAnteriores(string nomeVariavel, char opcao){
	string variavel;
	
	if(opcao == 'e'){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		
		copiaPilha.pop();
		
		Contexto c;

		do{

			variavel = copiaPilha.top().mapa[nomeVariavel].nomeVariavel; //Verifica novamente
			c = copiaPilha.top();
			variavel = c.mapa[nomeVariavel].nomeVariavel;
			if(variavel != ""){
				return true;
			}
			copiaPilha.pop();
		
		}while(copiaPilha.size() >= 1);

		return false;

	}
	else if(opcao == 'd'){
		PilhaContexto copiaPilha;
		copiaPilha = pilhaDeContextos;
		copiaPilha.pop();
		
		Contexto c;
		do{
			
			variavel = copiaPilha.top().mapa[nomeVariavel].nomeVariavel; //Verifica novamente
			c = copiaPilha.top(); 
			variavel = c.mapa[nomeVariavel].nomeVariavel;
			if(variavel == ""){
				return true;
			}
			copiaPilha.pop();

		}while(copiaPilha.size() >= 1);

		return false;
	}

}

bool variavelExistente(string nomeVariavel, char opcao){

	string variavel = pilhaDeContextos.top().mapa[nomeVariavel].nomeVariavel;
	
		if(opcao == 'e'){
			if(variavel != ""){
				return true;
			}
			else if(pilhaDeContextos.size() > 1){
				
				bool achou = verificaNosContextosAnteriores(nomeVariavel, opcao);
				if(achou){
					return true;
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);
				}
				
			}
			else{
				indicaErro(MSG_ERRO_NDECLARADA);
				exit(1);	
			}
		}else if(opcao == 'd'){
			if(variavel == ""){
				return true;
			}
			else if(pilhaDeContextos.size() > 1){
				bool podeDeclarar = verificaNosContextosAnteriores(nomeVariavel, opcao);
				if(podeDeclarar){
					return true;
				}
				else{
					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);
				}
				
			}
			else{
				indicaErro(MSG_ERRO_NDECLARADA);
				exit(1);	
			}
		}			
				
}
string verificaErros(Atributos $1, Atributos $3, int opcao){

	if(opcao == 1){
		if(variavelExistente($1.nomeVariavel,'e')){
			Contexto c = retornarContextoDaVariavel($1.nomeVariavel);	
			if(c.mapa[$1.nomeVariavel].tipo == "int" || c.mapa[$1.labelTemp].tipo == "float"){
				
				if(c.mapa[$1.nomeVariavel].tipo != $3.tipo){											
					indicaErro(MSG_ERRO_TIPO);
					exit(1);		
				}
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else if($3.tipo == "string"){
				c.mapa[$1.nomeVariavel].tipo = $3.tipo;
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				c.mapa[$1.nomeVariavel].varTamString = $3.varTamString;
				c.mapa[$1.nomeVariavel].labelTemp = geraLabelTemp(c.mapa[$1.nomeVariavel].tipo);				
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else{

				indicaErro(MSG_ERRO_TIPO);
				exit(1);									
			}					
		}
	}else if(opcao == 2){

		if(variavelExistente($1.nomeVariavel, 'e')){
			Contexto c = retornarContextoDaVariavel($1.nomeVariavel);

			if(c.mapa[$1.nomeVariavel].tipo == "int" || c.mapa[$1.nomeVariavel].tipo == "float" || c.mapa[$1.nomeVariavel].tipo == "bool" || c.mapa[$1.nomeVariavel].tipo == "char"){
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else if(c.mapa[$1.nomeVariavel].tipo == "undefined"){
				c.mapa[$1.nomeVariavel].tipo = $3.tipo;
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				c.mapa[$1.nomeVariavel].labelTemp = geraLabelTemp(c.mapa[$1.nomeVariavel].tipo);				
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}
			else if($1.tipo == ""){
				c.mapa[$1.nomeVariavel].tipo = $3.tipo;
				c.mapa[$1.nomeVariavel].valor = $3.traducao;
				c.mapa[$1.nomeVariavel].labelTemp = geraLabelTemp(c.mapa[$1.nomeVariavel].tipo);				
				atualizarPilhaContextos(c.mapa[$1.nomeVariavel]);
				
				string retorno = $3.traducao + "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $3.labelTemp +";\n";
				
				return retorno;
			}else if($3.tipo == "string"){
				//cout<<"aaaa"<< endl;
			}else{

				indicaErro(MSG_ERRO_TIPO);
				exit(1);									
			}
		}
	}

}
 


#line 627 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_MAIN = 258,
    TOKEN_BEGIN = 259,
    TOKEN_VAR = 260,
    TOKEN_INT = 261,
    TOKEN_FLOAT = 262,
    TOKEN_DOUBLE = 263,
    TOKEN_CHAR = 264,
    TOKEN_BOOL = 265,
    TOKEN_STR = 266,
    TOKEN_NULL = 267,
    TOKEN_VOID = 268,
    TOKEN_IF = 269,
    TOKEN_ELSE = 270,
    TOKEN_ELSEIF = 271,
    TOKEN_SWITCH = 272,
    TOKEN_CASE = 273,
    TOKEN_DEFAULT = 274,
    TOKEN_IMP = 275,
    TOKEN_BREAK_ALL = 276,
    TOKEN_BREAK = 277,
    TOKEN_CONTINUE = 278,
    TOKEN_DO = 279,
    TOKEN_FOR = 280,
    TOKEN_WHILE = 281,
    TOKEN_PRINT = 282,
    TOKEN_ERROR = 283,
    TOKEN_STRUCT = 284,
    TOKEN_NOME = 285,
    TOKEN_NUM_INT = 286,
    TOKEN_NUM_FLOAT = 287,
    TOKEN_BOOLEAN_FALSE = 288,
    TOKEN_BOOLEAN_TRUE = 289,
    TOKEN_CARACTERE = 290,
    TOKEN_STRING = 291,
    TOKEN_POTENCIA = 292,
    TOKEN_MAIOR = 293,
    TOKEN_MENOR = 294,
    TOKEN_DIF = 295,
    TOKEN_IGUAL = 296,
    TOKEN_MAIORIGUAL = 297,
    TOKEN_MENORIGUAL = 298,
    TOKEN_E = 299,
    TOKEN_OU = 300,
    TOKEN_MAISIGUAL = 301,
    TOKEN_MENOSIGUAL = 302,
    TOKEN_VEZESIGUAL = 303,
    TOKEN_DIVIDEIGUAL = 304,
    TOKEN_PONTOIGUAL = 305,
    TOKEN_CONV_FLOAT = 306,
    TOKEN_CONV_INT = 307,
    TOKEN_ATR = 308,
    TOKEN_SCANF = 309,
    TOKEN_COMENT = 310,
    TOKEN_COM_INT = 311,
    TOKEN_COM_END = 312,
    TOKEN_LINECOMENT = 313,
    TOKEN_FUNCT = 314,
    TOKEN_RETURN = 315
  };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_BEGIN 259
#define TOKEN_VAR 260
#define TOKEN_INT 261
#define TOKEN_FLOAT 262
#define TOKEN_DOUBLE 263
#define TOKEN_CHAR 264
#define TOKEN_BOOL 265
#define TOKEN_STR 266
#define TOKEN_NULL 267
#define TOKEN_VOID 268
#define TOKEN_IF 269
#define TOKEN_ELSE 270
#define TOKEN_ELSEIF 271
#define TOKEN_SWITCH 272
#define TOKEN_CASE 273
#define TOKEN_DEFAULT 274
#define TOKEN_IMP 275
#define TOKEN_BREAK_ALL 276
#define TOKEN_BREAK 277
#define TOKEN_CONTINUE 278
#define TOKEN_DO 279
#define TOKEN_FOR 280
#define TOKEN_WHILE 281
#define TOKEN_PRINT 282
#define TOKEN_ERROR 283
#define TOKEN_STRUCT 284
#define TOKEN_NOME 285
#define TOKEN_NUM_INT 286
#define TOKEN_NUM_FLOAT 287
#define TOKEN_BOOLEAN_FALSE 288
#define TOKEN_BOOLEAN_TRUE 289
#define TOKEN_CARACTERE 290
#define TOKEN_STRING 291
#define TOKEN_POTENCIA 292
#define TOKEN_MAIOR 293
#define TOKEN_MENOR 294
#define TOKEN_DIF 295
#define TOKEN_IGUAL 296
#define TOKEN_MAIORIGUAL 297
#define TOKEN_MENORIGUAL 298
#define TOKEN_E 299
#define TOKEN_OU 300
#define TOKEN_MAISIGUAL 301
#define TOKEN_MENOSIGUAL 302
#define TOKEN_VEZESIGUAL 303
#define TOKEN_DIVIDEIGUAL 304
#define TOKEN_PONTOIGUAL 305
#define TOKEN_CONV_FLOAT 306
#define TOKEN_CONV_INT 307
#define TOKEN_ATR 308
#define TOKEN_SCANF 309
#define TOKEN_COMENT 310
#define TOKEN_COM_INT 311
#define TOKEN_COM_END 312
#define TOKEN_LINECOMENT 313
#define TOKEN_FUNCT 314
#define TOKEN_RETURN 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 798 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   514

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  163
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  360

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      66,    67,    64,    62,    61,    63,    73,    65,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    70,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    72,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,     2,    69,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   646,   646,   655,   656,   663,   668,   672,   673,   677,
     682,   688,   694,   701,   707,   713,   720,   726,   731,   736,
     737,   738,   739,   740,   741,   742,   743,   744,   745,   746,
     747,   748,   749,   750,   751,   754,   760,   764,   768,   771,
     776,   781,   820,   892,   981,  1008,  1062,  1131,  1143,  1157,
    1173,  1176,  1206,  1229,  1258,  1280,  1285,  1299,  1305,  1319,
    1326,  1332,  1344,  1382,  1384,  1389,  1401,  1416,  1421,  1425,
    1431,  1445,  1459,  1476,  1488,  1504,  1518,  1535,  1551,  1567,
    1582,  1591,  1595,  1599,  1605,  1616,  1622,  1632,  1680,  1711,
    1723,  1729,  1731,  1736,  1739,  1754,  1772,  1786,  1800,  1814,
    1818,  1821,  1827,  1833,  1840,  1846,  1855,  1871,  1877,  1905,
    1926,  1945,  1951,  1988,  2023,  2059,  2095,  2130,  2166,  2201,
    2236,  2242,  2248,  2256,  2264,  2272,  2280,  2323,  2365,  2407,
    2448,  2456,  2464,  2472,  2480,  2504,  2512,  2518,  2537,  2570,
    2617,  2672,  2723,  2777,  2783,  2788,  2793,  2798,  2814,  2819,
    2837,  2861,  2897,  2901,  2906,  2910,  2962,  2972,  2982,  3015,
    3062,  3115,  3124,  3133
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_MAIN", "TOKEN_BEGIN", "TOKEN_VAR",
  "TOKEN_INT", "TOKEN_FLOAT", "TOKEN_DOUBLE", "TOKEN_CHAR", "TOKEN_BOOL",
  "TOKEN_STR", "TOKEN_NULL", "TOKEN_VOID", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_ELSEIF", "TOKEN_SWITCH", "TOKEN_CASE", "TOKEN_DEFAULT",
  "TOKEN_IMP", "TOKEN_BREAK_ALL", "TOKEN_BREAK", "TOKEN_CONTINUE",
  "TOKEN_DO", "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_PRINT", "TOKEN_ERROR",
  "TOKEN_STRUCT", "TOKEN_NOME", "TOKEN_NUM_INT", "TOKEN_NUM_FLOAT",
  "TOKEN_BOOLEAN_FALSE", "TOKEN_BOOLEAN_TRUE", "TOKEN_CARACTERE",
  "TOKEN_STRING", "TOKEN_POTENCIA", "TOKEN_MAIOR", "TOKEN_MENOR",
  "TOKEN_DIF", "TOKEN_IGUAL", "TOKEN_MAIORIGUAL", "TOKEN_MENORIGUAL",
  "TOKEN_E", "TOKEN_OU", "TOKEN_MAISIGUAL", "TOKEN_MENOSIGUAL",
  "TOKEN_VEZESIGUAL", "TOKEN_DIVIDEIGUAL", "TOKEN_PONTOIGUAL",
  "TOKEN_CONV_FLOAT", "TOKEN_CONV_INT", "TOKEN_ATR", "TOKEN_SCANF",
  "TOKEN_COMENT", "TOKEN_COM_INT", "TOKEN_COM_END", "TOKEN_LINECOMENT",
  "TOKEN_FUNCT", "TOKEN_RETURN", "','", "'+'", "'-'", "'*'", "'/'", "'('",
  "')'", "'{'", "'}'", "';'", "'['", "']'", "'.'", "$accept", "S",
  "BLOCO_GLOBAL", "EMP_GLOBAL", "BLOCO_MAIN", "EMP_MAIN", "BLOCO_NI",
  "BLOCO_FUN", "BLOCO_FUN_RET", "EMP_NI", "BLOCO_LOOP", "BLOCO_SWITCH",
  "EMP_LOOP", "COMANDOS", "COMANDO", "ATR_RL", "ATR", "DCL_GLOBAL", "DCL",
  "MLTVAR_MAT", "MLTVAR_VET", "MLTVAR", "MLTVAR_STRING", "COMENT", "IF",
  "ELSE", "ELSEIF", "WHILE", "DO_WHILE", "FOR", "SWITCH", "CASES", "CASE",
  "DEFAULT", "CASE_VALUE", "FUNCTION_CALL", "FUNCT_CALLN",
  "FUNCT_CALL_AUX", "FUNCT_CALL_PAR_AUX", "FUNCTION", "FUNCTION_NOME",
  "FUNCTION_PARA", "TIPO", "RETURN", "BREAK_ALL", "BREAK", "CONTINUE",
  "ERL", "E", "ES", "CONCATENACAO", "PRINT", "CONTEUDO_PRINT",
  "MAIS_PRINT", "SCANF", "E_BASICA", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,    44,    43,    45,    42,    47,    40,    41,   123,   125,
      59,    91,    93,    46
};
# endif

#define YYPACT_NINF -260

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-260)))

#define YYTABLE_NINF -141

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -61,    21,    43,   193,  -260,   -35,  -260,   -31,  -260,   -12,
    -260,    78,    30,    -5,  -260,  -260,  -260,  -260,  -260,   344,
     344,   177,   344,  -260,    15,  -260,   449,   291,   291,   291,
      35,   -30,    75,  -260,  -260,  -260,    45,   193,   177,   177,
     177,   177,   177,   218,   350,   344,   344,    58,    76,  -260,
    -260,  -260,  -260,    79,    57,    84,    11,    74,    86,   103,
     108,    94,   291,  -260,  -260,    97,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,   102,  -260,    99,   105,   117,   118,   120,
     122,   124,   126,   129,   300,   174,   190,  -260,  -260,   150,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   177,
    -260,  -260,  -260,    57,   177,    57,   291,    57,   465,  -260,
      95,    27,   337,   179,   207,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,   172,   210,  -260,  -260,  -260,   344,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,   145,  -260,   180,
     181,    60,   182,   175,   418,   194,   249,    57,   426,    57,
      57,    57,    57,    57,    57,    57,    57,  -260,   196,   196,
     -39,   196,   196,   196,   195,   187,  -260,    73,   387,   197,
     385,   201,     2,   449,  -260,   199,    42,   198,   200,   211,
    -260,   229,  -260,   231,  -260,   300,  -260,  -260,   -25,   242,
    -260,  -260,  -260,   402,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,   191,   191,    95,  -260,  -260,   243,  -260,  -260,  -260,
    -260,  -260,   244,   344,  -260,  -260,  -260,    27,  -260,    42,
     216,   247,    42,   208,   344,  -260,   213,    69,   180,   181,
     232,   255,  -260,   225,    63,   234,   233,   344,  -260,   230,
     239,   236,  -260,  -260,   238,    33,   253,  -260,   211,   130,
      27,  -260,  -260,  -260,   300,   265,  -260,  -260,   261,  -260,
    -260,   268,   146,   272,   -16,   269,   271,   291,  -260,   177,
    -260,   276,  -260,   315,   287,   287,    87,  -260,    57,  -260,
     177,   329,   286,   146,  -260,  -260,   324,  -260,   325,  -260,
     289,    42,   291,  -260,   288,   300,   290,   292,   294,  -260,
     435,   345,  -260,   291,  -260,  -260,  -260,   314,   318,  -260,
    -260,   304,   101,   287,   287,   180,   181,   316,  -260,   291,
    -260,   196,  -260,   344,   321,  -260,  -260,  -260,  -260,   300,
      63,  -260,  -260,  -260,   323,   287,   287,  -260,  -260,  -260,
     322,   326,   332,   332,   328,   335,   336,   300,   180,   180,
     287,   287,  -260,  -260,   334,   339,   332,   332,  -260,  -260
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,    40,     3,     0,     7,     0,     8,     0,
       1,     0,     0,   158,   156,   157,   161,   162,   163,     0,
       0,     0,     0,     4,     0,    50,   136,    18,    18,    18,
       0,    64,     0,   130,   131,   132,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
     109,   110,    16,     0,     0,     0,   158,     0,     0,     0,
       0,     0,    18,    21,    20,     0,    33,    23,    25,    26,
      27,    24,    38,     0,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    63,     0,
     121,    39,   134,   122,   123,   124,   125,   133,   126,   135,
     127,   128,   129,     0,     0,     0,     0,     0,    16,   120,
     152,     0,     0,     0,     0,    69,   101,   103,   104,   102,
     105,    96,     0,     0,     6,    17,    19,    91,    34,    29,
      32,    22,    31,    30,    10,    14,     9,   158,   137,    64,
      67,    64,     0,   159,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,   154,   154,
     154,   154,   154,   154,     0,   138,   142,   158,     0,     0,
       0,     0,     0,   120,    68,     0,   100,     0,     0,    93,
       2,     0,    41,     0,    44,     0,    61,    63,    64,     0,
      13,    16,    78,     0,   111,   112,   113,   116,   117,   114,
     115,   118,   119,   152,   148,   146,     0,   149,   144,   145,
     147,   143,     0,    91,    35,    36,    37,     0,   155,   100,
       0,     0,   100,     0,     0,    90,     0,    67,    64,    67,
       0,     0,    48,     0,    70,     0,     0,     0,   153,     0,
       0,     0,   141,    99,     0,   100,     0,    88,    93,   159,
       0,    65,    62,    66,     0,     0,   160,    13,     0,    72,
      71,     0,     0,     0,   154,   139,     0,    18,    94,     0,
      98,     0,    92,     0,    60,    60,    64,    73,     0,    80,
       0,     0,     0,    83,    82,    16,     0,   150,     0,    87,
       0,   100,    18,    95,     0,     0,     0,     0,     0,    49,
       0,     0,    86,    18,    15,    81,    79,     0,     0,    11,
      97,   107,   160,    57,    59,    64,    67,     0,    13,    18,
      85,   154,   140,     0,     0,    56,    58,    42,    45,     0,
      74,    84,   151,   106,     0,    60,    60,    76,    75,    12,
       0,     0,    55,    55,     0,     0,     0,     0,    64,    64,
      60,    60,    43,    46,     0,     0,    52,    54,    51,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -260,  -260,  -260,  -260,   273,  -260,  -181,  -260,  -260,  -260,
     -46,  -260,   206,   -24,   302,  -260,  -260,   375,    17,  -259,
    -240,  -129,  -127,  -260,  -260,    85,   104,  -260,  -260,  -260,
    -260,   131,  -260,  -260,  -260,  -260,   319,   219,   185,  -260,
     312,  -211,   376,  -260,  -260,  -260,  -260,     4,   -19,   -82,
    -260,  -260,   245,  -144,  -260,    29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     4,     5,     6,   268,   293,     7,
       8,   235,     9,    61,    62,    63,    64,    23,    65,   345,
     296,    87,    88,    66,    67,   259,   260,    68,    69,    70,
      71,   282,   283,   284,   301,    72,    73,   178,   225,    74,
     122,   220,   221,   324,    75,    76,    77,   148,    25,   229,
      78,    79,   164,   204,    80,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    34,   140,    36,    81,    82,   105,    -9,   243,   234,
     182,   246,   186,   184,   187,   205,   207,   208,   209,   210,
      24,    10,   203,    84,    98,   100,   101,   102,   230,   166,
     172,    85,   206,    27,   270,   297,    85,    28,   125,   116,
     117,    86,   118,   119,   120,   203,   231,    11,   116,   117,
      35,   118,   119,   120,    24,   286,    29,   165,   108,   232,
      31,   111,   157,   138,   112,   139,    32,    92,    93,    94,
      95,    96,   216,   325,   326,   217,   277,   -89,   257,   258,
     310,    30,    32,   109,   346,    37,   269,    13,    14,    15,
      16,    17,    18,   171,   219,   340,   341,   358,   359,   252,
     251,    83,   253,   219,   158,   159,    89,   144,   179,   146,
     354,   355,    90,   185,   116,   117,   170,   118,   119,   120,
     287,    85,   250,   107,   103,   160,   161,   162,    35,   113,
     183,   163,   109,   145,   109,   242,   109,   330,   121,   -89,
     298,   173,   104,  -138,   181,   106,  -138,   299,    85,    36,
     110,   193,   114,   195,   196,   197,   198,   199,   200,   201,
     202,   115,  -140,   124,   280,   281,   228,   126,   127,   128,
    -140,  -140,   275,  -140,  -140,   129,   109,   332,   109,   109,
     109,   109,   109,   109,   109,   109,   327,   130,   131,   328,
     132,  -139,   133,   134,   179,   135,   136,   173,    12,  -139,
    -139,   273,  -139,  -139,   141,   248,  -138,    13,    14,    15,
      16,    17,    18,   314,  -138,  -138,   181,  -138,   263,   352,
     353,   142,   143,    13,    14,    15,    16,    17,    18,   149,
     150,   151,   152,   153,   154,   274,   174,   175,   176,   306,
     121,    85,   183,   290,    19,    20,   189,   336,    13,    14,
      15,    16,    17,    18,   188,   191,    21,   203,   212,    22,
     226,   227,   211,   213,   222,   351,   218,   223,   311,    19,
      20,   215,   224,   233,   239,   240,   313,   245,   247,   320,
      97,    21,   300,   244,    22,   249,   255,   149,   150,   151,
     152,   153,   154,   155,   156,   331,    12,   256,   291,   262,
     254,   261,   264,   266,   333,    47,   267,   109,    48,   302,
     335,   265,    49,    50,    51,    52,    53,    54,    55,   192,
     271,    56,    14,    15,    16,    17,    18,   278,   350,    57,
     137,    14,    15,    16,    17,    18,   138,   276,   279,   285,
     288,   289,    19,    20,   292,    58,   294,    59,   295,   303,
      60,    19,    20,   304,    21,   307,   308,    22,   309,   315,
     312,   316,   317,    21,   323,   319,    22,   167,    14,    15,
      16,    17,    18,   138,    13,    14,    15,    16,    17,    18,
      13,    14,    15,    16,    17,    18,   321,   329,    19,    20,
     322,   334,   339,   344,   342,    19,    20,   236,   343,   347,
      21,    19,    20,   168,   348,   349,   356,    21,   147,   180,
      22,   357,    91,    99,   305,   337,    22,    13,    14,    15,
      16,    17,    18,   149,   150,   151,   152,   153,   154,   155,
     156,   169,   241,   272,   338,   177,   123,     0,    19,    20,
     149,   150,   151,   152,   153,   154,   155,   156,   238,     0,
      21,     0,     0,   168,     0,   214,   149,   150,   151,   152,
     153,   154,   155,   156,   149,   150,   151,   152,   153,   154,
     155,   156,   237,   149,   150,   151,   152,   153,   154,   155,
     156,     0,     0,     0,     0,   190,    38,     0,     0,     0,
       0,     0,     0,   194,     0,    39,    40,    41,    42,     0,
       0,     0,   318,   149,   150,   151,   152,   153,   154,   155,
     156,    43,    44,    45,    46
};

static const yytype_int16 yycheck[] =
{
      19,    20,    84,    22,    28,    29,    52,    68,   219,   190,
     139,   222,   141,   140,   141,   159,   160,   161,   162,   163,
       3,     0,    61,    53,    43,    44,    45,    46,    53,   111,
     112,    61,    71,    68,   245,   275,    61,    68,    62,     6,
       7,    71,     9,    10,    11,    61,    71,     4,     6,     7,
      21,     9,    10,    11,    37,    71,    68,    30,    54,   188,
      30,    50,   108,    36,    53,    84,    71,    38,    39,    40,
      41,    42,    70,   313,   314,    73,   257,    66,    15,    16,
     291,     3,    71,    54,   343,    70,    53,    30,    31,    32,
      33,    34,    35,   112,    61,   335,   336,   356,   357,   228,
     227,    66,   229,    61,     9,    10,    31,   103,   127,   105,
     350,   351,    67,    53,     6,     7,   112,     9,    10,    11,
     264,    61,    53,    66,    66,    30,    31,    32,    99,    55,
      61,    36,   103,   104,   105,   217,   107,   318,    30,    66,
      53,   112,    66,    70,    71,    66,    73,   276,    61,   168,
      66,   147,    66,   149,   150,   151,   152,   153,   154,   155,
     156,    58,    61,    69,    18,    19,   185,    70,    66,    70,
      69,    70,   254,    72,    73,    70,   147,   321,   149,   150,
     151,   152,   153,   154,   155,   156,   315,    70,    70,   316,
      70,    61,    70,    69,   213,    69,    67,   168,     5,    69,
      70,    71,    72,    73,    30,   224,    61,    30,    31,    32,
      33,    34,    35,   295,    69,    70,    71,    72,   237,   348,
     349,    31,    72,    30,    31,    32,    33,    34,    35,    38,
      39,    40,    41,    42,    43,   254,    57,    30,    66,   285,
      30,    61,    61,   267,    51,    52,    71,   329,    30,    31,
      32,    33,    34,    35,    72,    61,    63,    61,    71,    66,
      31,    30,    67,    66,    66,   347,    67,    67,   292,    51,
      52,    70,    61,    31,    31,    31,   295,    30,    70,   303,
      62,    63,   278,    67,    66,    72,    31,    38,    39,    40,
      41,    42,    43,    44,    45,   319,     5,    72,   269,    66,
      68,    67,    72,    67,   323,    14,    68,   278,    17,   280,
     329,    72,    21,    22,    23,    24,    25,    26,    27,    70,
      67,    30,    31,    32,    33,    34,    35,    66,   347,    38,
      30,    31,    32,    33,    34,    35,    36,    72,    70,    67,
      71,    70,    51,    52,    68,    54,    31,    56,    61,    20,
      59,    51,    52,    67,    63,    31,    31,    66,    69,    69,
      72,    69,    68,    63,    60,    20,    66,    30,    31,    32,
      33,    34,    35,    36,    30,    31,    32,    33,    34,    35,
      30,    31,    32,    33,    34,    35,    72,    71,    51,    52,
      72,    70,    69,    61,    72,    51,    52,   191,    72,    71,
      63,    51,    52,    66,    69,    69,    72,    63,   106,   136,
      66,    72,    37,    63,   283,   330,    66,    30,    31,    32,
      33,    34,    35,    38,    39,    40,    41,    42,    43,    44,
      45,   112,   213,   248,   330,   123,    60,    -1,    51,    52,
      38,    39,    40,    41,    42,    43,    44,    45,   203,    -1,
      63,    -1,    -1,    66,    -1,    70,    38,    39,    40,    41,
      42,    43,    44,    45,    38,    39,    40,    41,    42,    43,
      44,    45,    70,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    67,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    46,    47,    48,    49,    -1,
      -1,    -1,    67,    38,    39,    40,    41,    42,    43,    44,
      45,    62,    63,    64,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,    76,    77,    78,    79,    80,    83,    84,    86,
       0,     4,     5,    30,    31,    32,    33,    34,    35,    51,
      52,    63,    66,    91,    92,   122,   129,    68,    68,    68,
       3,    30,    71,   122,   122,   129,   122,    70,    37,    46,
      47,    48,    49,    62,    63,    64,    65,    14,    17,    21,
      22,    23,    24,    25,    26,    27,    30,    38,    54,    56,
      59,    87,    88,    89,    90,    92,    97,    98,   101,   102,
     103,   104,   109,   110,   113,   118,   119,   120,   124,   125,
     128,    87,    87,    66,    53,    61,    71,    95,    96,    31,
      67,    91,   129,   129,   129,   129,   129,    62,   122,    63,
     122,   122,   122,    66,    66,    84,    66,    66,   121,   129,
      66,    50,    53,    55,    66,    58,     6,     7,     9,    10,
      11,    30,   114,   116,    69,    87,    70,    66,    70,    70,
      70,    70,    70,    70,    69,    69,    67,    30,    36,   122,
     123,    30,    31,    72,   121,   129,   121,    88,   121,    38,
      39,    40,    41,    42,    43,    44,    45,    84,     9,    10,
      30,    31,    32,    36,   126,    30,   123,    30,    66,   110,
     121,   122,   123,   129,    57,    30,    66,   114,   111,   122,
      78,    71,    95,    61,    96,    53,    95,    96,    72,    71,
      67,    61,    70,   121,    67,   121,   121,   121,   121,   121,
     121,   121,   121,    61,   127,   127,    71,   127,   127,   127,
     127,    67,    71,    66,    70,    70,    70,    73,    67,    61,
     115,   116,    66,    67,    61,   112,    31,    30,   122,   123,
      53,    71,    95,    31,    80,    85,    86,    70,   126,    31,
      31,   111,   123,   115,    67,    30,   115,    70,   122,    72,
      53,    96,    95,    96,    68,    31,    72,    15,    16,    99,
     100,    67,    66,   122,    72,    72,    67,    68,    81,    53,
     115,    67,   112,    71,   122,   123,    72,    80,    66,    70,
      18,    19,   105,   106,   107,    67,    71,   127,    71,    70,
      87,   129,    68,    82,    31,    61,    94,    94,    53,    95,
     121,   108,   129,    20,    67,   105,    84,    31,    31,    69,
     115,    87,    72,   122,   123,    69,    69,    68,    67,    20,
      87,    72,    72,    60,   117,    94,    94,    95,    96,    71,
      80,    87,   127,   122,    70,   122,   123,    99,   100,    69,
      94,    94,    72,    72,    61,    93,    93,    71,    69,    69,
     122,   123,    95,    95,    94,    94,    72,    72,    93,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    78,    78,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    90,    90,    90,    91,
      91,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    96,    96,    96,    97,    97,
      98,    98,    98,    99,   100,   100,   100,   101,   102,   103,
     104,   105,   105,   105,   106,   107,   108,   109,   109,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   115,
     115,   116,   116,   116,   116,   116,   117,   117,   118,   119,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   123,
     123,   124,   124,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   127,   127,   128,   129,   129,   129,   129,
     129,   129,   129,   129
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     2,     0,     4,     1,     1,     0,
       4,     3,     5,     0,     4,     4,     0,     2,     0,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     2,     4,     4,     4,     1,     3,
       0,     5,    11,    17,     5,    11,    17,     3,     6,     9,
       1,     6,     5,     6,     5,     0,     3,     2,     3,     2,
       0,     3,     5,     1,     0,     3,     5,     0,     3,     2,
       5,     6,     6,     2,     5,     6,     6,     3,     4,     8,
       7,     2,     1,     1,     4,     3,     1,     7,     5,     1,
       2,     0,     3,     0,     6,     7,     1,     5,     3,     2,
       0,     1,     1,     1,     1,     1,     2,     0,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     3,     3,     1,     1,     1,     4,
       7,     5,     3,     4,     2,     2,     2,     2,     2,     2,
       5,     8,     0,     2,     0,     4,     1,     1,     1,     4,
       7,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 647 "sintatica.y" /* yacc.c:1646  */
    {
            	
            	(yyval).labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void){\n" <<
				(yyval).labelTemp << (yyvsp[-5]).traducao + (yyvsp[0]).traducao << "\treturn 0;\n}" << endl; 							
				
			}
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 657 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 663 "sintatica.y" /* yacc.c:1646  */
    {	
				//Empilha o Escopo Global
				empilhaMapa(0,"","");
			}
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 669 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 677 "sintatica.y" /* yacc.c:1646  */
    {
				//Empilha o Main
				empilhaMapa(0,"","");
			}
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 683 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 689 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 695 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao;
			}
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 701 "sintatica.y" /* yacc.c:1646  */
    {
				//Empilha o Bloco não interrompível
				empilhaMapa(0,"","");
			}
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 708 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2246 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 714 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 720 "sintatica.y" /* yacc.c:1646  */
    {
				//Empilha o Bloco interrompível
				empilhaMapa(1,geraRotulo(),geraRotulo());
			}
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 727 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 731 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 755 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 2);
			}
#line 2287 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 761 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 1);
			}
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 765 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = verificaErros((yyvsp[-3]), (yyvsp[-1]), 1);
			}
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 772 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
			}
#line 2311 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 776 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 782 "sintatica.y" /* yacc.c:1646  */
    {
				
				Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
				string tipo;
				string valor;
				string traducao;
				string labelTemp;

				if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == ""){
					tipo = (yyvsp[-1]).tipo;
					valor = (yyvsp[-1]).valor;
					traducao = (yyvsp[-1]).traducao;
					labelTemp = (yyvsp[-1]).labelTemp;
				}else{
					tipo = c.mapa[(yyvsp[-1]).nomeVariavel].tipo;
					valor = c.mapa[(yyvsp[-1]).nomeVariavel].valor;
					traducao = c.mapa[(yyvsp[-1]).nomeVariavel].traducao;
					labelTemp = c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp;
				}				
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = (yyvsp[-1]).tipo;
					(yyval).valor = valor;			

					if(tipo != (yyval).tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).valor = traducao;
					(yyval).traducao = (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + labelTemp + ";\n" + (yyvsp[0]).traducao; 

					adicionaVariavelContexto((yyval));

					ultimoTipo = (yyval).tipo;
				}

			}
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 821 "sintatica.y" /* yacc.c:1646  */
    {
				tamanhoVetor += 1;
				if(stoi((yyvsp[-7]).traducao) == tamanhoVetor){
					
					int compTipos;
					if((yyvsp[-2]).tipo.compare("umElemento") == 0)
						compTipos = 1;
					else
					 	compTipos = !(yyvsp[-3]).tipo.compare((yyvsp[-2]).tipo);

					if(compTipos){
						if((yyvsp[-3]).tipo.compare("int") == 0)
							(yyval).tipo = "intP";					
						if((yyvsp[-3]).tipo.compare("float") == 0)
							(yyval).tipo = "floatP";
						if((yyvsp[-3]).tipo.compare("bool") == 0)
							(yyval).tipo = "boolP";
						if((yyvsp[-3]).tipo.compare("char") == 0)
							(yyval).tipo = "charP";
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ((yyvsp[-3]).tipo.compare("int") == 0){
						c = nI - tamanhoVetor + 1;
						s += "TMP_INT_"; 
					}
					if ((yyvsp[-3]).tipo.compare("float") == 0){
						c = nF - tamanhoVetor + 1;
						s += "TMP_FLOAT_";
					}
					if ((yyvsp[-3]).tipo.compare("bool") == 0){
						c = nB - tamanhoVetor + 1;
						s += "TMP_BOOL_";
					}
					if ((yyvsp[-3]).tipo.compare("char") == 0){
						c = nC - tamanhoVetor + 1;
						s += "TMP_CHAR_";
					}


					(yyval).labelTemp = geraLabelTemp((yyval).tipo);	
					string labelAux = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoVetor ; i++){
						labelVetor += "\t" + (yyval).labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + 
					"\t" + labelAux + " = " + to_string(tamanhoVetor) + ";\n" +
					"\t" + (yyval).labelTemp + " = (" + (yyvsp[-3]).tipo + "*)malloc(" + labelAux + " * sizeof(" + (yyvsp[-3]).tipo +"));\n" +
					labelVetor;
					
					(yyval).nomeVariavel = (yyvsp[-9]).nomeVariavel;									
					(yyval).tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					(yyval).tamanhoMax = stoi((yyvsp[-7]).traducao);
					(yyval).valor = "preenchido";

					adicionaVariavelContexto((yyval));
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
#line 2438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 893 "sintatica.y" /* yacc.c:1646  */
    {
				tamanhoMatriz += tamanhoVetor + 1;
				if(stoi((yyvsp[-13]).traducao) * stoi((yyvsp[-10]).traducao) == tamanhoMatriz){	

										

					int compTipos, compTipos2;
					if (((yyvsp[-4]).tipo.compare("umElemento") == 0) && ((yyvsp[-2]).tipo.compare("umElemento") == 0)) {
						compTipos = 1;
						compTipos2 = 1;
					}	
					else if(stoi((yyvsp[-10]).traducao) == 1 and ((yyvsp[-4]).tipo.compare("umElemento") == 0)){
						compTipos = 1;
						compTipos2 = !(yyvsp[-5]).tipo.compare((yyvsp[-2]).tipo);
					}
					else if(stoi((yyvsp[-13]).traducao) == 1 and ((yyvsp[-2]).tipo.compare("umElemento") == 0)){
						compTipos = !(yyvsp[-5]).tipo.compare((yyvsp[-4]).tipo);
						compTipos2 = 1 ;
					}
					else{
					 	compTipos = !(yyvsp[-5]).tipo.compare((yyvsp[-4]).tipo);
					 	compTipos2 = !(yyvsp[-5]).tipo.compare((yyvsp[-2]).tipo);	
					}

					if(compTipos == 1 and compTipos2 == 1){
						if((yyvsp[-5]).tipo.compare("int") == 0)
							(yyval).tipo = "intP";					
						if((yyvsp[-5]).tipo.compare("float") == 0)
							(yyval).tipo = "floatP";
						if((yyvsp[-5]).tipo.compare("bool") == 0)
							(yyval).tipo = "boolP";
						if((yyvsp[-5]).tipo.compare("char") == 0)
							(yyval).tipo = "charP";
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ((yyvsp[-5]).tipo.compare("int") == 0){
						c = nI - tamanhoMatriz + 1;
						s += "TMP_INT_"; 
					}
					if ((yyvsp[-5]).tipo.compare("float") == 0){
						c = nF - tamanhoMatriz + 1;
						s += "TMP_FLOAT_";
					}
					if ((yyvsp[-5]).tipo.compare("bool") == 0){
						c = nB - tamanhoMatriz + 1;
						s += "TMP_BOOL_";
					}
					if ((yyvsp[-5]).tipo.compare("char") == 0){
						c = nC - tamanhoMatriz + 1;
						s += "TMP_CHAR_";
					}


					(yyval).labelTemp = geraLabelTemp((yyval).tipo);	
					string labelAux = geraLabelTemp("int");
					string labelAux2 = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoMatriz ; i++){
						labelVetor += "\t" + (yyval).labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-4]).traducao + (yyvsp[-2]).traducao +
					"\n\t" + labelAux + " = " + (yyvsp[-13]).traducao + ";\n" +
					"\t" + labelAux2 + " = " + (yyvsp[-10]).traducao + ";\n" +
					"\t" + (yyval).labelTemp + " = (" + (yyvsp[-5]).tipo + "*)malloc(" + labelAux + " * " + labelAux2 + " * sizeof(" + (yyvsp[-5]).tipo +"));\n" +
					labelVetor;
					
					(yyval).nomeVariavel = (yyvsp[-15]).nomeVariavel;									
					(yyval).tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					tamanhoMatriz = 0;
					(yyval).tamanhoMax = stoi((yyvsp[-13]).traducao) * stoi((yyvsp[-10]).traducao);
					(yyval).valor = "preenchido";

					adicionaVariavelContexto((yyval));
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
#line 2531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 982 "sintatica.y" /* yacc.c:1646  */
    {

				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					if(tipoGeral == 2){
						(yyval).tipo = "string";
						(yyval).valor = (yyvsp[-1]).valor;						

						if((yyvsp[-1]).tipo != (yyval).tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						(yyval).tamanho = (yyvsp[-1]).tamanho;
						(yyval).varTamString = (yyvsp[-1]).varTamString;
						(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;						
						(yyval).labelTemp = geraLabelTemp((yyval).tipo);
						(yyval).traducao = (yyvsp[-1]).traducao +  "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 

						adicionaVariavelContexto((yyval));
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1009 "sintatica.y" /* yacc.c:1646  */
    {
				tamanhoVetor += 1;
				if(stoi((yyvsp[-7]).traducao) == tamanhoVetor){
					
					int compTipos;
					if((yyvsp[-2]).tipo.compare("umElemento") == 0)
						compTipos = 1;
					else
					 	compTipos = !(yyvsp[-3]).tipo.compare((yyvsp[-2]).tipo);

					if(compTipos){
						if((yyvsp[-3]).tipo.compare("string") == 0)
							(yyval).tipo = "stringP";					
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ((yyvsp[-3]).tipo.compare("string") == 0){
						c = nS - tamanhoVetor + 1;
						s += "TMP_STRING_"; 
					}

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);	
					string labelAux = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoVetor ; i++){
						labelVetor += "\t" + (yyval).labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + 
					"\n\t" + labelAux + " = " + to_string(tamanhoVetor) + ";\n" +
					"\t" + (yyval).labelTemp + " = (char*)malloc(" + labelAux + " * sizeof(char));\n" +
					labelVetor;
					
					(yyval).nomeVariavel = (yyvsp[-9]).nomeVariavel;									
					(yyval).tamanho = tamanhoVetor;
					tamanhoVetor = 0;

					(yyval).tamanhoMax = stoi((yyvsp[-7]).traducao);
					(yyval).valor = "preenchido";

					adicionaVariavelContexto((yyval)); 
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
#line 2620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1063 "sintatica.y" /* yacc.c:1646  */
    {
				tamanhoMatriz += tamanhoVetor + 1;
				if(stoi((yyvsp[-13]).traducao) * stoi((yyvsp[-10]).traducao) == tamanhoMatriz){									
					int compTipos, compTipos2;

					if (((yyvsp[-4]).tipo.compare("umElemento") == 0) && ((yyvsp[-2]).tipo.compare("umElemento") == 0)) {
						compTipos = 1;
						compTipos2 = 1;
					}	
					else if(stoi((yyvsp[-10]).traducao) == 1 and ((yyvsp[-4]).tipo.compare("umElemento") == 0)){
						compTipos = 1;
						compTipos2 = !(yyvsp[-5]).tipo.compare((yyvsp[-2]).tipo);
					}
					else if(stoi((yyvsp[-13]).traducao) == 1 and ((yyvsp[-2]).tipo.compare("umElemento") == 0)){
						compTipos = !(yyvsp[-5]).tipo.compare((yyvsp[-4]).tipo);
						compTipos2 = 1 ;
					}					
					else{
					 	compTipos = !(yyvsp[-5]).tipo.compare((yyvsp[-4]).tipo);
					 	compTipos2 = !(yyvsp[-5]).tipo.compare((yyvsp[-2]).tipo);	
					}

					if(compTipos == 1 and compTipos2 == 1){
						if((yyvsp[-5]).tipo.compare("string") == 0)
							(yyval).tipo = "stringP";	
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ((yyvsp[-5]).tipo.compare("string") == 0){
						c = nS - tamanhoMatriz + 1;
						s += "TMP_STRING_"; 
					}


					(yyval).labelTemp = geraLabelTemp((yyval).tipo);	
					string labelAux = geraLabelTemp("int");
					string labelAux2 = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoMatriz ; i++){
						labelVetor += "\t" + (yyval).labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-4]).traducao + (yyvsp[-2]).traducao +
					"\n\t" + labelAux + " = " + (yyvsp[-13]).traducao + ";\n" +
					"\t" + labelAux2 + " = " + (yyvsp[-10]).traducao + ";\n" +
					"\t" + (yyval).labelTemp + "(char*)malloc(" + labelAux + " * " + labelAux2 + " * sizeof(char));\n" +
					labelVetor;
					
					(yyval).nomeVariavel = (yyvsp[-15]).nomeVariavel;									
					(yyval).tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					tamanhoMatriz = 0;
					(yyval).tamanhoMax = stoi((yyvsp[-13]).traducao) * stoi((yyvsp[-10]).traducao);
					(yyval).valor = "preenchido";

					adicionaVariavelContexto((yyval));
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
#line 2693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1132 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "undefined";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;
					adicionaVariavelContexto((yyval));
										
				}
			}
#line 2709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1144 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-4]).nomeVariavel, 'd')){
					(yyval).tipo = "undefined";
					(yyval).valor = "null";
					(yyval).tamanhoMax = stoi((yyvsp[-2]).traducao);				
					(yyval).tamanho = 0;	
					(yyval).nomeVariavel = (yyvsp[-4]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;
					adicionaVariavelContexto((yyval));
										
				}
			}
#line 2727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1158 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-7]).nomeVariavel, 'd')){
					(yyval).tipo = "undefined";
					(yyval).valor = "null";
					(yyval).tamanhoMax = stoi((yyvsp[-5]).traducao);				
					(yyval).tamanhoMax2 = stoi((yyvsp[-2]).traducao);				
					(yyval).tamanho = 0;
					(yyval).tamanho2 = 0;	
					(yyval).nomeVariavel = (yyvsp[-7]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[0]).traducao;
					adicionaVariavelContexto((yyval));
										
				}
			}
#line 2747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1177 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				tamanhoVetor += 1;

				
				int compTipos;
				if(!(yyvsp[-2]).tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !(yyvsp[-3]).tipo.compare((yyvsp[-2]).tipo);;
				}


				if(compTipos){
					compTipos = !(yyvsp[-2]).tipo.compare((yyvsp[0]).tipo);
					if(compTipos){
						(yyval).tipo = (yyvsp[-2]).tipo;					
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);						
					}
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1207 "sintatica.y" /* yacc.c:1646  */
    {				
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[-1]).traducao;
				tamanhoVetor += 1;

				int compTipos;
				if(!(yyvsp[-1]).tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !(yyvsp[-2]).tipo.compare((yyvsp[-1]).tipo);;
				}

												
				if(compTipos){
					(yyval).tipo = (yyvsp[-1]).tipo;
					cout << (yyvsp[-1]).tipo << endl;													
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1230 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				tamanhoVetor += 1;

				
				int compTipos;
				if(!(yyvsp[-2]).tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !(yyvsp[-3]).tipo.compare((yyvsp[-2]).tipo);;
				}

				if(compTipos){
					compTipos = !(yyvsp[-2]).tipo.compare((yyvsp[0]).tipo);
					if(compTipos){
						(yyval).tipo = (yyvsp[-2]).tipo;					
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);						
					}
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1259 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[-1]).traducao;
				tamanhoVetor += 1;

				int compTipos;
				if(!(yyvsp[-1]).tipo.compare("umElemento")){
					compTipos = 1;					
				}
				else
					compTipos = !(yyvsp[-2]).tipo.compare((yyvsp[-1]).tipo);

				if(compTipos){
					(yyval).tipo = (yyvsp[-1]).tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1280 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "umElemento";
				(yyval).traducao = "";
			}
#line 2875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1286 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				tamanhoVetor += 1;

				int compTipos = !(yyvsp[-1]).tipo.compare((yyvsp[0]).tipo);
				if(compTipos){
					(yyval).tipo = (yyvsp[-1]).tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1300 "sintatica.y" /* yacc.c:1646  */
    {		
				(yyval).tipo = (yyvsp[0]).tipo;				
				(yyval).traducao = (yyvsp[0]).traducao;
				tamanhoVetor += 1;
			}
#line 2903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1306 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				tamanhoVetor += 1;

				int compTipos = !(yyvsp[-1]).tipo.compare((yyvsp[0]).tipo);
				if(compTipos){
					(yyval).tipo = (yyvsp[-1]).tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
#line 2921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1320 "sintatica.y" /* yacc.c:1646  */
    {		
				(yyval).tipo = (yyvsp[0]).tipo;				
				(yyval).traducao = (yyvsp[0]).traducao;
				tamanhoVetor += 1;
			}
#line 2931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1326 "sintatica.y" /* yacc.c:1646  */
    {	
				(yyval).tipo = "umElemento";
				(yyval).traducao = "";
			}
#line 2940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1333 "sintatica.y" /* yacc.c:1646  */
    {
			if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
				(yyval).tipo = "undefined";
				(yyval).valor = "null";
				(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "";
				
				adicionaVariavelContexto((yyval));
			}
		}
#line 2956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1345 "sintatica.y" /* yacc.c:1646  */
    {
			Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
			string tipo;
			string valor;
			string traducao;
			string labelTemp;

			if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == ""){
				tipo = (yyvsp[-1]).tipo;
				valor = (yyvsp[-1]).valor;
				traducao = (yyvsp[-1]).traducao;
				labelTemp = (yyvsp[-1]).labelTemp;
			}else{
				tipo = c.mapa[(yyvsp[-1]).nomeVariavel].tipo;
				valor = c.mapa[(yyvsp[-1]).nomeVariavel].valor;
				traducao = c.mapa[(yyvsp[-1]).nomeVariavel].traducao;
				labelTemp = c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp;
			}
			

			if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).valor = valor;		
				if(tipo != (yyval).tipo ){																
					indicaErro(MSG_ERRO_TIPO);
					exit(1);		
				}				
				(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = traducao;
				(yyval).traducao = (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + labelTemp + ";\n" + (yyvsp[0]).traducao; 

				adicionaVariavelContexto((yyval));

				ultimoTipo = (yyval).tipo;
			}
		}
#line 2998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1384 "sintatica.y" /* yacc.c:1646  */
    {
			(yyval).traducao = "";
		}
#line 3006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1390 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'd')){
					(yyval).tipo = "string";
					(yyval).valor = "null";
					(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = "";

					adicionaVariavelContexto((yyval));
				}
			}
#line 3022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1402 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'd')){
					(yyval).tipo = "string";
					(yyval).valor = (yyvsp[-1]).valor;
					(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).tamanho = (yyvsp[-1]).tamanho;
					(yyval).varTamString = (yyvsp[-1]).varTamString;
					(yyval).traducao = (yyvsp[0]).traducao + (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" ;
					
					adicionaVariavelContexto((yyval));
				}
			}
#line 3040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1416 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 3048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1422 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\n\t/*" + (yyvsp[-1]).traducao + "*/\n\n";
			}
#line 3056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1426 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\n\t/" + (yyvsp[0]).traducao + "\n";
			}
#line 3064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1432 "sintatica.y" /* yacc.c:1646  */
    {	

				string sFimIF = geraRotulo();
					
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n" + (yyvsp[-2]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-2]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto "+ sFimIF +";\n" + (yyvsp[0]).traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();
			}
#line 3082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1446 "sintatica.y" /* yacc.c:1646  */
    {		
        		string sElseIF = geraRotulo(); 
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sElseIF +";\n" +
				(yyvsp[-1]).traducao + "\tgoto "+ sFimIFs +";\n\n\t" + sElseIF +":\n" + (yyvsp[0]).traducao;        	
        		
        		desempilhaMapa();

			}
#line 3100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1460 "sintatica.y" /* yacc.c:1646  */
    {		
        		string sFimIF = geraRotulo();       	
        		string sElse = geraRotulo();
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//IF COMEÇA\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto "+  sElse + ";\n" +
				(yyvsp[-1]).traducao +"\t"+ sElse +":\n" + (yyvsp[0]).traducao;

				desempilhaMapa();
       		 	
			}
#line 3119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1477 "sintatica.y" /* yacc.c:1646  */
    {
  				sFimIFs = geraRotulo();      	        
  				string sElse = geraRotulo();  			
  				
  				(yyval).traducao = "\t//ELSE COMEÇA\n" + (yyvsp[0]).traducao+"\t" + 
				sFimIFs +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				
  				desempilhaMapa();
			}
#line 3134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1489 "sintatica.y" /* yacc.c:1646  */
    {		
				sFimIFs = geraRotulo();
				
				string sElseIF = geraRotulo();      			
      							
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t//ELSEIF COMEÇA\n"+(yyvsp[-2]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-2]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sFimIFs + ";\n" +
				(yyvsp[0]).traducao + 
				"\n\t" + sFimIFs + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();				
			}
#line 3154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1505 "sintatica.y" /* yacc.c:1646  */
    {		
				string sFimIF = geraRotulo();
				string sElseIF = geraRotulo(); 				
        						
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+(yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sFimIF + ";\n" +
				(yyvsp[-1]).traducao + "\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();			
			}
#line 3172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1519 "sintatica.y" /* yacc.c:1646  */
    {
        		string sFimIF = geraRotulo();
				string sElse = geraRotulo();
				string sElseIF = geraRotulo();  				

				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t//ELSEIF COMEÇA\n"+ (yyvsp[-3]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-3]).labelTemp + ";\n" +
				"\tif(" + (yyval).labelTemp + ") goto " + sElse +";\n" +
				(yyvsp[-1]).traducao + "\tgoto "+ sFimIFs +";\n\n\t" +sElse+":\n"+ (yyvsp[0]).traducao;
				desempilhaMapa();
			}
#line 3191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1536 "sintatica.y" /* yacc.c:1646  */
    {	
  				string sWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFWhile = pilhaDeContextos.top().rotuloFim;				
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t" + sWhile +":\n\t" + "//WHILE COMEÇA\n"+ (yyvsp[-1]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-1]).labelTemp + ";\n" +
				 "\tif("+(yyval).labelTemp+")goto "+sFWhile+"\n"+ (yyvsp[0]).traducao + "\tgoto " + 
				sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 3209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1552 "sintatica.y" /* yacc.c:1646  */
    {	
  				string sDWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFDWhile = pilhaDeContextos.top().rotuloFim;				
				
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\n\t" + sDWhile +":\n"+ "\t//DO_WHILE COMEÇA\n"+ (yyvsp[-1]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-1]).labelTemp + ";\n" +
				(yyvsp[-2]).traducao+"\tif("+(yyval).labelTemp+") goto "+sFDWhile+";\n\tgoto " + 
				sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO_WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 3227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1568 "sintatica.y" /* yacc.c:1646  */
    {
				string sFor = pilhaDeContextos.top().rotuloInicio;
  				string sFFor = pilhaDeContextos.top().rotuloFim;	

				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + sFor +":\n"+"\t//FOR COMEÇA\n"+ (yyvsp[-5]).traducao + (yyvsp[-4]).traducao +
				"\t" + (yyval).labelTemp + " = !" + (yyvsp[-4]).labelTemp + ";\n" +
				 "\t" + "if("+(yyval).labelTemp+") goto "+ sFFor +";\n"+(yyvsp[0]).traducao + (yyvsp[-2]).traducao + "\tgoto "+sFor+";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				
  				desempilhaMapa();
			}
#line 3244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1583 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = "\n\t//SWITCH COMEÇA\n" + (yyvsp[-2]).traducao + "\t" + sFSwitch +":\n\t//SWITCH TERMINA\n";

				desempilhaMapa();
			}
#line 3255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1592 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 3263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1596 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;	
			}
#line 3271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1600 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 3279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1606 "sintatica.y" /* yacc.c:1646  */
    {

				string sFimIF = geraRotulo();
  				sFSwitch = pilhaDeContextos.top().rotuloFim;

				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[-2]).traducao + "\t"+ (yyval).labelTemp + " = !"+ (yyvsp[-2]).labelTemp + "\n\tif( "+(yyval).labelTemp+") goto " +sFimIF + ";\n"+ (yyvsp[0]).traducao + "\n\t" + sFimIF +":\n";
			}
#line 3293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1617 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao + "\n";
			}
#line 3301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1623 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).tipo = "bool";
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).labelTemp = geraLabelTemp("bool");				
				(yyval).traducao = (yyval).valor + "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).labelTemp + " == " + switchPar +";\n";
			}
#line 3313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1633 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-4]).traducao);
				Contexto d = retornarContextoDaVariavel((yyvsp[-6]).nomeVariavel);
				string parametros = "";
				cout << c.mapa[(yyvsp[-6]).nomeVariavel].tipo <<endl;
				if(c.mapa[(yyvsp[-4]).traducao].tipo == "void"){
					cout<<"La funzione "+c.mapa[(yyvsp[-4]).traducao].funcao.nome+" non è compatibile con return perché è nullo."<<endl;	
					exit(1);
				}
				if(c.mapa[(yyvsp[-6]).nomeVariavel].tipo == "undefined"){

				}else if(c.mapa[(yyvsp[-6]).nomeVariavel].tipo != c.mapa[(yyvsp[-4]).traducao].tipo){
					cout<<"Il tipo di restituire di funzione "+c.mapa[(yyvsp[-4]).traducao].funcao.nome+" non è compatibile con "+(yyvsp[-6]).nomeVariavel<<endl;
					exit(1);
				}
				if(c.mapa[(yyvsp[-4]).traducao].funcao.parametros.size() == parametroAux.size()){
					(yyval).traducao = "\n\t//"+c.mapa[(yyvsp[-4]).traducao].funcao.nome+";\n";
					for(auto it_m1 = c.mapa[(yyvsp[-4]).traducao].funcao.parametros.cbegin(), end_m1 = c.mapa[(yyvsp[-4]).traducao].funcao.parametros.cend(),
	        			it_m2 = parametroAux.cbegin(), end_m2 = parametroAux.cend();
	        			it_m1 != end_m1 || it_m2 != end_m2;){
						if(it_m1->second != it_m2->second){
							cout<< "Parametros informados não possuem os mesmos tipos dos enunciados na função "+(yyvsp[-4]).traducao<<endl;
							exit(1);
						}
						parametros += "\t"+it_m1->first + " = "+  it_m2->first+";\n";
						if((it_m1 != end_m1)&&(it_m2 != end_m2)) {
				            ++it_m2;
				            ++it_m1;
				        }			
					}
					if(d.mapa[(yyvsp[-6]).nomeVariavel].tipo == "undefined"){
						d.mapa[(yyvsp[-6]).nomeVariavel].tipo = c.mapa[(yyvsp[-4]).traducao].tipo;
						d.mapa[(yyvsp[-6]).nomeVariavel].labelTemp = geraLabelTemp(d.mapa[(yyvsp[-6]).nomeVariavel].tipo);
						atualizarPilhaContextos(d.mapa[(yyvsp[-6]).nomeVariavel]);

					}

					(yyval).labelTemp = geraLabelTemp(c.mapa[(yyvsp[-4]).traducao].tipo);
					(yyval).traducao += c.mapa[(yyvsp[-4]).traducao].funcao.cabecalho +(yyvsp[-2]).traducao+ parametros + c.mapa[(yyvsp[-4]).traducao].funcao.escopo + "\t"
					+ d.mapa[(yyvsp[-6]).nomeVariavel].labelTemp + " = " + c.mapa[(yyvsp[-4]).traducao].funcao.retorno + ";\n";	
					parametroAux.clear();

				}else{
					cout << "Numero de parametros incorretos"<<endl;
					exit(1);
				}
			}
#line 3365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1681 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).traducao);
				
				string parametros = "";
				if(c.mapa[(yyvsp[-4]).traducao].funcao.parametros.size() == parametroAux.size()){
					(yyval).traducao = "\n\t//"+c.mapa[(yyvsp[-4]).traducao].funcao.nome+";\n";
					for(auto it_m1 = c.mapa[(yyvsp[-4]).traducao].funcao.parametros.cbegin(), end_m1 = c.mapa[(yyvsp[-4]).traducao].funcao.parametros.cend(),
	        			it_m2 = parametroAux.cbegin(), end_m2 = parametroAux.cend();
	        			it_m1 != end_m1 || it_m2 != end_m2;){
						if(it_m1->second != it_m2->second){
							cout<< "Parametros informados não possuem os mesmos tipos dos enunciados na função "+(yyvsp[-4]).traducao<<endl;
							exit(1);
						}
						parametros += "\t"+it_m1->first + " = "+  it_m2->first+";\n";
						if((it_m1 != end_m1)&&(it_m2 != end_m2)) {
				            ++it_m2;
				            ++it_m1;
				        }			
					}

					(yyval).labelTemp = geraLabelTemp(c.mapa[(yyvsp[-4]).traducao].tipo);
					(yyval).traducao += c.mapa[(yyvsp[-2]).traducao].funcao.cabecalho +(yyvsp[-4]).traducao + parametros + c.mapa[(yyvsp[-4]).traducao].funcao.escopo + "\n\t";
					parametroAux.clear();
				}else{
					cout << "Numero de parametros incorretos"<<endl;
					exit(1);
				}
			}
#line 3398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1712 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[0]).nomeVariavel);
				if(c.mapa[(yyvsp[0]).nomeVariavel].funcao.nome == ""){
					cout<<"Funzione "+(yyvsp[0]).nomeVariavel+" non valida"<<endl;
					parametroAux.clear();
					exit(1);
				}
				(yyval).traducao = (yyvsp[0]).nomeVariavel;
			}
#line 3412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1724 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				parametroAux.insert({(yyvsp[-1]).labelTemp, (yyvsp[-1]).tipo});

			}
#line 3422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1732 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				parametroAux.insert({(yyvsp[-1]).labelTemp, (yyvsp[-1]).tipo});
			}
#line 3431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1740 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel(function);
				(yyval).tipo = "void";
				(yyval).labelTemp = "";
				(yyval).valor = "";
				(yyvsp[-2]).traducao = "";
				c.mapa[function].tipo = "void";
				c.mapa[function].funcao.cabecalho = (yyvsp[-2]).traducao;
				c.mapa[function].funcao.escopo = (yyvsp[0]).traducao;	
				c.mapa[function].funcao.traducao = "\n\t//"+ ((yyvsp[-4]).traducao) + ":\n" + (yyvsp[-2]).traducao + c.mapa[function].funcao.escopo + (yyvsp[0]).traducao;
				atualizarPilhaContextos(c.mapa[function]);

				count = 0;
			}
#line 3450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1755 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-4]).traducao);
				(yyval).nomeVariavel = (yyvsp[-4]).traducao;
				(yyval).tipo = retornoR;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "";
				(yyval).traducao = "";
				(yyval).funcao.nome = (yyvsp[-4]).traducao;
				c.mapa[function].funcao.cabecalho = (yyvsp[-2]).traducao;
				c.mapa[function].funcao.escopo = (yyvsp[0]).traducao;
				c.mapa[function].funcao.traducao = "\n\t//"+ ((yyvsp[-4]).traducao) + ":\n";
				atualizarPilhaContextos(c.mapa[function]);

				count = 0;						
			}
#line 3470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1773 "sintatica.y" /* yacc.c:1646  */
    {

				function = (yyvsp[0]).nomeVariavel;
				(retornoR=="")? "undefined" : (yyval).tipo = retornoR ;
				(yyval).nomeVariavel = (yyvsp[0]).nomeVariavel;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).funcao.nome = (yyvsp[0]).nomeVariavel;
				(yyval).traducao = (yyvsp[0]).nomeVariavel;
				adicionaVariavelContexto((yyval));

			}
#line 3486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1787 "sintatica.y" /* yacc.c:1646  */
    {	
				Contexto c = retornarContextoDaVariavel(function);
				
				(yyval).tipo =  (yyvsp[-1]).tipo;
				(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[-1]).valor;
				(yyval).traducao = (yyvsp[-1]).traducao + "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).labelTemp + ";\n" + (yyvsp[0]).traducao; 
				c.mapa[function].funcao.parametros.insert({(yyval).labelTemp, (yyvsp[-1]).tipo});
				adicionaVariavelContexto((yyval));
				atualizarPilhaContextos(c.mapa[function]);
				ultimoTipo = (yyval).tipo;
			}
#line 3504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1801 "sintatica.y" /* yacc.c:1646  */
    {	
				Contexto c = retornarContextoDaVariavel(function);

				(yyval).tipo =  (yyvsp[-2]).tipo;
				(yyval).nomeVariavel = (yyvsp[-1]).nomeVariavel;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "";
				(yyval).traducao = (yyvsp[0]).traducao; 
				adicionaVariavelContexto((yyval));
				c.mapa[function].funcao.parametros.insert({(yyval).labelTemp, (yyval).tipo});				
				atualizarPilhaContextos(c.mapa[function]);
				ultimoTipo = (yyval).tipo;
			}
#line 3522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1815 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;	
			}
#line 3530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1822 "sintatica.y" /* yacc.c:1646  */
    {
				if(count == 0)
					retornoR = "int";
				count++;
			}
#line 3540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1828 "sintatica.y" /* yacc.c:1646  */
    {
				if(count == 0)
					retornoR = "bool";
				count++;
			}
#line 3550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1834 "sintatica.y" /* yacc.c:1646  */
    {
			
				if(count == 0)
					retornoR = "float";
				count++;
			}
#line 3561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1841 "sintatica.y" /* yacc.c:1646  */
    {
				if(count == 0)
					retornoR = "char";
				count++;
			}
#line 3571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1847 "sintatica.y" /* yacc.c:1646  */
    {
				if(count == 0)
					retornoR = "string";
				count++;
			}
#line 3581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1856 "sintatica.y" /* yacc.c:1646  */
    {
			Contexto c = retornarContextoDaVariavel(function);

			if((yyvsp[0]).tipo != retornoR){
				cout<<"Funzione con parametri di ritorno errati"<< endl;
				exit(1);
			}
			(yyval).tipo = (yyvsp[0]).tipo;
			(yyval).labelTemp = geraLabelTemp((yyval).tipo);
			(yyval).traducao = (yyvsp[0]).traducao;
			c.mapa[function].funcao.retorno = (yyvsp[0]).labelTemp ;
			atualizarPilhaContextos(c.mapa[function]);

		}
#line 3600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1871 "sintatica.y" /* yacc.c:1646  */
    {
			cout<<"La funzione richiede parametri di ritorno"<< endl;
			exit(1);
		}
#line 3609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1878 "sintatica.y" /* yacc.c:1646  */
    {

			PilhaContexto copiaPilha = pilhaDeContextos;
			bool achouInterrompivel = 0;
			Contexto c;
        		while(copiaPilha.size() > 1){
        			
        			if(copiaPilha.top().interrompivel == 1){
        				
        				c = copiaPilha.top();
        				achouInterrompivel = 1;
        				          				
        			}        			
        			
        			copiaPilha.pop();
        			
        		}

        		if(copiaPilha.size() == 1 && !achouInterrompivel){
        			indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
					exit(1);
        		}

        		(yyval).traducao = "\t//BREAK_ALL\n\tgoto " + c.rotuloFim + ";\n";

		}
#line 3640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1906 "sintatica.y" /* yacc.c:1646  */
    {
       			
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				(yyval).traducao = "\t//BREAK\n\tgoto " + copiaPilha.top().rotuloFim + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
        		
      		}
#line 3664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1927 "sintatica.y" /* yacc.c:1646  */
    {
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				(yyval).traducao = "\t//CONTINUE\n\tgoto " + copiaPilha.top().rotuloInicio + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
			}
#line 3686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1946 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 3696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1952 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + labelCasting +
					";\n";
					cout<< (yyvsp[-2]).labelTemp;
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " > " + (yyvsp[0]).labelTemp +
					";\n";
				}

			}
#line 3737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1989 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " < " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 2024 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + labelCasting +
					";\n";
					
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " >= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 2060 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + (yyvsp[0]).labelTemp +
					";\n";


				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{	EL:
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " <= " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 2096 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " != " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 2131 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " == " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 2167 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " && " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 3973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 2202 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "bool";
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[(yyvsp[-2]).nomeVariavel].tipo, (yyvsp[0]).tipo);
				string theCasting = "";
				string labelTemp = c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + labelTemp + " || " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 4012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 2237 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 4020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 2243 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).labelTemp = (yyvsp[-1]).labelTemp;
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 4030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 2249 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao +"\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " + " + (yyvsp[0]).labelTemp +" ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 2257 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao +"\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " - " + (yyvsp[0]).labelTemp +" ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 2265 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao +"\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " * " + (yyvsp[0]).labelTemp +" ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 2273 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao +"\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " / " + (yyvsp[0]).labelTemp +" ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 2281 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " + " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " + " + (yyvsp[0]).labelTemp +
					";\n";
				}

				
			}
#line 4125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 2324 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " - " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " - " + (yyvsp[0]).labelTemp +
					";\n";
				}
				
			}
#line 4171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 2366 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " * " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " * " + (yyvsp[0]).labelTemp +
					";\n";
				}
				
			}
#line 4217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 2408 "sintatica.y" /* yacc.c:1646  */
    {
				fazCasting = tabelaDeTipos((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[-2]).labelTemp + ";\n";

					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + labelCasting + " / " + (yyvsp[0]).labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					(yyval).tipo = "float";
					string labelCasting = geraLabelTemp((yyval).tipo);
					theCasting = "\t" + labelCasting + " = (float) " + (yyvsp[0]).labelTemp + ";\n";
					
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + theCasting +"\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					(yyval).tipo = "int";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + (yyvsp[0]).labelTemp +
					";\n";
				}
				else{		
					(yyval).tipo = "float";
					(yyval).labelTemp = geraLabelTemp((yyval).tipo);
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" +
					(yyval).labelTemp + " = " + (yyvsp[-2]).labelTemp + " / " + (yyvsp[0]).labelTemp +
					";\n";
				}
			}
#line 4262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 2449 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "float";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).labelTemp + " = (float) " + (yyvsp[0]).labelTemp +
				";\n";
			}
#line 4274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 2457 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = "int";
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).labelTemp + " = (int) " + (yyvsp[0]).labelTemp +
				";\n";
			}
#line 4286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 2465 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;

				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).nomeVariavel + " = -" + (yyvsp[0]).nomeVariavel +
				";\n";			
			}
#line 4298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 2473 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " + 1 ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 2481 "sintatica.y" /* yacc.c:1646  */
    {
				string sPot = "Potencia_" + to_string(contaPot);
				string sFPot = "Potencia_" + to_string(contaPot+1);
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				string labelMult = geraLabelTemp("int");
				string labelVer = geraLabelTemp("bool");
				string label0 = geraLabelTemp("bool");
				string labelAux = geraLabelTemp((yyvsp[0]).tipo); 

				(yyval).traducao = "\n\t//PONTENCIA\n"+(yyvsp[0]).traducao + "\t" +labelAux+ " = " +(yyvsp[0]).labelTemp+";\n\t"+
				labelVer + " = " + labelAux + " == 0;\n\t" + labelVer + " = !" +labelVer+ ";\n\tif("+labelVer+") goto "+ sPot+";\n\t"+
				labelMult + " = 1" + +";\n\t"+ "goto "+sFPot+";\n\t"+
				sPot +":\n\t" + labelMult + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp +" * 1;\n\t"+
				label0 +" = "+labelAux+" == 0;\n\t"+label0+ " = !"+labelAux+";\n\t"+ "if("+label0+") goto "+sFPot+";\n\t"+
				labelMult + " = " + c.mapa[(yyvsp[0]).nomeVariavel].labelTemp+ " * "+ labelMult + ";" + 
				"\n\t" + labelAux + " = " + labelAux + " - 1 ;\n\t"+
				"goto "+sPot+";\n\t" + sFPot +":\n\t"+
				(yyval).labelTemp + " = " + labelMult +";\n";
				contaPot++;
			}
#line 4338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 2505 "sintatica.y" /* yacc.c:1646  */
    {
				Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);
				(yyval).tipo = c.mapa[(yyvsp[-2]).nomeVariavel].tipo;
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " - 1 ;\n"
				+ "\t" + c.mapa[(yyvsp[-2]).nomeVariavel].labelTemp + " = " + (yyval).labelTemp + ";\n";
			}
#line 4350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 2513 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 4358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 2519 "sintatica.y" /* yacc.c:1646  */
    {
				ultimoTipo = "string";
				tipoGeral = 2;
				(yyval).tipo = "string";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				
				//remover aspas 	
				string removerAspas = (yyvsp[0]).traducao;
				string semAspas = (yyvsp[0]).traducao.erase(0, 1);
				int lenSemAspas = semAspas.length() - 1;
				(yyval).valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
				(yyval).tamanho = (yyval).valor.length();					

				(yyval).varTamString	= geraLabelTemp("string_tam");
				(yyval).traducao = "\n\t" + (yyval).varTamString + " = " + to_string((yyval).tamanho) + ";\n\t" + (yyval).labelTemp + " = (char*)malloc(" + 
				(yyval).varTamString + " * sizeof(char));\n\t" + "strcat(" + (yyval).labelTemp + ", '" + (yyval).valor + "')" +
				";\n";
			}
#line 4381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 2538 "sintatica.y" /* yacc.c:1646  */
    {

                if(variavelExistente((yyvsp[0]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[0]).nomeVariavel);
					if(c.mapa[(yyvsp[0]).nomeVariavel].tipo == "string"){
						if(c.mapa[(yyvsp[0]).nomeVariavel].valor != "null"){						

							(yyval).nomeVariavel = (yyvsp[0]).nomeVariavel;
							(yyval).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;							
							(yyval).valor = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
							(yyval).tamanho =pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tamanho;
							(yyval).varTamString = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].varTamString;
							(yyval).traducao = ""; 

						}
						else{
							std::cout <<c.mapa[(yyvsp[0]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
			}
#line 4418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 2571 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-3]).nomeVariavel);
                	
                	if(c.mapa[(yyvsp[-3]).nomeVariavel].valor != "null"){
                		(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
                		
                		if(stoi((yyvsp[-1]).traducao) < c.mapa[(yyval).nomeVariavel].tamanhoMax){
							(yyval).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp + "[" + (yyvsp[-1]).traducao + "]";							
							(yyval).valor = c.mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = c.mapa[(yyval).nomeVariavel].tipo;
							if(!(yyval).tipo.compare("intP")){
								(yyval).tipo = "int";
							}
							if(!(yyval).tipo.compare("floatP")){
								(yyval).tipo = "float";
							}
							if(!(yyval).tipo.compare("boolP")){
								(yyval).tipo = "bool";
							}
							if(!(yyval).tipo.compare("stringP")){
								(yyval).tipo = "string";
							}
							if(!(yyval).tipo.compare("charP")){
								(yyval).tipo = "char";
							}
							(yyval).traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[(yyvsp[-3]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
#line 4469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 2618 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-6]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-6]).nomeVariavel);
                	
                	if(c.mapa[(yyvsp[-6]).nomeVariavel].valor != "null"){
                		(yyval).nomeVariavel = (yyvsp[-6]).nomeVariavel;
                		
                		if(stoi((yyvsp[-4]).traducao) * stoi((yyvsp[-1]).traducao) < c.mapa[(yyval).nomeVariavel].tamanhoMax){
                			int i, j, valor = 0;
	                		for (i=0;i<=stoi((yyvsp[-4]).traducao);i++)
	                			valor += stoi((yyvsp[-4]).traducao);
	                		for(j=0;j<stoi((yyvsp[-1]).traducao);j++)
	                			valor += 1;

							(yyval).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp + "[" + to_string(valor) + "]";							
							(yyval).valor = c.mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = c.mapa[(yyval).nomeVariavel].tipo;
							if(!(yyval).tipo.compare("intP")){
								(yyval).tipo = "int";
							}
							if(!(yyval).tipo.compare("floatP")){
								(yyval).tipo = "float";
							}
							if(!(yyval).tipo.compare("boolP")){
								(yyval).tipo = "bool";
							}
							if(!(yyval).tipo.compare("stringP")){
								(yyval).tipo = "string";
							}
							if(!(yyval).tipo.compare("charP")){
								(yyval).tipo = "char";
							}
							(yyval).traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[(yyvsp[-6]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
#line 4526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 2673 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-4]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-4]).nomeVariavel);

                	if(c.mapa[(yyvsp[-4]).nomeVariavel].tipo == "string") {
						if(c.mapa[(yyvsp[-4]).nomeVariavel].valor != "null"){						

							(yyvsp[-4]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-4]).tamanho = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tamanho;							
							(yyvsp[-4]).varTamString = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].varTamString;
							(yyvsp[-4]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;

						}
						else{
							(yyvsp[-4]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-4]).tamanho = 0;							
							(yyvsp[-4]).varTamString = geraLabelTemp("string_tam");
							(yyvsp[-4]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
						}
						
							(yyval).labelTemp = geraLabelTemp((yyvsp[-4]).tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + (yyvsp[-2]).valor + (yyvsp[0]).valor;
							(yyvsp[-4]).valor = 	concat;				
							(yyvsp[-4]).tamanho = (yyvsp[-4]).valor.length() - 1;

							

							(yyval).traducao = "\n\t//concatenacao\n" + (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\n\t" + varTamString + " = " + (yyvsp[-2]).varTamString + " + " + (yyvsp[0]).varTamString + ";\n" +
							"\t" + (yyval).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[-2]).labelTemp + ");\n" +
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[0]).labelTemp + ");\n" +
							"\tfree( " + (yyvsp[-4]).labelTemp + " );\n" + 
							"\t" + (yyvsp[-4]).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + (yyvsp[-4]).labelTemp + ", " + (yyval).labelTemp + ");\n" + 
							"\t"+ (yyvsp[-4]).varTamString + " = " + varTamString + ";\n";									
										
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}				
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}	
			}
#line 4581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 2724 "sintatica.y" /* yacc.c:1646  */
    {	
				if(variavelExistente((yyvsp[-2]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-2]).nomeVariavel);

                	if(c.mapa[(yyvsp[-2]).nomeVariavel].tipo == "string") {
						if(c.mapa[(yyvsp[-2]).nomeVariavel].valor != "null"){						

							(yyvsp[-2]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-2]).tamanho = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tamanho;							
							(yyvsp[-2]).varTamString = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].varTamString;
							(yyvsp[-2]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;

						}
						else{
							(yyvsp[-2]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;														
							(yyvsp[-2]).tamanho = 0;							
							(yyvsp[-2]).varTamString = geraLabelTemp("string_tam");
							(yyvsp[-2]).tipo = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].tipo;
						}
						
							(yyval).labelTemp = geraLabelTemp((yyvsp[-2]).tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + (yyvsp[-2]).valor + (yyvsp[0]).valor;
							(yyvsp[-2]).valor = 	concat;				
							(yyvsp[-2]).tamanho = (yyvsp[-2]).valor.length() - 1;

							

							(yyval).traducao = "\n\t//.= concatenacao\n"+ (yyvsp[0]).traducao+ "\t" + varTamString + " = " + (yyvsp[-2]).varTamString + " + " + (yyvsp[0]).varTamString + ";\n" +
							"\t" + (yyval).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[-2]).labelTemp + ");\n" +
							"\tstrcat(" + (yyval).labelTemp + ", " + (yyvsp[0]).labelTemp + ");\n" +
							"\tfree( " + (yyvsp[-2]).labelTemp + " );\n" + 
							"\t" + (yyvsp[-2]).labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + (yyvsp[-2]).labelTemp + ", " + (yyval).labelTemp + ");\n" + 
							"\t"+ (yyvsp[-2]).varTamString + " = " + varTamString + ";\n" + 
							"\tfree( " + (yyval).labelTemp + " );\n";									
										
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}				
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}	
			}
#line 4637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 2778 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 4645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 2784 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("int");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 4654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 2789 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("float");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 4663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 2794 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("bool");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 4672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 2799 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("string");	
					(yyval).varTamString = geraLabelTemp("string_tam");			

					//remover aspas 	
					string removerAspas = (yyvsp[-1]).traducao;
					string semAspas = (yyvsp[-1]).traducao.erase(0, 1);
					int lenSemAspas = semAspas.length() - 1;
					(yyval).valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
					(yyval).tamanho = (yyval).valor.length() + 1;

					(yyval).traducao = "\n\t" + (yyval).varTamString + " = " + to_string((yyval).tamanho) + ";\n\t" + (yyval).labelTemp + " = (char*)malloc(" + 
					(yyval).varTamString + " * sizeof(char));\n\t" + "strcat(" + (yyval).labelTemp + ", '" + (yyval).valor + "')" +
					";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 4692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 2815 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).labelTemp = geraLabelTemp("char");				
					(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[-1]).valor + ";\n\tcout << " + (yyval).labelTemp + " << endl;\n" + (yyvsp[0]).traducao;
				}
#line 4701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 2820 "sintatica.y" /* yacc.c:1646  */
    {
					if(variavelExistente((yyvsp[-1]).nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
	                	if(c.mapa[(yyvsp[-1]).nomeVariavel].valor != "null"){      
	                		(yyvsp[-1]).labelTemp = pilhaDeContextos.top().mapa[(yyval).nomeVariavel].labelTemp;		          		                		
	                		(yyval).traducao = "\tcout << " + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp +" << endl;\n" + (yyvsp[0]).traducao;
	                	}
						else {
							std::cout <<c.mapa[(yyvsp[-1]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
#line 4723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 2838 "sintatica.y" /* yacc.c:1646  */
    {
					if(variavelExistente((yyvsp[-4]).nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel((yyvsp[-4]).nomeVariavel);
	                	if(c.mapa[(yyvsp[-4]).nomeVariavel].valor != "null"){
	                		if(stoi((yyvsp[-2]).traducao) < c.mapa[(yyvsp[-4]).nomeVariavel].tamanhoMax) {     
	                			(yyvsp[-4]).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp;		          		                		
	                			(yyval).traducao = "\tcout << " + c.mapa[(yyvsp[-4]).nomeVariavel].labelTemp + "[" + (yyvsp[-2]).traducao + "] << endl;\n" + (yyvsp[0]).traducao;
	                		}
	                		else{
	                			indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
	                			exit(1);
	                		}
	                	}
						else {
							std::cout <<c.mapa[(yyvsp[-4]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
#line 4751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 2862 "sintatica.y" /* yacc.c:1646  */
    {
					if(variavelExistente((yyvsp[-7]).nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel((yyvsp[-7]).nomeVariavel);
	                	if(c.mapa[(yyvsp[-7]).nomeVariavel].valor != "null"){

	                		if(stoi((yyvsp[-5]).traducao) * stoi((yyvsp[-2]).traducao) < c.mapa[(yyvsp[-7]).nomeVariavel].tamanhoMax) {   
	                			string labelPos = "";
	                			
	                			int i, j, valor = 0;
	                			for (i=0;i<=stoi((yyvsp[-5]).traducao);i++)
	                				valor += stoi((yyvsp[-5]).traducao);
	                			for(j=0;j<stoi((yyvsp[-2]).traducao);j++)
	                				valor += 1;
	                			
	                			labelPos += to_string(valor);

	                			(yyvsp[-7]).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp;		          		                		
	                			(yyval).traducao = "\tcout << " + c.mapa[(yyvsp[-7]).nomeVariavel].labelTemp + "[" + labelPos + "] << endl;\n" + (yyvsp[0]).traducao;
	                		}
	                		else{
	                			indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
	                			exit(1);
	                		}
	                	}
						else {
							std::cout <<c.mapa[(yyvsp[-7]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
#line 4790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 2897 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = "";
				}
#line 4798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 2902 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 4806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 2906 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 4814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 2911 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-1]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-1]).nomeVariavel);
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "int") {                		
                		(yyval).traducao = "\tscanf(\"%d\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "float") {
                		(yyval).traducao = "\tscanf(\"%f\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "char") {
                		(yyval).traducao = "\tscanf(\"%c\", &" + c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "string") {
                		string varTamString = c.mapa[(yyvsp[-1]).nomeVariavel].varTamString;
                	
                		string var = c.mapa[(yyvsp[-1]).nomeVariavel].labelTemp;
                		string varT = geraLabelTemp("char");
                		string numVarT = geraLabelTemp("string_tam");
                		string rotI = "ROT_STR_LET_IN_" + to_string(nCL);
                		string rotF = "ROT_STR_LET_FIM_" + to_string(nCL);

                		(yyval).traducao = "\n\tif (" + varTamString + " > 0) free(" + var + ");\n" +
						"\t" + var + " = (char*) malloc(" + varTamString +" * sizeof(char));\n" +
						"\t" + numVarT + " = " + varTamString + "\n" + 
						"\t" + varTamString + " = 0;\n\t" + rotI + ":\n" + 						
						'\t' + varT + " = getchar();\n" + 
						"\tif(" + varT + " == \'\\0\' ) goto " + rotF + ";\n" +
						"\tif(" + varT + " == \'\\n\' ) goto " + rotF + ";\n" + 
						'\t' + var + '[' + varTamString + "] = " + varT + ";\n" +
						'\t' + varTamString + " = " + varTamString + " + 1;\n" +
						"\tif(" + varTamString + " < " + numVarT + ") goto " + rotI + ";\n" +
						'\t' + varTamString + " = " + varTamString + " + " + numVarT + ";\n" +
						'\t' + var + " = (char*) realloc(" + var + ", " + varTamString + ");\n" + 
						"\tgoto " + rotI + ";\n" + '\t' + rotF + ":\n" +
						'\t' + varTamString + " = " + varTamString + " + 1;\n" +
						'\t' + var + '[' + varTamString + "] = \'\\0\';\n";						
                	}        
                	if(c.mapa[(yyvsp[-1]).nomeVariavel].tipo == "undefined")
                	{
                		indicaErro(MSG_ERRO_TIPO_INDEFINIDO);
                		exit(1);
                	}
                }
                else{
					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}	
			}
#line 4867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 2963 "sintatica.y" /* yacc.c:1646  */
    {
				ultimoTipo = "int";
				tipoGeral = 1;
				(yyval).tipo = "int";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 4881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 2973 "sintatica.y" /* yacc.c:1646  */
    {	
				ultimoTipo = "float";
				tipoGeral = 1;
				(yyval).tipo = "float";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 4895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 2983 "sintatica.y" /* yacc.c:1646  */
    {

                if(variavelExistente((yyvsp[0]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[0]).nomeVariavel);

					if(c.mapa[(yyvsp[0]).nomeVariavel].tipo == "float" || c.mapa[(yyvsp[0]).nomeVariavel].tipo == "int"){
						if(c.mapa[(yyvsp[0]).nomeVariavel].valor != "null"){						


							(yyval).nomeVariavel = (yyvsp[0]).nomeVariavel;
							(yyval).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp;							
							(yyval).valor = c.mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = c.mapa[(yyval).nomeVariavel].tipo;
							(yyval).traducao = ""; 
							switchPar = (yyval).labelTemp;
						}
						else{
							std::cout <<c.mapa[(yyvsp[0]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);									
					}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
			}
#line 4932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 3016 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-3]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-3]).nomeVariavel);
                	
                	if(c.mapa[(yyvsp[-3]).nomeVariavel].valor != "null"){
                		(yyval).nomeVariavel = (yyvsp[-3]).nomeVariavel;
                		
                		if(stoi((yyvsp[-1]).traducao) < c.mapa[(yyval).nomeVariavel].tamanhoMax){
							(yyval).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp + "[" + (yyvsp[-1]).traducao + "]";							
							(yyval).valor = c.mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = c.mapa[(yyval).nomeVariavel].tipo;
							if(!(yyval).tipo.compare("intP")){
								(yyval).tipo = "int";
							}
							if(!(yyval).tipo.compare("floatP")){
								(yyval).tipo = "float";
							}
							if(!(yyval).tipo.compare("boolP")){
								(yyval).tipo = "bool";
							}
							if(!(yyval).tipo.compare("stringP")){
								(yyval).tipo = "string";
							}
							if(!(yyval).tipo.compare("charP")){
								(yyval).tipo = "char";
							}
							(yyval).traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[(yyvsp[-3]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
#line 4983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 3063 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelExistente((yyvsp[-6]).nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel((yyvsp[-6]).nomeVariavel);
                	
                	if(c.mapa[(yyvsp[-6]).nomeVariavel].valor != "null"){
                		(yyval).nomeVariavel = (yyvsp[-6]).nomeVariavel;
                		
                		if(stoi((yyvsp[-4]).traducao) * stoi((yyvsp[-1]).traducao) < c.mapa[(yyval).nomeVariavel].tamanhoMax){
                			int i, j, valor = 0;
	                		for (i=0;i<=stoi((yyvsp[-4]).traducao);i++)
	                			valor += stoi((yyvsp[-4]).traducao);
	                		for(j=0;j<stoi((yyvsp[-1]).traducao);j++)
	                			valor += 1;

							(yyval).labelTemp = c.mapa[(yyval).nomeVariavel].labelTemp + "[" + to_string(valor) + "]";							
							(yyval).valor = c.mapa[(yyval).nomeVariavel].valor;
							(yyval).tipo = c.mapa[(yyval).nomeVariavel].tipo;
							if(!(yyval).tipo.compare("intP")){
								(yyval).tipo = "int";
							}
							if(!(yyval).tipo.compare("floatP")){
								(yyval).tipo = "float";
							}
							if(!(yyval).tipo.compare("boolP")){
								(yyval).tipo = "bool";
							}
							if(!(yyval).tipo.compare("stringP")){
								(yyval).tipo = "string";
							}
							if(!(yyval).tipo.compare("charP")){
								(yyval).tipo = "char";
							}
							(yyval).traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[(yyvsp[-6]).nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
#line 5040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 3116 "sintatica.y" /* yacc.c:1646  */
    {
				ultimoTipo = "bool";
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "0";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 5053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 3125 "sintatica.y" /* yacc.c:1646  */
    {
				ultimoTipo = "bool";
				(yyval).tipo = "bool";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = "1";
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyval).valor +
				";\n";
			}
#line 5066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 3134 "sintatica.y" /* yacc.c:1646  */
    {
				tipoGeral = 2;
				(yyval).tipo = "char";
				(yyval).labelTemp = geraLabelTemp((yyval).tipo);
				(yyval).valor = (yyvsp[0]).traducao;
				(yyval).traducao = "\t" + (yyval).labelTemp + " = " + (yyvsp[0]).traducao +
				";\n";
			}
#line 5079 "y.tab.c" /* yacc.c:1646  */
    break;


#line 5083 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  return yyresult;
}
#line 3145 "sintatica.y" /* yacc.c:1906  */


#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
