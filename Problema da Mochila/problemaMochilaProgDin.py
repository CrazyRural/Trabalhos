'''
    Feito por João Victor Araújo, Julia Rodrigues e Victor Diniz
'''
def resolverKnapsack(pesos,valores,capacidade):

    n = len(pesos)
    l, c = n + 1, capacidade + 1
    
    valorFuncao = [[0 for col in range(c)] for row in range(l)]
    valoresMatriz = [[0 for col in range(c)] for row in range(l)]
    
    for i in range(1, n + 1):
        for x in range(0,capacidade + 1):
            if(x - pesos[i - 1] >= 0):
                valorFuncao[i][x] = max(valorFuncao[i - 1][x], valorFuncao[i - 1][ x - pesos[i - 1]] + valores[i - 1])
                if(valorFuncao[i - 1][x] < valorFuncao[i - 1][ x - pesos[i - 1]] + valores[i - 1]):
                    valoresMatriz[i][x] = 1
            else:
                valorFuncao[i][x] = valorFuncao[i - 1][x]
    return valorFuncao,valoresMatriz          

def removerElementos(valoresMatriz,pesos):

    [n,capacidade] = len(valoresMatriz), len(valoresMatriz[0])
    n = n - 1
    capacidade = capacidade - 1
    conteudo = []
    k = capacidade
    
    for i in range(n,0, -1):
        if(valoresMatriz[i][k] == 1):
            conteudo.append(i - 1)
            k = capacidade-pesos[i - 1]                    
    return conteudo

def imprimirElementos(entrada):
    
    print()
    for linha in range (len(entrada)):
        for coluna in range (len(entrada[0])):
            print('[', str(entrada[linha][coluna]), end =' ]  '),
        print()
    print()

def main():

    capacidade = 5  

    listaValores = []

    listaPesos = []
    #numero de itens
    listaPesos.append(6) 
    listaPesos.append(4)
    listaPesos.append(2)
    listaPesos.append(1)
    #peso dos itens
    listaValores.append(4)
    listaValores.append(6)
    listaValores.append(12)
    listaValores.append(24)

    [valorFuncao, valoresMatriz] = resolverKnapsack(listaPesos, listaValores, capacidade)  
          
    imprimirElementos(valorFuncao)
    imprimirElementos(valoresMatriz)   
    
    print((removerElementos(valoresMatriz,listaPesos)))

    imprimirElementos(valorFuncao)
    imprimirElementos(valoresMatriz) 

main()    