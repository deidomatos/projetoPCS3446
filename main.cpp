#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <list>
#include <vector>
#include <queue>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>

//############################################################
//############ PCS3446 - Sistemas de Programação #############
//############   Projeto final da disciplina     #############
//############                                   #############
//############     Prof. Dr. João José Neto      #############
//############    Aluno: David Almeida Matos     #############
//############################################################

using namespace std;

// Protótipo das funções a serem utilizadas no projeto
void carregarPrograma(string in, char memoria[340][2], int bloco[40][4], int id, int numeroInstrucao[5]);
int getEndereco(char varAuxiliar1, char varAuxiliar2, char varAuxiliar3);
void escreverDados(char memoria[2],char x, char y);
void somar(char ac[2]);
int pegarBlocoDados(int bloco[40][4], int id);


// Abaixo, as implementações das funções necessárias à execução do projeto

// Transforma uma variável do tipo char para o tipo int
int charParaInteger(char varAuxiliar)
{
    int u;
    switch(varAuxiliar)
    {
    case '0':
        u = 0;
        break;
    case '1':
        u = 1;
        break;
    case '2':
        u = 2;
        break;
    case '3':
        u = 3;
        break;
    case '4':
        u = 4;
        break;
    case '5':
        u = 5;
        break;
    case '6':
        u = 6;
        break;
    case '7':
        u = 7;
        break;
    case '8':
        u = 8;
        break;
    case '9':
        u = 9;
        break;
    case 'a':
        u = 10;
        break;
    case 'b':
        u = 11;
        break;
    case 'c':
        u = 12;
        break;
    case 'd':
        u = 13;
        break;
    case 'e':
        u = 14;
        break;
    case 'f':
        u = 15;
        break;
    default:
        u = 15;
        break;
    }
    return u;
}

// Pega o endereço necessário para a execução do programa
int getEndereco(char varAuxiliar1, char varAuxiliar2, char varAuxiliar3)
{
    int c,d,u;
    c = charParaInteger(varAuxiliar1);
    d = charParaInteger(varAuxiliar2);
    u = charParaInteger(varAuxiliar3);

    return c*16*16 + d*16 + u;

}

// Realiza a soma com base nos dados presentes no vector de char
void somar(char ac[2])
{
    switch(ac[1])
    {
    case '0':
        ac[1] = '1';
        break;
    case '1':
        ac[1] = '2';
        break;
    case '2':
        ac[1] = '3';
        break;
    case '3':
        ac[1] = '4';
        break;
    case '4':
        ac[1] = '5';
        break;
    case '5':
        ac[1] = '6';
        break;
    case '6':
        ac[1] = '7';
        break;
    case '7':
        ac[1] = '8';
        break;
    case '8':
        ac[1] = '9';
        break;
    case '9':
        ac[1] = 'a';
        break;
    case 'a':
        ac[1] = 'b';
        break;
    case 'b':
        ac[1] = 'c';
        break;
    case 'c':
        ac[1] = 'd';
        break;
    case 'd':
        ac[1] = 'e';
        break;
    case 'e':
        ac[1] = 'f';
        break;
    case 'f':
        ac[1] = '0';
        break;
    default:
        ac[1] = '0';
        break;
    }
}

// Pega o bloco de dados do sistema para execução
int pegarBlocoDados(int bloco[40][4], int id)
{
    for (int i = 0; i < 19; i++)
    {
        if(bloco[i][2] == id)
            return i;
    }
    return 0;
}

// Carrega o programa na memória para poder ser executado corretamente
void carregarPrograma(string codigo, char memoria[340][2], int bloco[40][4], int id, int numeroInstrucao[5])
{
    ifstream codigoEntrada;
    string linha;
    int d = 0;
    int pc = 0, encontrado = 0, k = 0, kAnterior = 0;
    codigoEntrada.open(codigo.c_str());
    if (codigoEntrada.fail())
        cout << "\n Erro: Arquivo nao encontrado";
    else
    {
        while (codigoEntrada.good())
        {
            while (encontrado == 0)
            {
                k++;
                if (bloco[k][0] == 0)
                {
                    pc = k*16;
                    bloco[k][0] = 1;
                    encontrado = 1;
                    bloco[kAnterior][1] = k;
                    bloco[kAnterior][2] = id;
                }
            }
            getline(codigoEntrada, linha);
            memoria[pc][0] = linha.at(0);
            memoria[pc][1] = linha.at(1);
            memoria[pc+1][0] = linha.at(2);
            memoria[pc+1][1] = linha.at(3);
            pc = pc+2;
            if (pc % 16 == 0 )
            {
                pc = 0;
                d++;
                kAnterior = k;
                encontrado = 0;
            }
        }
        numeroInstrucao[id] = (8*d)+(pc%16)/2;

        bloco[0][1] = -1;
        bloco[0][2] = -1;
        bloco[k][2] = id;
        bloco[k][1] = -1;
    }
}

// Escreve os dados obtidos na memória do Sistema Operacional
void escreverDados(char memoria[2],char x, char y)
{
    memoria[0] = x;
    memoria[1] = y;
}

// Função principal para execução do sistema operacional desenvolvido
int main()
{
    std::size_t encontrado;
    string in, temporario;
    char memoria[340][2];
    char ac1[2];
    char ac2[2];
    char operando1,operando2,operando3,operando4;
    int varAuxiliar, id = 0, c, ii;
    int bloco[40][4];
    string idPrograma[5];
    int numeroInstrucao[5];
    std::queue<int> fila;
    int id1 = -1, id2 = -1;
    int varAuxiliar3;
    int estado = 1;
    int pc1, pc2;
    int b1, b2;

    cout << endl <<         " ############################################################"  << endl;
    cout <<         " ############ PCS3446 - Sistemas de Programacao #############"  << endl;
    cout <<         " ############   Projeto final da disciplina     #############"  << endl;
    cout <<         " ############     Prof. Dr. Joao Jose Neto      #############"  << endl;
    cout <<         " ############    Aluno: David Almeida Matos     #############"  << endl;
    cout <<         " ############       Numero USP: 9344998         #############"  << endl;
    cout <<         " ############################################################"  << endl << endl;

    for (int i = 0; i < 5; i++)
        idPrograma[i] = "0";
    for (int i = 0; i < 319; i++)
        escreverDados(memoria[i], '0', '0');
    for (int i = 0; i < 19; i++)
    {
        bloco[i][0] = 0;
        bloco[i][1] = 0;
        bloco[i][2] = -1;
    }
    bloco[0][0] = 1;

    struct dirent *lsDiretorio;
    int operando = -1;
    DIR *diretorio;
    ifstream codigo;
    string linha, programa, varAuxiliar1, varAuxiliar2;

    while(operando != 0)
    {
        cout << endl <<  " >>>>>> MENU DE COMANDOS DISPONIVEIS <<<<<<" << endl << endl << endl;
        cout << " 1)  QLOAD" << endl;
        cout << " 2)  LOAD <nomePrograma>" << endl;
        cout << " 3)  ID" << endl;
        cout << " 4)  QUEUE <id>"<< endl;
        cout << " 5)  SHOW" << endl;
        cout << " 6)  RUN" << endl;
        cout << " 7)  KILL <numeroIdentificacao>" << endl;
        cout << " 8)  MEM <numeroBloco>" << endl;
        cout << " 9)  PMT <numeroIdentificacao>"  << endl;
        cout << " 10) MBT"  << endl;
        cout << " 11) END"<< endl << endl << endl;
        cout << " Por favor, escolha o comando e digite-o exatamente como" << endl;
        cout << " consta no menu, ou seja, utilizando letras maiusculas e" << endl;
        cout << " com os parametros apropriados: ";
        cin >> in;

        // Realiza a leitura do comando inserido pelo usuário
        //Comando QLOAD
        encontrado = in.find("QLOAD");
        if (encontrado!=std::string::npos)
            operando = 1;
        //Comando LOAD
        encontrado = in.find("LOAD");
        if (encontrado!=std::string::npos)
            operando = 2;
        //Comando ID
        encontrado = in.find("ID");
        if (encontrado!=std::string::npos)
            operando = 3;
        //Comando QUEUE
        encontrado = in.find("QUEUE");
        if (encontrado!=std::string::npos)
            operando = 4;
        //Comando SHOW
        encontrado = in.find("SHOW");
        if (encontrado!=std::string::npos)
            operando = 5;
        //Comando RUN
        encontrado = in.find("RUN");
        if (encontrado!=std::string::npos)
            operando = 6;
        //Comando KILL
        encontrado = in.find("KILL");
        if (encontrado!=std::string::npos)
            operando = 7;
        //Comando MEM
        encontrado = in.find("MEM");
        if (encontrado!=std::string::npos)
            operando = 8;
        //Comando PMT
        encontrado = in.find("PMT");
        if (encontrado!=std::string::npos)
            operando = 9;
        //Comando MBT
        encontrado = in.find("MBT");
        if (encontrado!=std::string::npos)
            operando = 10;
        //Comando END
        encontrado = in.find("END");
        if (encontrado!=std::string::npos)
            operando = 11;

        switch (operando)
        {
        case 1:
            temporario = "./programas";
            diretorio = opendir(temporario.c_str());
            cout << endl << " A seguir, os programas a serem carregados na fila do sistema operacional: " << endl;
            while ((lsDiretorio = readdir(diretorio)) != NULL)
            {
                string temporario = lsDiretorio->d_name;
                std::size_t encontrado = temporario.find(".txt");
                std::size_t encontrado2 = temporario.find("nnn.txt");
                if (encontrado2!=std::string::npos) {}
                else if (encontrado!=std::string::npos)
                {
                    string temporarioSemTxt = temporario.substr(0, temporario.find("."));
                    cout << "    " << temporarioSemTxt << endl;
                }
            }
            operando = -1;
            break;

        case 2:
            cin >> in;
            varAuxiliar1 = "./programas/"+in+".txt";
            varAuxiliar2 = "./programas/"+in+"nnn.txt";
            carregarPrograma(varAuxiliar1, memoria, bloco, id, numeroInstrucao);
            idPrograma[id++] = in;

            operando = -1;
            break;

        case 3:
            for (int i = 0; i < 5; i++)
            {
                if (idPrograma[i] != "0")
                    cout << "   Programa: " << idPrograma[i] << "   id: " << i << endl;
            }
            cout << endl<< endl;
            operando = -1;
            break;

        case 4:
            cin >> varAuxiliar;
            fila.push(varAuxiliar);
            if (id1 == -1 && !fila.empty())
            {
                id1 = fila.front();
                fila.pop();
                pc1 = 0;
                b1 = pegarBlocoDados(bloco, id1);
            }
            if (id2 == -1 && !fila.empty())
            {
                id2 = fila.front();
                fila.pop();
                pc2 = 0;
                b2 = pegarBlocoDados(bloco, id2);
            }

            operando = -1;
            break;

        case 5:
            if (id1 == -1 && !fila.empty())
            {
                id1 = fila.front();
                fila.pop();
                pc1 = 0;
                b1 = pegarBlocoDados(bloco, id1);
            }
            if (id2 == -1 && !fila.empty())
            {
                id2 = fila.front();
                fila.pop();
                pc2 = 0;
                b2 = pegarBlocoDados(bloco, id2);
            }
            if (id1 != -1)
            {
                cout << endl << "   Id Processo 1: "<< std::dec  << id1 << "    Somente faltam "  << numeroInstrucao[id1] << " instrucoes para o fim    Estado: ";
                if(estado)
                    cout << "em processamento" << endl;
                else
                    cout << "em espera" << endl;
            }
            else
            {
                cout << endl << "   Identificacao do processo 1: -" << endl;
            }
            if (id2 != -1)
            {
                cout << endl << "   Identificacao do processo 2: "<< std::dec  << id2 << "    Somente faltam "  << numeroInstrucao[id2] << " instrucoes para o fim    Estado: ";
                if(!estado)
                    cout << "processando..." << endl;
                else
                    cout << "esperando..." << endl;
            }
            else
            {
                cout << endl << "   Identificacao do processo 2: -"<< endl;
            }
            operando = -1;
            break;

        case 6:
            if(estado)
            {
                operando1 = memoria[b1*16+pc1][0];
                operando2 = memoria[b1*16+pc1][1];
                operando3 = memoria[b1*16+pc1+1][0];
                operando4 = memoria[b1*16+pc1+1][1];

                if(operando1 == '1')
                {
                    varAuxiliar3 = getEndereco(operando2, operando3, operando4);
                    ac1[0] = memoria[varAuxiliar3][0];
                    ac1[1] = memoria[varAuxiliar3][1];
                }
                else if(operando1 == '2')
                {
                    varAuxiliar3 = getEndereco(operando2, operando3, operando4);
                    memoria[varAuxiliar3][0] = ac1[0];
                    memoria[varAuxiliar3][1] = ac1[1];
                }
                else if(operando1 == '3')
                {
                    somar(ac1);
                }
                else if(operando1 == '4')
                {
                    estado = 0;
                }
                pc1+=2;
                numeroInstrucao[id1] -= 1;
                if(numeroInstrucao[id1] == 0)
                    id1 = -1;
                if (pc1 == 16)
                {
                    b1 = bloco[b1][1];
                    pc1 = 0;
                }
            }
            if(!estado)
            {
                operando1 = memoria[b2*16+pc2][0];
                operando2 = memoria[b2*16+pc2][1];
                operando3 = memoria[b2*16+pc2+1][0];
                operando4 = memoria[b2*16+pc2+1][1];

                if(operando1 == '1')
                {
                    varAuxiliar3 = getEndereco(operando2, operando3, operando4);
                    ac2[0] = memoria[varAuxiliar3][0];
                    ac2[1] = memoria[varAuxiliar3][1];
                }
                else if(operando1 == '2')
                {
                    varAuxiliar3 = getEndereco(operando2, operando3, operando4);
                    memoria[varAuxiliar3][0] = ac2[0];
                    memoria[varAuxiliar3][1] = ac2[1];
                }
                else if(operando1 == '3')
                {
                    somar(ac2);
                }
                else if(operando1 == '4')
                {
                    estado = 0;
                }
                pc2+=2;
                numeroInstrucao[id2] -= 1;
                if(numeroInstrucao[id2] == 0)
                    id2 = -1;
                if (pc2 == 16)
                {
                    b2 = bloco[b1][1];
                    pc1 = 0;
                }
            }
            if (estado)
                estado = 0;
            else
                estado = 1;

            operando = -1;
            break;

        case 7:
            cin >> varAuxiliar;
            if (id1 == varAuxiliar)
                id1 = -1;
            if (id2 == varAuxiliar)
                id2 = -1;
            operando = -1;
            break;

        case 8:
            cin >> varAuxiliar;
            cout << "                   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F" << endl;
            cout << "   endereco " << setfill('0') << setw(3) << std::hex << varAuxiliar << "   ";
            for (int i = 0; i < 16; i++)
            {
                cout << memoria[varAuxiliar*16+i][0] << memoria[varAuxiliar*16+i][1] << "  ";
            }
            cout << endl << endl;
            operando = -1;
            break;

        case 9:
            cin >> varAuxiliar;
            cout << "       Page Map Table para a identificacao = " << varAuxiliar << " :"<< endl;
            for (ii = 0; ii < 19; ii++)
            {
                if (bloco[ii][2] == varAuxiliar && bloco[ii][0] == 1 )
                {
                    c = 0;
                    if (bloco[ii][1] == -1 )
                        cout << "   Paginacao: " << c++ << "      Bloco: " << ii << endl;
                    else
                    {
                        while (bloco[ii][1] > 0 && c < 19)
                        {
                            cout << "   Paginacao: " << c++ << "      Bloco: " << ii << endl;
                            ii = bloco[ii][1];
                        }
                        cout << "   Paginacao: " << c << "      Bloco: " << ii << endl << endl;
                        break;
                    }
                }
            }
            operando = -1;
            break;

        case 10:
            cout << "                   0   1   2   3   4   5   6   7   8   9" << endl;
            cout << "         Bloco 0   ";
            for (int i = 0; i < 19; i++)
            {
                if (i == 10)
                {
                    cout << endl << "         Bloco 1   ";
                }
                if (bloco[i][0] == 1 && i > 0)
                    cout << bloco[i][2] << "   ";
                else
                    cout << "    ";
            }
            operando = -1;
            break;

        case 11:
            operando = 0;
            break;

        default:
            cout << endl << " O comando digitado nao e valido. Por favor, digite um dos comandos da lista exibida. Obrigado!" << endl << endl;
            break;
        }
    }
    return 0;
}
