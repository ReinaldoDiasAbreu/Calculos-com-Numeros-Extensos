#ifndef NUMBERS_H
#define NUMBERS_H
#include <iostream>
#include <cstdlib>
#include <cmath>

class LongNum
{
    private:
        int *dados;
        int topo;
        int capacidade;

    public:
        LongNum(int cap=1)                  /// Construtor da pilha e inicia os elementos
        {
            dados = new int[cap];
            topo = -1;
            capacidade = cap;
        }
        bool vazia()                        /// Verifica se a pilha está vazia
        {
            return topo == -1;
        }
        void realocar()                     /// Realoca mais uma posição na pilha
        {
            int *aux = new int[capacidade+1];
            for(int i=0; i< capacidade; i++)
                aux[i] = dados[i];
            delete []dados;
            dados = aux;
            capacidade += 1;
        }
        void EmpilhaElemento(int elem)      ///  Empilha um elemento inteiro
        {
            if(topo+1 == capacidade)
            {
                this->realocar();     // Realoca 1 dezena no numero
                dados[++topo] = elem;
            }
            else
            {
                dados[++topo] = elem;
            }
        }
        int tamanho()                       /// Retorna capacidade da pilha.
        {
            return capacidade;
        }
        void EmpilhaNumero(std::string num) /// Empilha toda uma string de inteiros.
        {
            for(int i = 0; i < capacidade; i++)
            {
                int elem = (num[i] - 48);   // Conversão explicita pela tabela ASCII
                EmpilhaElemento(elem);      // Empilha o elemento na pilha correspondente
            }
        }
        int desempilha()                    /// Retorna numero no topo da pilha
        {
            if(!vazia())
                return dados[topo--];
            else
                return -1; // Retorna -1 que é tratado nas funções
        }
        int retornanumpos(int p)                    /// Retorna numero da posicao de dados
        {
            if(!vazia())
                return dados[p];
            else
                return -1;
        }
        void inverter()                     /// Inverte os dados da pilha
        {
            int t = tamanho();
            int *aux = new int[t];
            for(int i = 0, j = t-1 ; i < t || j >= 0 ; i++ , j--)
                    aux[j] = dados[i];
            delete(dados);
            dados = aux;
        }
        void imprimir()                     /// Imprime a pilha
        {
            if(!vazia())
            {
                for(int i=0; i <= topo; i++)
                {
                    std::cout << dados[i];
                }
            }
            std::cout << std::endl;
        }
        void imprimeresultado()                 /// Imprime a pilha do resultado
        {
            if(!vazia())
            {
                for(int i=topo; i >= 0; i--)
                {
                    std::cout << dados[i];
                }
                std::cout << std::endl;
            }
        }
        void somar(LongNum num2)  /// Soma a pilha, com a passada por parâmetro e preenche a pilha com a soma
        {
            LongNum num;  // Copia o primeiro numero
            for(int i=0; i < capacidade; i++)
               num.EmpilhaElemento(this->retornanumpos(i));

            delete []dados;     // Desaloca o primeiro numero
            topo = -1;

            int var1, var2, soma, elev=0;   // Variáveis Auxiliares

            for(int i=0; i < num.tamanho(); i++)
            {
                var1 = num.desempilha();  // Captura o valor do topo da pilha 1
                var2 = num2.desempilha();   // Captura o valor do topo da pilha 2

                if(var1 == -1)  // Caso o topo retorne -1, para se uma pilha for maior que a outra
                    var1 = 0;   // O valor -1 passa a ser zero, neutro na soma
                if(var2 == -1)
                    var2 = 0;

                soma = var1 + var2 + elev;  // A soma será os dois elementos mais o número elevado

                elev = soma / 10;           // O numero elevado será o que passar da base 10
                soma = soma % 10;           // O resto dessa soma por 10 será o valor da soma

                this->EmpilhaElemento(soma);
            }
            if(elev > 0)
            {
                this->EmpilhaElemento(elev); // Ultimo elemento da soma para caso as duas pilhas serem do mesmo tamanho
            }

        }
        void dobrar(LongNum *numDobro)              /// Dobra o valor
        {
            if(!vazia())
            {
                int dobro, elev=0;   // Variáveis Auxiliares

                for(int i=0; i < capacidade; i++)
                {
                    dobro = 2 * desempilha() + elev;

                    elev = dobro / 10;
                    dobro = dobro % 10;

                    numDobro->EmpilhaElemento(dobro);
                }
                if(elev > 0)
                    numDobro->EmpilhaElemento(elev);
            }
        }
        void metade(int tam, LongNum *numResultado)
        {
            LongNum numDiv(tam);                // Pilha para as divisões
            LongNum numResto(tam);              // Pilha para o resto
            int resultado=0, div=0, resto=0;    // Variáveis auxiliares

            for(int i = capacidade-1; i >= 0; i--)
            {
                int aux = this->desempilha();       // Desempilha o numero a partir das unidades
                div = aux / 2;                      // Captura a divisão por 2
                resto = aux % 2;                    // Captura o resto da divisão por 2
                numDiv.EmpilhaElemento(div);        // Empilha o resultado da divisão
                numResto.EmpilhaElemento(resto);    // Empilha o resultado do resto
            }
            for(int i = 0; i < capacidade; i++)
            {
                div = resto = resultado = 0;        // Inicializa as variáveis
                div = numDiv.desempilha();          // Desempilha as divisões até as unidades

                if(i == 0)
                    resultado = div;                // Se for o primeiro algarismo, o primeiro digito
                else                                // do resultado será ele
                {
                    resto = numResto.desempilha();  // Desempilha o resto do algarismo anterior
                    resultado = ((div*2) + (resto*10))/2;   // Calcula o resultado para a posição desse algarismo
                }
                numResultado->EmpilhaElemento(resultado);    // Salva a posição do resultado  na pilha
            }
        }

        void diferenca(LongNum *num)               /// Calcula diferença
        {
            LongNum dif;        // Pilha de resultado
            int emp = 0;        // Variável auxiliar para empréstimo

            for(int i=0; i < this->capacidade; i++)
            {
                int aux1 = this->desempilha();  // Captura valor a partir das unidades
                int aux2 = num->desempilha();   // Captura valor a partir das unidades

                if(aux1 == -1) aux1 = 0;    // Troca para 0 caso já esteja vazia
                if(aux2 == -1) aux2 = 0;    // Troca para 0 caso já esteja vazia

                if(aux1 < aux2)
                {
                    if(emp == 0)
                    {
                        dif.EmpilhaElemento((10+aux1) - aux2);
                        emp++;
                    }
                    else
                    {
                         dif.EmpilhaElemento(((10-emp)+aux1) - aux2);
                    }
                }
                else if(aux1 == aux2)
                {
                    if(emp == 0)
                    {
                        dif.EmpilhaElemento(aux1 - aux2);
                    }
                    else
                    {
                         dif.EmpilhaElemento(((10-emp)+aux1) - aux2);
                    }
                }
                else
                {
                    if(emp == 0)
                    {
                        dif.EmpilhaElemento(aux1 - aux2);
                    }
                    else
                    {
                         dif.EmpilhaElemento((aux1-emp) - aux2);
                         emp--;
                    }
                }
            }

            dif.imprimeresultado();
        }

        void multiplica(LongNum *num, LongNum *Resultado)   /// Não Funcional não deu tempo de revisar e
        {                                                   /// enxugar o código, funciona para alguns números
            int aux1, aux2, M;
            LongNum *tabela = new LongNum[this->capacidade];    // Aloca o resultado das multiplicações

            for(int i=this->capacidade-1; i >=0; i--)  // Realiza a multiplicação de cada parcela
            {
                aux1 = this->retornanumpos(i);
                int elev = 0; // Auxiliar para valores excedidos

                for(int j= num->capacidade-1; j >= 0; j--)
                {
                    aux2 = num->retornanumpos(j);
                    M = (aux1 * aux2) + elev;

                    if(M<10)
                    {
                        tabela[i].EmpilhaElemento(M);
                        elev=0;
                    }
                    else
                    {
                        int aux = M%10;
                        elev = M/10;
                        tabela[i].EmpilhaElemento(aux);
                    }
                    //std::cout << "Num1: " << aux1 << " - Num2: " << aux2 << " = Result: " << M << " Elev: " << elev << std::endl;
                }
                tabela[i].EmpilhaElemento(elev);
            }

            for(int i=0; i < this->capacidade; i++)
                tabela[i].inverter();   // Inverte os valores da tabela

            // Realizando a soma da Multiplicação das parcelas
            int rep = this->capacidade-1;
            int elevado = 0;

            for(int i=0; i < this->capacidade+1; i++)
            {
                int num1=0, num2=0, soma =0;

                if(i < this->capacidade)
                    num1 = tabela[rep].desempilha();

                if(i > 0)
                    num2 = tabela[rep+1].desempilha();

                if(num1 == -1)  // Caso o topo retorne -1, para se uma pilha for maior que a outra
                    num1 = 0;   // O valor -1 passa a ser zero, neutro na soma
                if(num2 == -1)
                    num2 = 0;

                soma = num1 + num2 + elevado;  // A soma será os dois elementos mais o número elevado

                elevado = soma / 10;           // O numero elevado será o que passar da base 10
                soma = soma % 10;           // O resto dessa soma por 10 será o valor da soma
                std::cout << " Elev: " << elevado << " Soma: " << soma << std::endl;
                Resultado->EmpilhaElemento(soma);
                rep--;
            }
            if(elevado > 0)
            {
                Resultado->EmpilhaElemento(elevado); // Ultimo elemento da soma para caso as duas pilhas serem do mesmo tamanho
            }
            Resultado->imprimeresultado();
        }
        ~LongNum()
        {
            if(dados)
                delete []dados;
        }

};

#endif // NUMBERS_H
