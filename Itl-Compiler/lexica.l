%{
	#include <string>
%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]
CARACTERES [A-Za-z]
CARACTER "'"({CARACTERES}|{DIGITO}+)"'"
STRING  "\""({CARACTERES}|{ESPACO}|{DIGITO}+)*"\""

DELIMITADOR {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
NOMEVAR {LETRA}({LETRA}|{NUM})*
BOOL [true]|[false]
LINECOMENT "/"([^\"\n]|\\\")*
COMENT ("//"((([^\"\n]|\\\")|\n)*)"|")


%%

"\n"				{contaLinha();}
{DELIMITADOR}		{}
"essere"			{return TOKEN_VAR;}
"principale"		{return TOKEN_MAIN;}
"iniziare"			{return TOKEN_BEGIN;}

"tutto"				{yylval.tipo = "int"; return TOKEN_INT;}
"reale"				{yylval.tipo = "float"; return TOKEN_FLOAT;}
"doppio"			{yylval.tipo = "doble"; return TOKEN_DOUBLE;}
"carat"				{yylval.tipo = "carat"; return TOKEN_CHAR;}
"boole"             {yylval.tipo = "bool"; return TOKEN_BOOL;}
"corda"				{yylval.tipo = "string"; return TOKEN_STR;}

"nullo" 			{return TOKEN_NULL;}
"vuoto" 			{return TOKEN_VOID;}

"strut"				{return TOKEN_STRUCT;}

"se"				{return TOKEN_IF;}
"altri"				{return TOKEN_ELSE;}
"altrise"			{return TOKEN_ELSEIF;}
"scelta"			{return TOKEN_SWITCH;}
"caso"				{return TOKEN_CASE;}
"predefinito"		{return TOKEN_DEFAULT;}

"rompere" 			{return TOKEN_BREAK;}
"romperetutti"		{return TOKEN_BREAK_ALL;}
"continuare"		{return TOKEN_CONTINUE;}

"fare" 				{return TOKEN_DO;}
"per" 				{return TOKEN_FOR;}
"mentre"			{return TOKEN_WHILE;}

"funzione"			{return TOKEN_FUNCT;}
"ritorno"			{return TOKEN_RETURN; }
"stampare"			{return TOKEN_PRINT; }
"leggere"			{return TOKEN_SCANF; }

">"					{return TOKEN_MAIOR; }	
"<"					{return TOKEN_MENOR; }	
">="				{return TOKEN_MAIORIGUAL; }	
"<="				{return TOKEN_MENORIGUAL; }	
"=="				{return TOKEN_IGUAL; }	
"!!"				{return TOKEN_DIF; }	
"->"				{return TOKEN_IMP; }

"+="				{return TOKEN_MAISIGUAL; }	
"-="				{return TOKEN_MENOSIGUAL; }	
"*="				{return TOKEN_VEZESIGUAL; }	
"/="				{return TOKEN_DIVIDEIGUAL; }	
".="				{return TOKEN_PONTOIGUAL; }	
"**"				{return TOKEN_POTENCIA;}

"="					{return TOKEN_ATR; }

"&&"				{return TOKEN_E; }
"||"				{return TOKEN_OU; }

"(reale)"           {return TOKEN_CONV_FLOAT; }
"(tutto)"			{return TOKEN_CONV_INT; }

"falso"				{yylval.tipo = "bool";yylval.traducao = yytext; return TOKEN_BOOLEAN_FALSE; }
"vero"				{yylval.tipo = "bool";yylval.traducao = yytext; return TOKEN_BOOLEAN_TRUE; }

"</"				{return TOKEN_COM_INT;}
"\\<"				{contaLinha(); return TOKEN_COM_END;}

{COMENT}			{ yylval.traducao = yytext; return TOKEN_COMENT; }
{LINECOMENT}		{ yylval.traducao = yytext; return TOKEN_LINECOMENT; }
[()[\];:,{}]		{ return *yytext; }	
[+\-*/]				{ return *yytext; }
{NUM}			    { yylval.tipo = "int";yylval.traducao = yytext; return TOKEN_NUM_INT; }
{REAL}				{ yylval.tipo = "float";yylval.traducao = yytext; return TOKEN_NUM_FLOAT; }
{CARACTER}			{ yylval.tipo = "char";yylval.traducao = yytext; return TOKEN_CARACTERE; }
{STRING}			{ yylval.tipo = "string";yylval.traducao = yytext; return TOKEN_STRING; }
{NOMEVAR}			{ yylval.nomeVariavel = yytext; return TOKEN_NOME; }
.					{ return *yytext; }


%%