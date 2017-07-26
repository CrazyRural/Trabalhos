print("Digite o número de rainhas: ")
N = io.read("*n")

 
tabuleiro = {};
for i = 1, N do
  tabuleiro[i] = {}
  for j = 1, N do
    tabuleiro[i][j] = false
  end
end
 
function verificarPosicao(x,y)
    for i = 1, x-1 do
      if (tabuleiro[i][y]) or (i <= y and tabuleiro[x-i][y-i]) or (y+i <= N and tabuleiro[x-i][y+i]) then 
        return false 
      end
    end   
    return true
end
 
function encontrarSolucao(x)
    for y = 1, N do
      if verificarPosicao(x, y) then 
        tabuleiro[x][y] = true 
        if x == N or encontrarSolucao(x+1) then
          return true
        end
        tabuleiro[x][y] = false      
      end   
     end
    return false
end

if encontrarSolucao(1) then
     for i = 1, N do
        for j = 1, N do
             if tabuleiro[i][j] then 
               io.write("|Q")
             else 
               io.write("| ")
             end
         end
        print("|")
      end
    else
       print(string.format( "Não tem solução para %d rainhas.\n", N ))
end