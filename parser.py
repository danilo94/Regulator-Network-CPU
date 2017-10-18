caminho="../Benchmarks/Benchmark1(CACnetwork)69Nos.txt"


ref = open(caminho,"r")
operacoesLogicas = {}

operacoesLogicas['not'] = '!'
operacoesLogicas['and'] = '&&'
operacoesLogicas['or'] = '||'
operacoesLogicas['('] = '('
operacoesLogicas[')'] = ')'
operacoesLogicas['='] = '='
operacoesLogicas['!'] = '!'
operacoesLogicas['~'] = '!'
operacoesLogicas['&'] = '&&'
operacoesLogicas['|'] = '||'


dict = {}
i=0
for linha in ref:
    caracteres = linha.split(" ")
    dict[caracteres[0]] = "vet["+str(i)+"]"
    dict[caracteres[0]+'\n'] = "vet["+str(i)+"]"

    i = i+1

ref.close()

ref = open(caminho,"r")

for linha in ref:
    out = ""
    linha = linha.strip('\n')
    caracteres = linha.split(" ")
    for substring in caracteres:
        if (operacoesLogicas.get(substring)!=None):
            out = out + operacoesLogicas.get(substring) + " "
        else:
            if (dict.get(substring)!=None):
                out = out + dict.get(substring) + " "
            else:
                out = out + substring + " "

    out = out + ";\n"
    print (out)
