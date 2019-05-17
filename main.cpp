#include <iostream>
#include "numbers.h"

using namespace std;

int main()
{
    int op; // Opcao

    do
    {
        cout << endl << "-------------------------------------" << endl;
        cout << "   CALCULOS COM NUMEROS EXTENSOS" << endl << endl;
        cout << "Escolha uma das opções abaixo: " << endl << endl;
        cout << "   1 - Soma de 2 números."  << endl;
        cout << "   2 - Dobro e Metade de um número." << endl;
        cout << "   3 - Diferença de 2 números." << endl;
        cout << "   0 - Sair."  << endl << endl;

        cout << "Digite opcao: ";
        cin >> op;

        if(op == 1)
        {
            string num1, num2;
            cout << endl << endl << "   -> SOMA DE DOIS NUMEROS" << endl << endl;
            cout << "Digite o primeiro numero: ";
            cin >> num1;
            cout << "Digite o segundo numero: ";
            cin >> num2;
            int tam1 = num1.length();
            int tam2 = num2.length();

            LongNum numLong1(tam1);
            LongNum numLong2(tam2);
            int maiorNum;   // Variável com o tamanho do maior numero

            if(numLong1.tamanho() > numLong2.tamanho())
                maiorNum = numLong1.tamanho();
            else
                maiorNum = numLong2.tamanho();

            LongNum numSoma(maiorNum);  // A soma terá no mínimo o tamanho do maior numero

            numLong1.EmpilhaNumero(num1);   // Empilha os valores digitados
            numLong2.EmpilhaNumero(num2);   // Empilha os valores digitados

            // Imprime os numeros na tela
            cout << endl << "  ";
            numLong1.imprimir();
            cout << "+ ";
            numLong2.imprimir();
            cout << "-";
            for(int i=0; i < maiorNum; i++)
                cout << "--";

            // RESULTADO DA SOMA
            cout << endl << "  ";
            numLong1.somar(numLong2); // Soma o numLong1, com numLong2 para numSoma
            numLong1.imprimeresultado(); // Imprime o resultado
            cout << endl;
        }
        else if(op == 2)
        {
            string num;
            cout << endl << endl << "   -> DOBRO E METADE DE UM NUMERO" << endl << endl;
            cout << "Digite o numero: ";
            cin >> num;
            int tam = num.length();

            LongNum numLong(tam);
            numLong.EmpilhaNumero(num);

            // Calculo do Dobro
            LongNum numDobro(tam);
            numLong.dobrar(&numDobro);
            cout << endl << "Dobro: ";
            numDobro.imprimeresultado();

            // Calculo da Metade
            LongNum numLong2(tam);
            numLong2.EmpilhaNumero(num);
            LongNum numMetade(tam);
            numLong2.metade(tam, &numMetade);
            cout << endl << "Metade: ";
            numMetade.imprimir();
        }
        else if(op == 3)
        {
            string num1, num2;
            cout << endl << endl << "   -> DIFERENÇA DE DOIS NUMEROS" << endl << endl;
            cout << "Digite o primeiro numero: ";
            cin >> num1;
            cout << "Digite o segundo numero: ";
            cin >> num2;
            int tam1 = num1.length();
            int tam2 = num2.length();

            LongNum a(tam1);
            LongNum b(tam2);
            a.EmpilhaNumero(num1);
            b.EmpilhaNumero(num2);
            cout << endl << "Diferença: ";
            a.diferenca(&b);

        }

    }while(op != 0);

    return 0;
}
