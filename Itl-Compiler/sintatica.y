%{
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
 

%}

%token TOKEN_MAIN
%token TOKEN_BEGIN
%token TOKEN_VAR

%token TOKEN_INT
%token TOKEN_FLOAT
%token TOKEN_DOUBLE
%token TOKEN_CHAR
%token TOKEN_BOOL
%token TOKEN_STR

%token TOKEN_NULL
%token TOKEN_VOID
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_ELSEIF
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_DEFAULT
%token TOKEN_IMP

%token TOKEN_BREAK_ALL
%token TOKEN_BREAK
%token TOKEN_CONTINUE

%token TOKEN_DO
%token TOKEN_FOR
%token TOKEN_WHILE
%token TOKEN_PRINT
%token TOKEN_ERROR
%token TOKEN_STRUCT

%token TOKEN_NOME
%token TOKEN_NUM_INT
%token TOKEN_NUM_FLOAT
%token TOKEN_BOOLEAN_FALSE
%token TOKEN_BOOLEAN_TRUE
%token TOKEN_CARACTERE
%token TOKEN_STRING
%token TOKEN_POTENCIA

%token TOKEN_MAIOR
%token TOKEN_MENOR
%token TOKEN_DIF
%token TOKEN_IGUAL
%token TOKEN_MAIORIGUAL
%token TOKEN_MENORIGUAL
%token TOKEN_E
%token TOKEN_OU

%token TOKEN_MAISIGUAL
%token TOKEN_MENOSIGUAL
%token TOKEN_VEZESIGUAL
%token TOKEN_DIVIDEIGUAL
%token TOKEN_PONTOIGUAL


%token TOKEN_CONV_FLOAT
%token TOKEN_CONV_INT

%token TOKEN_ATR
%token TOKEN_SCANF

%token TOKEN_COMENT
%token TOKEN_COM_INT 
%token TOKEN_COM_END 
%token TOKEN_LINECOMENT

%token TOKEN_FUNCT
%token TOKEN_RETURN

%left TOKEN_E TOKEN_OU 
%left TOKEN_MAIOR TOKEN_MENOR TOKEN_MAIORIGUAL TOKEN_MENORIGUAL TOKEN_DIF TOKEN_IGUAL 
%left ','
%left '+' '-'
%left '*' '/'
%left '(' 
%left TOKEN_CONV_FLOAT TOKEN_CONV_INT


%start S

%%

S		    : BLOCO_GLOBAL TOKEN_BEGIN TOKEN_MAIN '(' ')' BLOCO_MAIN 
            {
            	
            	$$.labelTemp = geraLabelFinal();
				cout << "/*Compilador ITL*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\nint main(void){\n" <<
				$$.labelTemp << $1.traducao + $6.traducao << "\treturn 0;\n}" << endl; 							
				
			}

BLOCO_GLOBAL: BLOCO_MAIN
			| EMP_GLOBAL DCL_GLOBAL
			{
				$$.traducao = $2.traducao;
			}
			;

EMP_GLOBAL	:
			{	
				//Empilha o Escopo Global
				empilhaMapa(0,"","");
			}

BLOCO_MAIN	: EMP_MAIN '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			| BLOCO_NI
			| BLOCO_LOOP
			;

EMP_MAIN 	:
			{
				//Empilha o Main
				empilhaMapa(0,"","");
			}

BLOCO_NI	: EMP_NI '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			;

BLOCO_FUN 	: '{' COMANDOS'}' 
			{
				$$.traducao = $2.traducao;
			}
			;

BLOCO_FUN_RET: '{' COMANDOS RETURN ';''}'
			{
				$$.traducao = $2.traducao + $3.traducao;
			}
			;

EMP_NI 		:
			{
				//Empilha o Bloco não interrompível
				empilhaMapa(0,"","");
			}
			;

BLOCO_LOOP	: EMP_LOOP '{' COMANDOS '}'
			{
				$$.traducao = $3.traducao;
			}
			;

BLOCO_SWITCH: EMP_LOOP '(' CASES ')'
			{
				$$.traducao = $3.traducao;
			}
			;	

EMP_LOOP	:
			{
				//Empilha o Bloco interrompível
				empilhaMapa(1,geraRotulo(),geraRotulo());
			}
			;						

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			| 
			{
				$$.traducao = "";
			}
			;

COMANDO 	: DCL ';'
			| ATR
			| ATR_RL
			| CONCATENACAO ';'
			| IF
			| SWITCH
			| WHILE
			| DO_WHILE
			| FOR
			| FUNCTION
			| BREAK ';'
			| SCANF ';'
			| PRINT ';'
     	 	| CONTINUE ';'
			| COMENT
			| BREAK_ALL ';'
			;

ATR_RL		: TOKEN_NOME TOKEN_ATR ERL ';'
			{
				$$.traducao = verificaErros($1, $3, 2);
			}
			;

ATR 		: TOKEN_NOME TOKEN_ATR E ';'
			{
				$$.traducao = verificaErros($1, $3, 1);
			}
			| TOKEN_NOME TOKEN_ATR ES ';'
			{
				$$.traducao = verificaErros($1, $3, 1);
			}
			| FUNCTION_CALL
			;

DCL_GLOBAL	: DCL ';' DCL_GLOBAL
			{
				$$.traducao = $1.traducao + $3.traducao;
			}
			|
			{
				$$.traducao = "";
			}
			;				

DCL 		: TOKEN_VAR TOKEN_NOME TOKEN_ATR E MLTVAR
			{
				
				Contexto c = retornarContextoDaVariavel($4.nomeVariavel);
				string tipo;
				string valor;
				string traducao;
				string labelTemp;

				if(c.mapa[$4.nomeVariavel].tipo == ""){
					tipo = $4.tipo;
					valor = $4.valor;
					traducao = $4.traducao;
					labelTemp = $4.labelTemp;
				}else{
					tipo = c.mapa[$4.nomeVariavel].tipo;
					valor = c.mapa[$4.nomeVariavel].valor;
					traducao = c.mapa[$4.nomeVariavel].traducao;
					labelTemp = c.mapa[$4.nomeVariavel].labelTemp;
				}				
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = $4.tipo;
					$$.valor = valor;			

					if(tipo != $$.tipo ){																
						indicaErro(MSG_ERRO_TIPO);
						exit(1);		
					}				
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.valor = traducao;
					$$.traducao = $4.traducao + "\t" + $$.labelTemp + " = " + labelTemp + ";\n" + $5.traducao; 

					adicionaVariavelContexto($$);

					ultimoTipo = $$.tipo;
				}

			}
			| TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' TOKEN_ATR '{' E MLTVAR_VET '}' MLTVAR
			{
				tamanhoVetor += 1;
				if(stoi($4.traducao) == tamanhoVetor){
					
					int compTipos;
					if($9.tipo.compare("umElemento") == 0)
						compTipos = 1;
					else
					 	compTipos = !$8.tipo.compare($9.tipo);

					if(compTipos){
						if($8.tipo.compare("int") == 0)
							$$.tipo = "intP";					
						if($8.tipo.compare("float") == 0)
							$$.tipo = "floatP";
						if($8.tipo.compare("bool") == 0)
							$$.tipo = "boolP";
						if($8.tipo.compare("char") == 0)
							$$.tipo = "charP";
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ($8.tipo.compare("int") == 0){
						c = nI - tamanhoVetor + 1;
						s += "TMP_INT_"; 
					}
					if ($8.tipo.compare("float") == 0){
						c = nF - tamanhoVetor + 1;
						s += "TMP_FLOAT_";
					}
					if ($8.tipo.compare("bool") == 0){
						c = nB - tamanhoVetor + 1;
						s += "TMP_BOOL_";
					}
					if ($8.tipo.compare("char") == 0){
						c = nC - tamanhoVetor + 1;
						s += "TMP_CHAR_";
					}


					$$.labelTemp = geraLabelTemp($$.tipo);	
					string labelAux = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoVetor ; i++){
						labelVetor += "\t" + $$.labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					$$.traducao = $8.traducao + $9.traducao + 
					"\t" + labelAux + " = " + to_string(tamanhoVetor) + ";\n" +
					"\t" + $$.labelTemp + " = (" + $8.tipo + "*)malloc(" + labelAux + " * sizeof(" + $8.tipo +"));\n" +
					labelVetor;
					
					$$.nomeVariavel = $2.nomeVariavel;									
					$$.tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					$$.tamanhoMax = stoi($4.traducao);
					$$.valor = "preenchido";

					adicionaVariavelContexto($$);
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
			| TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' '[' TOKEN_NUM_INT ']' TOKEN_ATR '{' '[' E MLTVAR_VET ']' MLTVAR_MAT '}' MLTVAR
			{
				tamanhoMatriz += tamanhoVetor + 1;
				if(stoi($4.traducao) * stoi($7.traducao) == tamanhoMatriz){	

										

					int compTipos, compTipos2;
					if (($13.tipo.compare("umElemento") == 0) && ($15.tipo.compare("umElemento") == 0)) {
						compTipos = 1;
						compTipos2 = 1;
					}	
					else if(stoi($7.traducao) == 1 and ($13.tipo.compare("umElemento") == 0)){
						compTipos = 1;
						compTipos2 = !$12.tipo.compare($15.tipo);
					}
					else if(stoi($4.traducao) == 1 and ($15.tipo.compare("umElemento") == 0)){
						compTipos = !$12.tipo.compare($13.tipo);
						compTipos2 = 1 ;
					}
					else{
					 	compTipos = !$12.tipo.compare($13.tipo);
					 	compTipos2 = !$12.tipo.compare($15.tipo);	
					}

					if(compTipos == 1 and compTipos2 == 1){
						if($12.tipo.compare("int") == 0)
							$$.tipo = "intP";					
						if($12.tipo.compare("float") == 0)
							$$.tipo = "floatP";
						if($12.tipo.compare("bool") == 0)
							$$.tipo = "boolP";
						if($12.tipo.compare("char") == 0)
							$$.tipo = "charP";
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ($12.tipo.compare("int") == 0){
						c = nI - tamanhoMatriz + 1;
						s += "TMP_INT_"; 
					}
					if ($12.tipo.compare("float") == 0){
						c = nF - tamanhoMatriz + 1;
						s += "TMP_FLOAT_";
					}
					if ($12.tipo.compare("bool") == 0){
						c = nB - tamanhoMatriz + 1;
						s += "TMP_BOOL_";
					}
					if ($12.tipo.compare("char") == 0){
						c = nC - tamanhoMatriz + 1;
						s += "TMP_CHAR_";
					}


					$$.labelTemp = geraLabelTemp($$.tipo);	
					string labelAux = geraLabelTemp("int");
					string labelAux2 = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoMatriz ; i++){
						labelVetor += "\t" + $$.labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					$$.traducao = $12.traducao + $13.traducao + $15.traducao +
					"\n\t" + labelAux + " = " + $4.traducao + ";\n" +
					"\t" + labelAux2 + " = " + $7.traducao + ";\n" +
					"\t" + $$.labelTemp + " = (" + $12.tipo + "*)malloc(" + labelAux + " * " + labelAux2 + " * sizeof(" + $12.tipo +"));\n" +
					labelVetor;
					
					$$.nomeVariavel = $2.nomeVariavel;									
					$$.tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					tamanhoMatriz = 0;
					$$.tamanhoMax = stoi($4.traducao) * stoi($7.traducao);
					$$.valor = "preenchido";

					adicionaVariavelContexto($$);
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
			| TOKEN_VAR TOKEN_NOME TOKEN_ATR ES MLTVAR_STRING
			{

				if(variavelExistente($2.nomeVariavel, 'd')){
					if(tipoGeral == 2){
						$$.tipo = "string";
						$$.valor = $4.valor;						

						if($4.tipo != $$.tipo ){																
							indicaErro(MSG_ERRO_TIPO);
							exit(1);		
						}
						$$.tamanho = $4.tamanho;
						$$.varTamString = $4.varTamString;
						$$.nomeVariavel = $2.nomeVariavel;						
						$$.labelTemp = geraLabelTemp($$.tipo);
						$$.traducao = $4.traducao +  "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 

						adicionaVariavelContexto($$);
					}else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}

				}

			}
			| TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' TOKEN_ATR '{' ES MLTVAR_VET '}' MLTVAR_STRING
			{
				tamanhoVetor += 1;
				if(stoi($4.traducao) == tamanhoVetor){
					
					int compTipos;
					if($9.tipo.compare("umElemento") == 0)
						compTipos = 1;
					else
					 	compTipos = !$8.tipo.compare($9.tipo);

					if(compTipos){
						if($8.tipo.compare("string") == 0)
							$$.tipo = "stringP";					
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ($8.tipo.compare("string") == 0){
						c = nS - tamanhoVetor + 1;
						s += "TMP_STRING_"; 
					}

					$$.labelTemp = geraLabelTemp($$.tipo);	
					string labelAux = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoVetor ; i++){
						labelVetor += "\t" + $$.labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					$$.traducao = $8.traducao + $9.traducao + 
					"\n\t" + labelAux + " = " + to_string(tamanhoVetor) + ";\n" +
					"\t" + $$.labelTemp + " = (char*)malloc(" + labelAux + " * sizeof(char));\n" +
					labelVetor;
					
					$$.nomeVariavel = $2.nomeVariavel;									
					$$.tamanho = tamanhoVetor;
					tamanhoVetor = 0;

					$$.tamanhoMax = stoi($4.traducao);
					$$.valor = "preenchido";

					adicionaVariavelContexto($$); 
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
			|  TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' '[' TOKEN_NUM_INT ']' TOKEN_ATR '{' '[' ES MLTVAR_VET ']' MLTVAR_MAT '}' MLTVAR
			{
				tamanhoMatriz += tamanhoVetor + 1;
				if(stoi($4.traducao) * stoi($7.traducao) == tamanhoMatriz){									
					int compTipos, compTipos2;

					if (($13.tipo.compare("umElemento") == 0) && ($15.tipo.compare("umElemento") == 0)) {
						compTipos = 1;
						compTipos2 = 1;
					}	
					else if(stoi($7.traducao) == 1 and ($13.tipo.compare("umElemento") == 0)){
						compTipos = 1;
						compTipos2 = !$12.tipo.compare($15.tipo);
					}
					else if(stoi($4.traducao) == 1 and ($15.tipo.compare("umElemento") == 0)){
						compTipos = !$12.tipo.compare($13.tipo);
						compTipos2 = 1 ;
					}					
					else{
					 	compTipos = !$12.tipo.compare($13.tipo);
					 	compTipos2 = !$12.tipo.compare($15.tipo);	
					}

					if(compTipos == 1 and compTipos2 == 1){
						if($12.tipo.compare("string") == 0)
							$$.tipo = "stringP";	
					}
					else{
						indicaErro(MSG_ERRO_TIPO);
						exit(1);
					}
					int i = 0, c;
					string s;
					string labelVetor;
					if ($12.tipo.compare("string") == 0){
						c = nS - tamanhoMatriz + 1;
						s += "TMP_STRING_"; 
					}


					$$.labelTemp = geraLabelTemp($$.tipo);	
					string labelAux = geraLabelTemp("int");
					string labelAux2 = geraLabelTemp("int");

					for(i = 0 ;i < tamanhoMatriz ; i++){
						labelVetor += "\t" + $$.labelTemp + "[" + to_string(i) + "] = " + s + to_string(c) + ";\n"; 
						c++;
					}

					$$.traducao = $12.traducao + $13.traducao + $15.traducao +
					"\n\t" + labelAux + " = " + $4.traducao + ";\n" +
					"\t" + labelAux2 + " = " + $7.traducao + ";\n" +
					"\t" + $$.labelTemp + "(char*)malloc(" + labelAux + " * " + labelAux2 + " * sizeof(char));\n" +
					labelVetor;
					
					$$.nomeVariavel = $2.nomeVariavel;									
					$$.tamanho = tamanhoVetor;
					tamanhoVetor = 0;
					tamanhoMatriz = 0;
					$$.tamanhoMax = stoi($4.traducao) * stoi($7.traducao);
					$$.valor = "preenchido";

					adicionaVariavelContexto($$);
				}
				else{
					indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
					exit(1);
				} 
			}
			|TOKEN_VAR TOKEN_NOME MLTVAR
			{	
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "undefined";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $3.traducao;
					adicionaVariavelContexto($$);
										
				}
			}
			| TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' MLTVAR
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "undefined";
					$$.valor = "null";
					$$.tamanhoMax = stoi($4.traducao);				
					$$.tamanho = 0;	
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $6.traducao;
					adicionaVariavelContexto($$);
										
				}
			}
			| TOKEN_VAR TOKEN_NOME '[' TOKEN_NUM_INT ']' '[' TOKEN_NUM_INT ']' MLTVAR
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "undefined";
					$$.valor = "null";
					$$.tamanhoMax = stoi($4.traducao);				
					$$.tamanhoMax2 = stoi($7.traducao);				
					$$.tamanho = 0;
					$$.tamanho2 = 0;	
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $9.traducao;
					adicionaVariavelContexto($$);
										
				}
			}
			| E
			;

MLTVAR_MAT: ',' '[' E MLTVAR_VET ']' MLTVAR_MAT
			{
				$$.traducao = $3.traducao + $4.traducao + $6.traducao;
				tamanhoVetor += 1;

				
				int compTipos;
				if(!$4.tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !$3.tipo.compare($4.tipo);;
				}


				if(compTipos){
					compTipos = !$4.tipo.compare($6.tipo);
					if(compTipos){
						$$.tipo = $4.tipo;					
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
			| ',' '[' E MLTVAR_VET ']'
			{				
				$$.traducao = $3.traducao + $4.traducao;
				tamanhoVetor += 1;

				int compTipos;
				if(!$4.tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !$3.tipo.compare($4.tipo);;
				}

												
				if(compTipos){
					$$.tipo = $4.tipo;
					cout << $4.tipo << endl;													
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			} 
			| ',' '[' ES MLTVAR_VET ']' MLTVAR_MAT
			{
				$$.traducao = $3.traducao + $4.traducao + $6.traducao;
				tamanhoVetor += 1;

				
				int compTipos;
				if(!$4.tipo.compare("umElemento")){
					compTipos = 1;
				}
				else{
					compTipos = !$3.tipo.compare($4.tipo);;
				}

				if(compTipos){
					compTipos = !$4.tipo.compare($6.tipo);
					if(compTipos){
						$$.tipo = $4.tipo;					
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
			| ',' '[' ES MLTVAR_VET ']'
			{

				$$.traducao = $3.traducao + $4.traducao;
				tamanhoVetor += 1;

				int compTipos;
				if(!$4.tipo.compare("umElemento")){
					compTipos = 1;					
				}
				else
					compTipos = !$3.tipo.compare($4.tipo);

				if(compTipos){
					$$.tipo = $4.tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			} 
			| 
			{
				$$.tipo = "umElemento";
				$$.traducao = "";
			}
			
MLTVAR_VET: ',' E MLTVAR_VET
			{
				$$.traducao = $2.traducao + $3.traducao;
				tamanhoVetor += 1;

				int compTipos = !$2.tipo.compare($3.tipo);
				if(compTipos){
					$$.tipo = $2.tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
			| ',' E
			{		
				$$.tipo = $2.tipo;				
				$$.traducao = $2.traducao;
				tamanhoVetor += 1;
			}
			| ',' ES MLTVAR_VET
			{
				$$.traducao = $2.traducao + $3.traducao;
				tamanhoVetor += 1;

				int compTipos = !$2.tipo.compare($3.tipo);
				if(compTipos){
					$$.tipo = $2.tipo;					
				}
				else{
					indicaErro(MSG_ERRO_TIPO);
					exit(1);
				}
			}
			| ',' ES
			{		
				$$.tipo = $2.tipo;				
				$$.traducao = $2.traducao;
				tamanhoVetor += 1;
			}
			|
			{	
				$$.tipo = "umElemento";
				$$.traducao = "";
			}
			;		

MLTVAR	: ',' TOKEN_NOME MLTVAR
		{
			if(variavelExistente($2.nomeVariavel, 'd')){
				$$.tipo = "undefined";
				$$.valor = "null";
				$$.nomeVariavel = $2.nomeVariavel;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "";
				
				adicionaVariavelContexto($$);
			}
		}
		| ',' TOKEN_NOME TOKEN_ATR E MLTVAR
		{
			Contexto c = retornarContextoDaVariavel($4.nomeVariavel);
			string tipo;
			string valor;
			string traducao;
			string labelTemp;

			if(c.mapa[$4.nomeVariavel].tipo == ""){
				tipo = $4.tipo;
				valor = $4.valor;
				traducao = $4.traducao;
				labelTemp = $4.labelTemp;
			}else{
				tipo = c.mapa[$4.nomeVariavel].tipo;
				valor = c.mapa[$4.nomeVariavel].valor;
				traducao = c.mapa[$4.nomeVariavel].traducao;
				labelTemp = c.mapa[$4.nomeVariavel].labelTemp;
			}
			

			if(variavelExistente($2.nomeVariavel, 'd')){
				$$.tipo = $4.tipo;
				$$.valor = valor;		
				if(tipo != $$.tipo ){																
					indicaErro(MSG_ERRO_TIPO);
					exit(1);		
				}				
				$$.nomeVariavel = $2.nomeVariavel;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = traducao;
				$$.traducao = $4.traducao + "\t" + $$.labelTemp + " = " + labelTemp + ";\n" + $5.traducao; 

				adicionaVariavelContexto($$);

				ultimoTipo = $$.tipo;
			}
		}
		| MLTVAR_STRING		
		|
		{
			$$.traducao = "";
		}
		;

MLTVAR_STRING : ',' TOKEN_NOME MLTVAR_STRING
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "string";
					$$.valor = "null";
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = "";

					adicionaVariavelContexto($$);
				}
			}
			| ',' TOKEN_NOME TOKEN_ATR ES MLTVAR_STRING
			{
				if(variavelExistente($2.nomeVariavel, 'd')){
					$$.tipo = "string";
					$$.valor = $4.valor;
					$$.nomeVariavel = $2.nomeVariavel;
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.tamanho = $4.tamanho;
					$$.varTamString = $4.varTamString;
					$$.traducao = $5.traducao + $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" ;
					
					adicionaVariavelContexto($$);
				}
			}
			|
			{
				$$.traducao = "";
			}
			;

COMENT      : TOKEN_MAIOR TOKEN_COMENT TOKEN_COM_END 
			{
				$$.traducao = "\n\t/*" + $2.traducao + "*/\n\n";
			}
			| TOKEN_COM_INT TOKEN_LINECOMENT
			{
				$$.traducao = "\n\t/" + $2.traducao + "\n";
			}
			;						

IF 			: TOKEN_IF '(' ERL ')' BLOCO_NI
			{	

				string sFimIF = geraRotulo();
					
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n" + $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto "+ sFimIF +";\n" + $5.traducao +
				"\n\t"+ sFimIF +":\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();
			}
			| TOKEN_IF '(' ERL ')' BLOCO_NI ELSEIF
			{		
        		string sElseIF = geraRotulo(); 
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sElseIF +";\n" +
				$5.traducao + "\tgoto "+ sFimIFs +";\n\n\t" + sElseIF +":\n" + $6.traducao;        	
        		
        		desempilhaMapa();

			}
			| TOKEN_IF '(' ERL ')' BLOCO_NI ELSE
			{		
        		string sFimIF = geraRotulo();       	
        		string sElse = geraRotulo();
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//IF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto "+  sElse + ";\n" +
				$5.traducao +"\t"+ sElse +":\n" + $6.traducao;

				desempilhaMapa();
       		 	
			}
			;

ELSE: 		TOKEN_ELSE BLOCO_NI
			{
  				sFimIFs = geraRotulo();      	        
  				string sElse = geraRotulo();  			
  				
  				$$.traducao = "\t//ELSE COMEÇA\n" + $2.traducao+"\t" + 
				sFimIFs +":\n\t//ELSE TERMINA\n\t"+
				"//IF TERMINA\n\n";
  				
  				desempilhaMapa();
			}
			;
ELSEIF  	: TOKEN_ELSEIF '(' ERL ')' BLOCO_NI
			{		
				sFimIFs = geraRotulo();
				
				string sElseIF = geraRotulo();      			
      							
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t//ELSEIF COMEÇA\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sFimIFs + ";\n" +
				$5.traducao + 
				"\n\t" + sFimIFs + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();				
			}
			| TOKEN_ELSEIF '(' ERL ')' BLOCO_NI ELSEIF
			{		
				string sFimIF = geraRotulo();
				string sElseIF = geraRotulo(); 				
        						
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t//ELSEIF COMEÇA\n\t" + sElseIF + ":\n"+$3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sFimIF + ";\n" +
				$5.traducao + "\n\t" + sFimIF + ":\n\t//ELSEIF TERMINA\n\t//IF TERMINA\n\n";
				
				desempilhaMapa();			
			}
			| TOKEN_ELSEIF '(' ERL ')' BLOCO_NI ELSE
			{
        		string sFimIF = geraRotulo();
				string sElse = geraRotulo();
				string sElseIF = geraRotulo();  				

				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t//ELSEIF COMEÇA\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				"\tif(" + $$.labelTemp + ") goto " + sElse +";\n" +
				$5.traducao + "\tgoto "+ sFimIFs +";\n\n\t" +sElse+":\n"+ $6.traducao;
				desempilhaMapa();
			}
			;

WHILE 		: TOKEN_WHILE ERL BLOCO_LOOP
			{	
  				string sWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFWhile = pilhaDeContextos.top().rotuloFim;				
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t" + sWhile +":\n\t" + "//WHILE COMEÇA\n"+ $2.traducao +
				"\t" + $$.labelTemp + " = !" + $2.labelTemp + ";\n" +
				 "\tif("+$$.labelTemp+")goto "+sFWhile+"\n"+ $3.traducao + "\tgoto " + 
				sWhile +";\n\t"+ sFWhile + ":\n\t//WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

DO_WHILE 	: TOKEN_DO BLOCO_LOOP ERL ';'
			{	
  				string sDWhile = pilhaDeContextos.top().rotuloInicio;
  				string sFDWhile = pilhaDeContextos.top().rotuloFim;				
				
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\n\t" + sDWhile +":\n"+ "\t//DO_WHILE COMEÇA\n"+ $3.traducao +
				"\t" + $$.labelTemp + " = !" + $3.labelTemp + ";\n" +
				$2.traducao+"\tif("+$$.labelTemp+") goto "+sFDWhile+";\n\tgoto " + 
				sDWhile +";\n\t"+ sFDWhile + ":\n\t//DO_WHILE TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

FOR			: TOKEN_FOR '('COMANDO ERL ';' E ')' BLOCO_LOOP		
			{
				string sFor = pilhaDeContextos.top().rotuloInicio;
  				string sFFor = pilhaDeContextos.top().rotuloFim;	

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + sFor +":\n"+"\t//FOR COMEÇA\n"+ $3.traducao + $4.traducao +
				"\t" + $$.labelTemp + " = !" + $4.labelTemp + ";\n" +
				 "\t" + "if("+$$.labelTemp+") goto "+ sFFor +";\n"+$8.traducao + $6.traducao + "\tgoto "+sFor+";\n\t"+ sFFor + ":\n\t//FOR TERMINA\n";
  				
  				desempilhaMapa();
			}
			;

SWITCH 		: TOKEN_SWITCH '('E_BASICA ',' BLOCO_SWITCH ')' ';'
			{

				$$.traducao = "\n\t//SWITCH COMEÇA\n" + $5.traducao + "\t" + sFSwitch +":\n\t//SWITCH TERMINA\n";

				desempilhaMapa();
			}
			;

CASES 		: CASE CASES
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			| DEFAULT 
			{
				$$.traducao = $1.traducao;	
			}
			| CASE
			{
				$$.traducao = $1.traducao;
			}

			
CASE 		: TOKEN_CASE CASE_VALUE TOKEN_IMP COMANDOS
			{

				string sFimIF = geraRotulo();
  				sFSwitch = pilhaDeContextos.top().rotuloFim;

				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t"+ $$.labelTemp + " = !"+ $2.labelTemp + "\n\tif( "+$$.labelTemp+") goto " +sFimIF + ";\n"+ $4.traducao + "\n\t" + sFimIF +":\n";
			}
			;
DEFAULT     : TOKEN_DEFAULT TOKEN_IMP COMANDOS 
			{
				$$.traducao = $3.traducao + "\n";
			}
			;

CASE_VALUE	: E_BASICA
			{

				$$.tipo = "bool";
				$$.valor = $1.traducao;
				$$.labelTemp = geraLabelTemp("bool");				
				$$.traducao = $$.valor + "\t" + $$.labelTemp + " = " + $1.labelTemp + " == " + switchPar +";\n";
			}
			;

FUNCTION_CALL: TOKEN_NOME TOKEN_ATR FUNCT_CALLN '(' FUNCT_CALL_AUX ')'';'
			{
				Contexto c = retornarContextoDaVariavel($3.traducao);
				Contexto d = retornarContextoDaVariavel($1.nomeVariavel);
				string parametros = "";
				cout << c.mapa[$1.nomeVariavel].tipo <<endl;
				if(c.mapa[$3.traducao].tipo == "void"){
					cout<<"La funzione "+c.mapa[$3.traducao].funcao.nome+" non è compatibile con return perché è nullo."<<endl;	
					exit(1);
				}
				if(c.mapa[$1.nomeVariavel].tipo == "undefined"){

				}else if(c.mapa[$1.nomeVariavel].tipo != c.mapa[$3.traducao].tipo){
					cout<<"Il tipo di restituire di funzione "+c.mapa[$3.traducao].funcao.nome+" non è compatibile con "+$1.nomeVariavel<<endl;
					exit(1);
				}
				if(c.mapa[$3.traducao].funcao.parametros.size() == parametroAux.size()){
					$$.traducao = "\n\t//"+c.mapa[$3.traducao].funcao.nome+";\n";
					for(auto it_m1 = c.mapa[$3.traducao].funcao.parametros.cbegin(), end_m1 = c.mapa[$3.traducao].funcao.parametros.cend(),
	        			it_m2 = parametroAux.cbegin(), end_m2 = parametroAux.cend();
	        			it_m1 != end_m1 || it_m2 != end_m2;){
						if(it_m1->second != it_m2->second){
							cout<< "Parametros informados não possuem os mesmos tipos dos enunciados na função "+$3.traducao<<endl;
							exit(1);
						}
						parametros += "\t"+it_m1->first + " = "+  it_m2->first+";\n";
						if((it_m1 != end_m1)&&(it_m2 != end_m2)) {
				            ++it_m2;
				            ++it_m1;
				        }			
					}
					if(d.mapa[$1.nomeVariavel].tipo == "undefined"){
						d.mapa[$1.nomeVariavel].tipo = c.mapa[$3.traducao].tipo;
						d.mapa[$1.nomeVariavel].labelTemp = geraLabelTemp(d.mapa[$1.nomeVariavel].tipo);
						atualizarPilhaContextos(d.mapa[$1.nomeVariavel]);

					}

					$$.labelTemp = geraLabelTemp(c.mapa[$3.traducao].tipo);
					$$.traducao += c.mapa[$3.traducao].funcao.cabecalho +$5.traducao+ parametros + c.mapa[$3.traducao].funcao.escopo + "\t"
					+ d.mapa[$1.nomeVariavel].labelTemp + " = " + c.mapa[$3.traducao].funcao.retorno + ";\n";	
					parametroAux.clear();

				}else{
					cout << "Numero de parametros incorretos"<<endl;
					exit(1);
				}
			}
			| FUNCT_CALLN '(' FUNCT_CALL_AUX ')'';'
			{
				Contexto c = retornarContextoDaVariavel($3.traducao);
				
				string parametros = "";
				if(c.mapa[$1.traducao].funcao.parametros.size() == parametroAux.size()){
					$$.traducao = "\n\t//"+c.mapa[$1.traducao].funcao.nome+";\n";
					for(auto it_m1 = c.mapa[$1.traducao].funcao.parametros.cbegin(), end_m1 = c.mapa[$1.traducao].funcao.parametros.cend(),
	        			it_m2 = parametroAux.cbegin(), end_m2 = parametroAux.cend();
	        			it_m1 != end_m1 || it_m2 != end_m2;){
						if(it_m1->second != it_m2->second){
							cout<< "Parametros informados não possuem os mesmos tipos dos enunciados na função "+$1.traducao<<endl;
							exit(1);
						}
						parametros += "\t"+it_m1->first + " = "+  it_m2->first+";\n";
						if((it_m1 != end_m1)&&(it_m2 != end_m2)) {
				            ++it_m2;
				            ++it_m1;
				        }			
					}

					$$.labelTemp = geraLabelTemp(c.mapa[$1.traducao].tipo);
					$$.traducao += c.mapa[$3.traducao].funcao.cabecalho +$1.traducao + parametros + c.mapa[$1.traducao].funcao.escopo + "\n\t";
					parametroAux.clear();
				}else{
					cout << "Numero de parametros incorretos"<<endl;
					exit(1);
				}
			}
			;

FUNCT_CALLN: TOKEN_NOME
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				if(c.mapa[$1.nomeVariavel].funcao.nome == ""){
					cout<<"Funzione "+$1.nomeVariavel+" non valida"<<endl;
					parametroAux.clear();
					exit(1);
				}
				$$.traducao = $1.nomeVariavel;
			}
			;

FUNCT_CALL_AUX: E FUNCT_CALL_PAR_AUX
			{
				$$.traducao = $1.traducao + $2.traducao;
				parametroAux.insert({$1.labelTemp, $1.tipo});

			}
			|
			;
FUNCT_CALL_PAR_AUX: ',' E FUNCT_CALL_PAR_AUX
			{
				$$.traducao = $2.traducao + $3.traducao;
				parametroAux.insert({$2.labelTemp, $2.tipo});
			}
			|
			;

FUNCTION	: TOKEN_FUNCT FUNCTION_NOME '(' FUNCTION_PARA ')' BLOCO_FUN
			{
				Contexto c = retornarContextoDaVariavel(function);
				$$.tipo = "void";
				$$.labelTemp = "";
				$$.valor = "";
				$4.traducao = "";
				c.mapa[function].tipo = "void";
				c.mapa[function].funcao.cabecalho = $4.traducao;
				c.mapa[function].funcao.escopo = $6.traducao;	
				c.mapa[function].funcao.traducao = "\n\t//"+ ($2.traducao) + ":\n" + $4.traducao + c.mapa[function].funcao.escopo + $6.traducao;
				atualizarPilhaContextos(c.mapa[function]);

				count = 0;
			}
			| TOKEN_FUNCT TIPO FUNCTION_NOME '(' FUNCTION_PARA ')' BLOCO_FUN_RET
			{
				Contexto c = retornarContextoDaVariavel($3.traducao);
				$$.nomeVariavel = $3.traducao;
				$$.tipo = retornoR;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "";
				$$.traducao = "";
				$$.funcao.nome = $3.traducao;
				c.mapa[function].funcao.cabecalho = $5.traducao;
				c.mapa[function].funcao.escopo = $7.traducao;
				c.mapa[function].funcao.traducao = "\n\t//"+ ($3.traducao) + ":\n";
				atualizarPilhaContextos(c.mapa[function]);

				count = 0;						
			}
			;	

FUNCTION_NOME: 	TOKEN_NOME 
			{

				function = $1.nomeVariavel;
				(retornoR=="")? "undefined" : $$.tipo = retornoR ;
				$$.nomeVariavel = $1.nomeVariavel;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.funcao.nome = $1.nomeVariavel;
				$$.traducao = $1.nomeVariavel;
				adicionaVariavelContexto($$);

			}
			;

FUNCTION_PARA:  TIPO TOKEN_NOME TOKEN_ATR E_BASICA FUNCTION_PARA
			{	
				Contexto c = retornarContextoDaVariavel(function);
				
				$$.tipo =  $4.tipo;
				$$.nomeVariavel = $2.nomeVariavel;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $4.valor;
				$$.traducao = $4.traducao + "\t" + $$.labelTemp + " = " + $4.labelTemp + ";\n" + $5.traducao; 
				c.mapa[function].funcao.parametros.insert({$$.labelTemp, $4.tipo});
				adicionaVariavelContexto($$);
				atualizarPilhaContextos(c.mapa[function]);
				ultimoTipo = $$.tipo;
			}
			| TIPO TOKEN_NOME FUNCTION_PARA
			{	
				Contexto c = retornarContextoDaVariavel(function);

				$$.tipo =  $1.tipo;
				$$.nomeVariavel = $2.nomeVariavel;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "";
				$$.traducao = $3.traducao; 
				adicionaVariavelContexto($$);
				c.mapa[function].funcao.parametros.insert({$$.labelTemp, $$.tipo});				
				atualizarPilhaContextos(c.mapa[function]);
				ultimoTipo = $$.tipo;
			}
			| ',' FUNCTION_PARA
			{
				$$.traducao = $2.traducao;	
			}
			|
			;

TIPO 		: TOKEN_INT	
			{
				if(count == 0)
					retornoR = "int";
				count++;
			}
			| TOKEN_BOOL 
			{
				if(count == 0)
					retornoR = "bool";
				count++;
			}
			| TOKEN_FLOAT 
			{
			
				if(count == 0)
					retornoR = "float";
				count++;
			}
			| TOKEN_CHAR
			{
				if(count == 0)
					retornoR = "char";
				count++;
			}
			| TOKEN_STR
			{
				if(count == 0)
					retornoR = "string";
				count++;
			}
			;


RETURN : TOKEN_RETURN E
		{
			Contexto c = retornarContextoDaVariavel(function);

			if($2.tipo != retornoR){
				cout<<"Funzione con parametri di ritorno errati"<< endl;
				exit(1);
			}
			$$.tipo = $2.tipo;
			$$.labelTemp = geraLabelTemp($$.tipo);
			$$.traducao = $2.traducao;
			c.mapa[function].funcao.retorno = $2.labelTemp ;
			atualizarPilhaContextos(c.mapa[function]);

		}
		|
		{
			cout<<"La funzione richiede parametri di ritorno"<< endl;
			exit(1);
		}
		;

BREAK_ALL: TOKEN_BREAK_ALL
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

        		$$.traducao = "\t//BREAK_ALL\n\tgoto " + c.rotuloFim + ";\n";

		}

BREAK   : TOKEN_BREAK
			{
       			
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				$$.traducao = "\t//BREAK\n\tgoto " + copiaPilha.top().rotuloFim + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
        		
      		}

CONTINUE: TOKEN_CONTINUE
			{
				PilhaContexto copiaPilha = pilhaDeContextos;
        		while(!copiaPilha.empty()){
        			if(copiaPilha.top().interrompivel == 1){
        				$$.traducao = "\t//CONTINUE\n\tgoto " + copiaPilha.top().rotuloInicio + ";\n";
        				
        				break;
        			}
        			if(copiaPilha.size() == 1){
        				indicaErro(MSG_ERRO_CONTEXTONAOINTERROMPIVEL);
						exit(1);
        			}
        			
        			copiaPilha.pop();
        			
        		}
			}

ERL         : '(' ERL ')'
			{
				$$.tipo = $2.tipo;
				$$.labelTemp = $2.labelTemp;
				$$.traducao = $2.traducao;
			}
 			| ERL TOKEN_MAIOR ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " > " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " > " + labelCasting +
					";\n";
					cout<< $1.labelTemp;
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " > " + $3.labelTemp +
					";\n";
				}

			}
			| ERL TOKEN_MENOR ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " < " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " < " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " < " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MAIORIGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + labelCasting +
					";\n";
					
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " >= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_MENORIGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + $3.labelTemp +
					";\n";


				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + labelCasting +
					";\n";
				}
				else{	EL:
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " <= " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_DIF ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " != " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " != " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " != " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_IGUAL ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " == " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " == " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " == " + $3.labelTemp +
					";\n";
				}
			}
			
			| ERL TOKEN_E ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " && " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " && " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " && " + $3.labelTemp +
					";\n";
				}
			}
			| ERL TOKEN_OU ERL
			{
				$$.tipo = "bool";
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				fazCasting = tabelaDeTipos(c.mapa[$1.nomeVariavel].tipo, $3.tipo);
				string theCasting = "";
				string labelTemp = c.mapa[$1.nomeVariavel].labelTemp;

				if(fazCasting == 1){					
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " || " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					string labelCasting = geraLabelTemp("float");
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelTemp + " || " + labelCasting +
					";\n";
				}
				else{		
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + labelTemp + " || " + $3.labelTemp +
					";\n";
				}
			}
			| E_BASICA
			{ 
				$$.traducao = $1.traducao;
			}
			;	

E 			: '(' E ')'
			{
				$$.tipo = $2.tipo;
				$$.labelTemp = $2.labelTemp;
				$$.traducao = $2.traducao;
			}
			| E_BASICA TOKEN_MAISIGUAL E_BASICA
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $3.traducao +"\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " + " + $3.labelTemp +" ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA TOKEN_MENOSIGUAL E_BASICA
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $3.traducao +"\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " - " + $3.labelTemp +" ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA TOKEN_VEZESIGUAL E_BASICA
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $3.traducao +"\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " * " + $3.labelTemp +" ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA TOKEN_DIVIDEIGUAL E_BASICA
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $3.traducao +"\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " / " + $3.labelTemp +" ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA '+' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " + " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " + " + $3.labelTemp +
					";\n";
				}

				
			}
			| E_BASICA '-' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " - " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " - " + $3.labelTemp +
					";\n";
				}
				
			}
			| E_BASICA '*' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " * " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " * " + $3.labelTemp +
					";\n";
				}
				
			}
			| E_BASICA '/' E
			{
				fazCasting = tabelaDeTipos($1.tipo, $3.tipo);
				string theCasting = ""; 

				if(fazCasting == 1){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $1.labelTemp + ";\n";

					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + labelCasting + " / " + $3.labelTemp +
					";\n";

				}
				else if(fazCasting == 2){
					$$.tipo = "float";
					string labelCasting = geraLabelTemp($$.tipo);
					theCasting = "\t" + labelCasting + " = (float) " + $3.labelTemp + ";\n";
					
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + theCasting +"\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + labelCasting +
					";\n";
				}
				else if(fazCasting == 0){
					$$.tipo = "int";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + $3.labelTemp +
					";\n";
				}
				else{		
					$$.tipo = "float";
					$$.labelTemp = geraLabelTemp($$.tipo);
					$$.traducao = $1.traducao + $3.traducao + "\t" +
					$$.labelTemp + " = " + $1.labelTemp + " / " + $3.labelTemp +
					";\n";
				}
			}
			| TOKEN_CONV_FLOAT E
			{
				$$.tipo = "float";
				
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.labelTemp + " = (float) " + $2.labelTemp +
				";\n";
			}
			| TOKEN_CONV_INT E
			{
				$$.tipo = "int";
				
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.labelTemp + " = (int) " + $2.labelTemp +
				";\n";
			}
			| '-' E_BASICA
			{
				$$.tipo = $2.tipo;

				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = $2.traducao + "\t" + $$.nomeVariavel + " = -" + $2.nomeVariavel +
				";\n";			
			}
			| E_BASICA '+''+'
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " + 1 ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA TOKEN_POTENCIA E_BASICA
			{
				string sPot = "Potencia_" + to_string(contaPot);
				string sFPot = "Potencia_" + to_string(contaPot+1);
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				
				$$.labelTemp = geraLabelTemp($$.tipo);
				string labelMult = geraLabelTemp("int");
				string labelVer = geraLabelTemp("bool");
				string label0 = geraLabelTemp("bool");
				string labelAux = geraLabelTemp($3.tipo); 

				$$.traducao = "\n\t//PONTENCIA\n"+$3.traducao + "\t" +labelAux+ " = " +$3.labelTemp+";\n\t"+
				labelVer + " = " + labelAux + " == 0;\n\t" + labelVer + " = !" +labelVer+ ";\n\tif("+labelVer+") goto "+ sPot+";\n\t"+
				labelMult + " = 1" + +";\n\t"+ "goto "+sFPot+";\n\t"+
				sPot +":\n\t" + labelMult + " = " + c.mapa[$1.nomeVariavel].labelTemp +" * 1;\n\t"+
				label0 +" = "+labelAux+" == 0;\n\t"+label0+ " = !"+labelAux+";\n\t"+ "if("+label0+") goto "+sFPot+";\n\t"+
				labelMult + " = " + c.mapa[$3.nomeVariavel].labelTemp+ " * "+ labelMult + ";" + 
				"\n\t" + labelAux + " = " + labelAux + " - 1 ;\n\t"+
				"goto "+sPot+";\n\t" + sFPot +":\n\t"+
				$$.labelTemp + " = " + labelMult +";\n";
				contaPot++;
			}
			| E_BASICA '-''-'
			{
				Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
				$$.tipo = c.mapa[$1.nomeVariavel].tipo;
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.traducao = "\t" + $$.labelTemp + " = " + c.mapa[$1.nomeVariavel].labelTemp + " - 1 ;\n"
				+ "\t" + c.mapa[$1.nomeVariavel].labelTemp + " = " + $$.labelTemp + ";\n";
			}
			| E_BASICA
			{ 
				$$.traducao = $1.traducao;
			}
			;

ES 			: TOKEN_STRING 
			{
				ultimoTipo = "string";
				tipoGeral = 2;
				$$.tipo = "string";
				$$.labelTemp = geraLabelTemp($$.tipo);
				
				//remover aspas 	
				string removerAspas = $1.traducao;
				string semAspas = $1.traducao.erase(0, 1);
				int lenSemAspas = semAspas.length() - 1;
				$$.valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
				$$.tamanho = $$.valor.length();					

				$$.varTamString	= geraLabelTemp("string_tam");
				$$.traducao = "\n\t" + $$.varTamString + " = " + to_string($$.tamanho) + ";\n\t" + $$.labelTemp + " = (char*)malloc(" + 
				$$.varTamString + " * sizeof(char));\n\t" + "strcat(" + $$.labelTemp + ", '" + $$.valor + "')" +
				";\n";
			}			
			| TOKEN_NOME
			{

                if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
					if(c.mapa[$1.nomeVariavel].tipo == "string"){
						if(c.mapa[$1.nomeVariavel].valor != "null"){						

							$$.nomeVariavel = $1.nomeVariavel;
							$$.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;							
							$$.valor = pilhaDeContextos.top().mapa[$$.nomeVariavel].valor;
							$$.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
							$$.tamanho =pilhaDeContextos.top().mapa[$$.nomeVariavel].tamanho;
							$$.varTamString = pilhaDeContextos.top().mapa[$$.nomeVariavel].varTamString;
							$$.traducao = ""; 

						}
						else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
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
			| TOKEN_NOME '[' TOKEN_NUM_INT ']'
			{
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
                	
                	if(c.mapa[$1.nomeVariavel].valor != "null"){
                		$$.nomeVariavel = $1.nomeVariavel;
                		
                		if(stoi($3.traducao) < c.mapa[$$.nomeVariavel].tamanhoMax){
							$$.labelTemp = c.mapa[$$.nomeVariavel].labelTemp + "[" + $3.traducao + "]";							
							$$.valor = c.mapa[$$.nomeVariavel].valor;
							$$.tipo = c.mapa[$$.nomeVariavel].tipo;
							if(!$$.tipo.compare("intP")){
								$$.tipo = "int";
							}
							if(!$$.tipo.compare("floatP")){
								$$.tipo = "float";
							}
							if(!$$.tipo.compare("boolP")){
								$$.tipo = "bool";
							}
							if(!$$.tipo.compare("stringP")){
								$$.tipo = "string";
							}
							if(!$$.tipo.compare("charP")){
								$$.tipo = "char";
							}
							$$.traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
			| TOKEN_NOME '[' TOKEN_NUM_INT ']' '[' TOKEN_NUM_INT ']'
			{
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
                	
                	if(c.mapa[$1.nomeVariavel].valor != "null"){
                		$$.nomeVariavel = $1.nomeVariavel;
                		
                		if(stoi($3.traducao) * stoi($6.traducao) < c.mapa[$$.nomeVariavel].tamanhoMax){
                			int i, j, valor = 0;
	                		for (i=0;i<=stoi($3.traducao);i++)
	                			valor += stoi($3.traducao);
	                		for(j=0;j<stoi($6.traducao);j++)
	                			valor += 1;

							$$.labelTemp = c.mapa[$$.nomeVariavel].labelTemp + "[" + to_string(valor) + "]";							
							$$.valor = c.mapa[$$.nomeVariavel].valor;
							$$.tipo = c.mapa[$$.nomeVariavel].tipo;
							if(!$$.tipo.compare("intP")){
								$$.tipo = "int";
							}
							if(!$$.tipo.compare("floatP")){
								$$.tipo = "float";
							}
							if(!$$.tipo.compare("boolP")){
								$$.tipo = "bool";
							}
							if(!$$.tipo.compare("stringP")){
								$$.tipo = "string";
							}
							if(!$$.tipo.compare("charP")){
								$$.tipo = "char";
							}
							$$.traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
			;

CONCATENACAO : TOKEN_NOME TOKEN_ATR ES '.' ES
			{	
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);

                	if(c.mapa[$1.nomeVariavel].tipo == "string") {
						if(c.mapa[$1.nomeVariavel].valor != "null"){						

							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = pilhaDeContextos.top().mapa[$$.nomeVariavel].tamanho;							
							$1.varTamString = pilhaDeContextos.top().mapa[$$.nomeVariavel].varTamString;
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;

						}
						else{
							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = 0;							
							$1.varTamString = geraLabelTemp("string_tam");
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
						}
						
							$$.labelTemp = geraLabelTemp($1.tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + $3.valor + $5.valor;
							$1.valor = 	concat;				
							$1.tamanho = $1.valor.length() - 1;

							

							$$.traducao = "\n\t//concatenacao\n" + $3.traducao + $5.traducao + "\n\t" + varTamString + " = " + $3.varTamString + " + " + $5.varTamString + ";\n" +
							"\t" + $$.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + $$.labelTemp + ", " + $3.labelTemp + ");\n" +
							"\tstrcat(" + $$.labelTemp + ", " + $5.labelTemp + ");\n" +
							"\tfree( " + $1.labelTemp + " );\n" + 
							"\t" + $1.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + $1.labelTemp + ", " + $$.labelTemp + ");\n" + 
							"\t"+ $1.varTamString + " = " + varTamString + ";\n";									
										
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
			|TOKEN_NOME TOKEN_PONTOIGUAL ES
			{	
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);

                	if(c.mapa[$1.nomeVariavel].tipo == "string") {
						if(c.mapa[$1.nomeVariavel].valor != "null"){						

							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = pilhaDeContextos.top().mapa[$$.nomeVariavel].tamanho;							
							$1.varTamString = pilhaDeContextos.top().mapa[$$.nomeVariavel].varTamString;
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;

						}
						else{
							$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;														
							$1.tamanho = 0;							
							$1.varTamString = geraLabelTemp("string_tam");
							$1.tipo = pilhaDeContextos.top().mapa[$$.nomeVariavel].tipo;
						}
						
							$$.labelTemp = geraLabelTemp($1.tipo);	
							string varTamString = geraLabelTemp("string_tam");
							string concat = "";
							concat = concat + $1.valor + $3.valor;
							$1.valor = 	concat;				
							$1.tamanho = $1.valor.length() - 1;

							

							$$.traducao = "\n\t//.= concatenacao\n"+ $3.traducao+ "\t" + varTamString + " = " + $1.varTamString + " + " + $3.varTamString + ";\n" +
							"\t" + $$.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +					
							"\tstrcat(" + $$.labelTemp + ", " + $1.labelTemp + ");\n" +
							"\tstrcat(" + $$.labelTemp + ", " + $3.labelTemp + ");\n" +
							"\tfree( " + $1.labelTemp + " );\n" + 
							"\t" + $1.labelTemp + " = (char*)malloc(" + varTamString + " * sizeof(char));\n" +
							"\tstrcat(" + $1.labelTemp + ", " + $$.labelTemp + ");\n" + 
							"\t"+ $1.varTamString + " = " + varTamString + ";\n" + 
							"\tfree( " + $$.labelTemp + " );\n";									
										
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
			;

PRINT 		: TOKEN_PRINT '(' CONTEUDO_PRINT ')'
			{
				$$.traducao = $3.traducao;
			}


CONTEUDO_PRINT: TOKEN_NUM_INT MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("int");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_NUM_FLOAT MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("float");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_BOOL MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("bool");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_STRING MAIS_PRINT
				{
					$$.labelTemp = geraLabelTemp("string");	
					$$.varTamString = geraLabelTemp("string_tam");			

					//remover aspas 	
					string removerAspas = $1.traducao;
					string semAspas = $1.traducao.erase(0, 1);
					int lenSemAspas = semAspas.length() - 1;
					$$.valor  = semAspas.erase(lenSemAspas, 1); //valor sem aspas
					$$.tamanho = $$.valor.length() + 1;

					$$.traducao = "\n\t" + $$.varTamString + " = " + to_string($$.tamanho) + ";\n\t" + $$.labelTemp + " = (char*)malloc(" + 
					$$.varTamString + " * sizeof(char));\n\t" + "strcat(" + $$.labelTemp + ", '" + $$.valor + "')" +
					";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_CHAR MAIS_PRINT 
				{
					$$.labelTemp = geraLabelTemp("char");				
					$$.traducao = "\t" + $$.labelTemp + " = " + $1.valor + ";\n\tcout << " + $$.labelTemp + " << endl;\n" + $2.traducao;
				}
				| TOKEN_NOME MAIS_PRINT 
				{
					if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
	                	if(c.mapa[$1.nomeVariavel].valor != "null"){      
	                		$1.labelTemp = pilhaDeContextos.top().mapa[$$.nomeVariavel].labelTemp;		          		                		
	                		$$.traducao = "\tcout << " + c.mapa[$1.nomeVariavel].labelTemp +" << endl;\n" + $2.traducao;
	                	}
						else {
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
				| TOKEN_NOME '[' TOKEN_NUM_INT ']' MAIS_PRINT 
				{
					if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
	                	if(c.mapa[$1.nomeVariavel].valor != "null"){
	                		if(stoi($3.traducao) < c.mapa[$1.nomeVariavel].tamanhoMax) {     
	                			$1.labelTemp = c.mapa[$$.nomeVariavel].labelTemp;		          		                		
	                			$$.traducao = "\tcout << " + c.mapa[$1.nomeVariavel].labelTemp + "[" + $3.traducao + "] << endl;\n" + $5.traducao;
	                		}
	                		else{
	                			indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
	                			exit(1);
	                		}
	                	}
						else {
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
				| TOKEN_NOME '[' TOKEN_NUM_INT ']' '['TOKEN_NUM_INT ']' MAIS_PRINT 
				{
					if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
	                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
	                	if(c.mapa[$1.nomeVariavel].valor != "null"){

	                		if(stoi($3.traducao) * stoi($6.traducao) < c.mapa[$1.nomeVariavel].tamanhoMax) {   
	                			string labelPos = "";
	                			
	                			int i, j, valor = 0;
	                			for (i=0;i<=stoi($3.traducao);i++)
	                				valor += stoi($3.traducao);
	                			for(j=0;j<stoi($6.traducao);j++)
	                				valor += 1;
	                			
	                			labelPos += to_string(valor);

	                			$1.labelTemp = c.mapa[$$.nomeVariavel].labelTemp;		          		                		
	                			$$.traducao = "\tcout << " + c.mapa[$1.nomeVariavel].labelTemp + "[" + labelPos + "] << endl;\n" + $8.traducao;
	                		}
	                		else{
	                			indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
	                			exit(1);
	                		}
	                	}
						else {
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);	
						}            
	                }
	                else{
						indicaErro(MSG_ERRO_NDECLARADA);
						exit(1);									
					}	
				}
				|
				{
					$$.traducao = "";
				}

MAIS_PRINT:	',' CONTEUDO_PRINT
			{
				$$.traducao = $2.traducao;
			}	
			|	
			{
				$$.traducao = "";
			}
		
SCANF 		: TOKEN_SCANF '(' TOKEN_NOME ')'
			{
				if(variavelExistente($3.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($3.nomeVariavel);
                	if(c.mapa[$3.nomeVariavel].tipo == "int") {                		
                		$$.traducao = "\tscanf(\"%d\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "float") {
                		$$.traducao = "\tscanf(\"%f\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "char") {
                		$$.traducao = "\tscanf(\"%c\", &" + c.mapa[$3.nomeVariavel].labelTemp + ");\n";
                	}
                	if(c.mapa[$3.nomeVariavel].tipo == "string") {
                		string varTamString = c.mapa[$3.nomeVariavel].varTamString;
                	
                		string var = c.mapa[$3.nomeVariavel].labelTemp;
                		string varT = geraLabelTemp("char");
                		string numVarT = geraLabelTemp("string_tam");
                		string rotI = "ROT_STR_LET_IN_" + to_string(nCL);
                		string rotF = "ROT_STR_LET_FIM_" + to_string(nCL);

                		$$.traducao = "\n\tif (" + varTamString + " > 0) free(" + var + ");\n" +
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
                	if(c.mapa[$3.nomeVariavel].tipo == "undefined")
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
			


E_BASICA	: TOKEN_NUM_INT
			{
				ultimoTipo = "int";
				tipoGeral = 1;
				$$.tipo = "int";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NUM_FLOAT
			{	
				ultimoTipo = "float";
				tipoGeral = 1;
				$$.tipo = "float";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
				";\n";
			}
			| TOKEN_NOME
			{

                if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);

					if(c.mapa[$1.nomeVariavel].tipo == "float" || c.mapa[$1.nomeVariavel].tipo == "int"){
						if(c.mapa[$1.nomeVariavel].valor != "null"){						


							$$.nomeVariavel = $1.nomeVariavel;
							$$.labelTemp = c.mapa[$$.nomeVariavel].labelTemp;							
							$$.valor = c.mapa[$$.nomeVariavel].valor;
							$$.tipo = c.mapa[$$.nomeVariavel].tipo;
							$$.traducao = ""; 
							switchPar = $$.labelTemp;
						}
						else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
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
			| TOKEN_NOME '[' TOKEN_NUM_INT ']'
			{
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
                	
                	if(c.mapa[$1.nomeVariavel].valor != "null"){
                		$$.nomeVariavel = $1.nomeVariavel;
                		
                		if(stoi($3.traducao) < c.mapa[$$.nomeVariavel].tamanhoMax){
							$$.labelTemp = c.mapa[$$.nomeVariavel].labelTemp + "[" + $3.traducao + "]";							
							$$.valor = c.mapa[$$.nomeVariavel].valor;
							$$.tipo = c.mapa[$$.nomeVariavel].tipo;
							if(!$$.tipo.compare("intP")){
								$$.tipo = "int";
							}
							if(!$$.tipo.compare("floatP")){
								$$.tipo = "float";
							}
							if(!$$.tipo.compare("boolP")){
								$$.tipo = "bool";
							}
							if(!$$.tipo.compare("stringP")){
								$$.tipo = "string";
							}
							if(!$$.tipo.compare("charP")){
								$$.tipo = "char";
							}
							$$.traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
			| TOKEN_NOME '[' TOKEN_NUM_INT ']' '[' TOKEN_NUM_INT ']'
			{
				if(variavelExistente($1.nomeVariavel, 'e')){ //Se a variável existir...
                	Contexto c = retornarContextoDaVariavel($1.nomeVariavel);
                	
                	if(c.mapa[$1.nomeVariavel].valor != "null"){
                		$$.nomeVariavel = $1.nomeVariavel;
                		
                		if(stoi($3.traducao) * stoi($6.traducao) < c.mapa[$$.nomeVariavel].tamanhoMax){
                			int i, j, valor = 0;
	                		for (i=0;i<=stoi($3.traducao);i++)
	                			valor += stoi($3.traducao);
	                		for(j=0;j<stoi($6.traducao);j++)
	                			valor += 1;

							$$.labelTemp = c.mapa[$$.nomeVariavel].labelTemp + "[" + to_string(valor) + "]";							
							$$.valor = c.mapa[$$.nomeVariavel].valor;
							$$.tipo = c.mapa[$$.nomeVariavel].tipo;
							if(!$$.tipo.compare("intP")){
								$$.tipo = "int";
							}
							if(!$$.tipo.compare("floatP")){
								$$.tipo = "float";
							}
							if(!$$.tipo.compare("boolP")){
								$$.tipo = "bool";
							}
							if(!$$.tipo.compare("stringP")){
								$$.tipo = "string";
							}
							if(!$$.tipo.compare("charP")){
								$$.tipo = "char";
							}
							$$.traducao = "";
						}
						else{
							indicaErro(MSG_ERRO_MUITOS_ELEMENTOS_VETOR);
							exit(1);
						}

                	}
                	else{
							std::cout <<c.mapa[$1.nomeVariavel].nomeVariavel<<MSG_ERRO_INICIALIZADA <<std::endl<<"Linea "<<ctdLinhas<< std::endl;
							exit(1);															
						}
				}
				else{

					indicaErro(MSG_ERRO_NDECLARADA);
					exit(1);									
				}
				
			}
			| TOKEN_BOOLEAN_FALSE
			{
				ultimoTipo = "bool";
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "0";
				$$.traducao = "\t" + $$.labelTemp + " = " + $$.valor +
				";\n";
			}
			| TOKEN_BOOLEAN_TRUE
			{
				ultimoTipo = "bool";
				$$.tipo = "bool";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = "1";
				$$.traducao = "\t" + $$.labelTemp + " = " + $$.valor +
				";\n";
			}
			| TOKEN_CARACTERE
			{
				tipoGeral = 2;
				$$.tipo = "char";
				$$.labelTemp = geraLabelTemp($$.tipo);
				$$.valor = $1.traducao;
				$$.traducao = "\t" + $$.labelTemp + " = " + $1.traducao +
				";\n";
			}					
            ;


%%

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
