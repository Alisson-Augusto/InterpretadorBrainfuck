#include <iostream>
#include <fstream>
#include <string>

// Autor: Alisson Augusto
// desc: Intepretador simples de brainfuck

using namespace std;

char memoria[5000];
// Armazena as instruções que estão em um loop
char loopInstrucoes[5000];

bool inLoop = false;
// A lista de instruções dentro do loop já foram todas adicionadas ?
bool isLoopFull = false;

unsigned short indexMemoriaLoop = 0;
unsigned short indexMemoria = 0;

void executaInstrucao(char instrucao) {

    if (inLoop == true) {
        if (!isLoopFull) {
            // Armazena Instruções que estão em loop
            loopInstrucoes[indexMemoriaLoop] = instrucao;
        }
        indexMemoriaLoop++;
    }

    // Instruções possíveis +-<>[].,
    switch (instrucao) {
        case '+': // Soma a célula atual
            memoria[indexMemoria]++;
            break;
        case '-': // Subtrai valor da célula atual
            memoria[indexMemoria]--;
            break;
        case '<': // Volta o ponteiro para a célula anterior
            indexMemoria = indexMemoria > 0 ? indexMemoria - 1 : 0;
            break;
        case '>': // Avança ponteiro para a próxima célula
            indexMemoria++;
            break;
        case '[': // Inicia Lanço de repetição
            inLoop = true;
            break;
        case ']': // Apenas termina o loop quando a célula tiver o valor de 0
          // cout << "Terminei de delimitar o loop!" << endl;
            isLoopFull = true;


            if (memoria[indexMemoria] != 0) {
                inLoop = true;
                indexMemoriaLoop = 0;
            }
            else {
                inLoop = false;
                isLoopFull = false;
                // Limpa a memória das instruções de loop
                for (unsigned short i = 0; i < 5000; i++)
                    loopInstrucoes[i] = 0;
            }

            break;
        case '.': // Imprime o valor da célula atual
            cout << memoria[indexMemoria];
            break;
        case ',':
            memoria[indexMemoria] = getchar();
            break;
        default: // Comentário
            break;
    }
}

int main(int argc, char *argv[]) {
    if(argc <= 1) {
      cout << "ERRO: Voce deve informar o arquivo com o codigo brainfuck" << endl;
    }else {
      fstream programa;
      string filename = argv[1];

      programa.open(filename, ios::in);

      if (programa.is_open()) {
          string linha;
          while (getline(programa, linha)) {
              for (unsigned int i = 0; i < linha.size(); i++) {
                  // Lê cada instrução sequencialmente
                  char instrucao = linha[i];

                  // cout << "INSTRUCAO : " << instrucao << endl;
                  executaInstrucao(instrucao);
                    
                  // Itera todas as instruções de loop
                  while (inLoop && isLoopFull) {
                      // cout << "Estou em loop! " << indexMemoriaLoop << endl;
                      executaInstrucao(loopInstrucoes[indexMemoriaLoop]);
                  }

              }
          }
          programa.close();
      }
    }


    return 0;
}