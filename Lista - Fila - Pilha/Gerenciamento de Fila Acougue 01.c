/*
	Algoritmo que representa o gerenciamento de fila de acougue de supermercado.
	Entradas: inteiro: 1 - Retirar uma nova senha
			  inteiro: 2 - Chamar Cliente
			  inteiro: 3 - Mostrar Fila de Espera
	Saídas: Fila de espera em ordem de chegada
	Autor: Alisson Jaques
*/

#include<stdio.h>  /* Biblioteca para entrada e saida de dados */
#include<stdlib.h> /* Biblioteca para manipulacao de constantes */
#include<string.h> /* Biblioteca para manipulacao de strings */

/*
	A estrutura Fila representa uma fila de acougue de supermercado,
	cada elemento da Fila representa uma senha tirada no sistema. A primeira
	senha tirada é a primeira a ser chamada.

*/
typedef struct celulas{
    int senha;                /* a senha do cliente */
    struct celulas * proximo; /* o proximo elemento da Fila */
}Fila;

/*
	A funcao retornaUltimoElemento(Fila) retorna o ultimo elemento da Fila.
*/
Fila * retornaUltimoElemento(Fila * cabeca){
    Fila *p;
    Fila *ultimo;
    for (p = cabeca->proximo; p != NULL; p = p->proximo){ /* percorre todos os elementos da Fila */
        if(p->proximo==NULL){ /* se p for o ultimo elemento */
            ultimo = p; /* ultimo recebe p */
        }
    }
    return ultimo;
} /* fim da funcao retornaUltimoElemento(Fila) */

/*
	A funcao retirarSenhaNovoCliente(Fila) permite que o usuario retire uma nova senha
	para atendimento. Cada elemento eh inserido no final da Fila, o que permite que sejam
	retirados elementos de forma crescente de chegada (o primeiro que chegou sera o primeiro a sair).

*/
void retirarSenhaNovoCliente(Fila *cabeca){
    if(cabeca->proximo==NULL){ /* se a Fila estiver vazia, faca */
        Fila *novaCelula;                    /* declara um apontador do tipo Fila */
        novaCelula = malloc (sizeof (Fila)); /* aloca memoria para a nova ordem de atendimento */
        novaCelula->senha = 1; /* a primeira sempre sera o numero 1 */
        printf("Senha de atendimento: %i\n", novaCelula->senha); /* informa a senha retirada no terminal da aplicacao */
        novaCelula->proximo = NULL; /* o primeiro elemento inserido tambem eh o ultimo elemento */
        cabeca->proximo = novaCelula; /* atualiza o proximo da cabeca com o elemento inserido */
    }
    else{ /* senao */
        Fila *novoUltimo;                    /* declara um apontador do tipo Fila */
        novoUltimo = malloc (sizeof (Fila)); /* aloca memoria para a nova ordem de atendimento */
        Fila *ultimo = retornaUltimoElemento(&(*cabeca)); /* ultimo aponta para o ultimo elemento da Fila */
        novoUltimo->proximo = NULL; /* o ultimo elemento da Fila sempre aponta para NULL */
        ultimo->proximo = novoUltimo; /* atuazila o ultimo elemento da Fila */
        novoUltimo->senha = ultimo->senha; /* atualiza a senha do novo ultimo com a senha do ultimo anterior */
        novoUltimo->senha += 1; /* incrementa a senha do ultimo elemento em uma unidade */
        printf("Senha de atendimento: %i\n", novoUltimo->senha); /* informa a senha retirada no terminal da aplicacao */
    } /* fim-se */
} /* fim da funcao retirarSenhaNovoCliente(Fila) */

/*
	A funcao chamarCliente(Fila) chama o cliente no topo da Fila, o primeiro cliente que retirou a senha eh
	chamado primeiro, e assim sucessivamente.

*/
void chamarCliente(Fila *cabeca){
    printf("Cliente de senha %i, gentileza comparecer ao caixa.\n",cabeca->proximo->senha); /* solicita ao cliente que compareca ao caixa do acougue */
    retirarDaFila(&(*cabeca)); /* chama a funcao retirarDaFila(Fila), que remove o elemento do topo da Fila */
} /* fim da funcao chamarCliente(Fila) */

/*
	A funcao mostrarFilaEspera(Fila) imprime no terminal todos os senhas que ainda nao foram
	atendidas, de forma crescente de chegada.
*/
void mostrarFilaEspera(Fila *cabeca){
    Fila *aux;
    for(aux=cabeca->proximo; aux!=NULL; aux=aux->proximo){ /* enquanto nao percorrer todos os elementos da Fila, faca: */
        printf("Senha: %i\n", aux->senha); /* imprime a senha que ainda nao foi chamada */
    }
} /* fim da funcao mostrarFilaEspera(Fila) */

/*
	A funcao retirarDaFila(Fila) retira o elemento do topo da Fila,
	atualiza o novo topo e desaloca a memoria do elemento removido.

*/
void retirarDaFila(Fila *cabeca){
    Fila *aux;             /* campo auxiliar */
    aux = cabeca->proximo; /* campo auxiliar recebe o topo da Fila */

    cabeca->proximo = cabeca->proximo->proximo; /* atualiza o novo topo da Fila */
    free(aux); /* desaloca a memoria do topo removido */
} /* fim da funcao retirarDaFila(Fila) */

/*
	A funcao liberarMemoriaFila(Fila) libera todas as memorias alocadas para
	os elementos da Fila.
*/
void liberarMemoriaFila(Fila *cabeca){
    Fila *noAtual;
    noAtual = cabeca;
    while (noAtual != NULL){ /* Enquanto noAtual for diferente de nulo, faca: */
        cabeca = noAtual->proximo; /* atualiza o novo elemento que a cabeca aponta */
        free(noAtual); /* libera o topo atual da Fila */
        noAtual = cabeca; /* atualiza o noAtual */
    }
} /* Fim da funcao liberarMemoriaFila(Cliente) */

/*
	A funcao main() permite a execucao dessa aplicacao e representa um programa que gerencia
	uma fila de acougue de supermercado.
*/
int main(){
    Fila *cabeca; 								/* A cabeca da Fila */
    cabeca = (Fila *) malloc (sizeof (Fila));   /* Aloca memoria para a cabeca da Fila */

    /* Verifica se conseguiu alocar */
	if (!cabeca) {
		printf("Nao conseguiu alocar a memoria.\n");
		exit(1);
	}

    cabeca->proximo = NULL; /* a cabeca da Fila comeca apontando para NULL */
    int opcao;

    do{
           /*
			O menu da aplicacao solicita ao usuario que escolha uma opcao e chama funcoes
			correspondentes de acordo com a escolha do usuario.
		   */
           printf("\n========================= Fila do Acougue =========================\n");
           printf("============================= Menu ================================\n\n");
           printf("Escolha uma das seguintes opcoes: \n\n");
           printf("1 - Retirar senha novo cliente\n");
           printf("2 - Chamar cliente\n");
           printf("3 - Mostrar fila de espera\n");
           printf("4 - Sair\n\n");
           printf("Digite sua escolha: ");
           scanf("%i",&opcao);
           fflush(stdin);

           switch(opcao){ /*Caso opcao seja: */
               case 1: /* Retirar senha novo cliente, faca: */
                   system("cls");
                   printf("\n======================= Senha de Atendimento ======================\n");
                   printf("-------------------------------------------------------------------\n");
                   retirarSenhaNovoCliente(&(*cabeca)); /* chama a funcao que retira uma nova senha para atendimento */
                   printf("-------------------------------------------------------------------\n");
                   printf("===================================================================\n");
                   system("pause");
                   system("cls");
                   break;
               case 2: /* Chamar cliente, faca: */
                   system("cls");
                   printf("\n========================== Chamando Cliente =======================\n");
                   printf("-------------------------------------------------------------------\n");
                   if(cabeca->proximo==NULL){ /* se a lista estiver vazia */
                       printf("Nao e possivel chamar, fila vazia.\n"); /* nao sera possivel chamar */
                   }
                   else{ /* senao */
                       chamarCliente(&(*cabeca)); /* chama o proximo cliente */
                   }
                   printf("-------------------------------------------------------------------\n");
                   printf("===================================================================\n");
                   system("pause");
                   system("cls");
                   break;
               case 3: /* Mostrar fila de espera, faca: */
                   system("cls");
                   printf("\n=========================== Fila de Espera ========================\n");
                   printf("-------------------------------------------------------------------\n");
                   if(cabeca->proximo==NULL){ /* se a fila estiver vazia */
                        printf("Fila vazia, todos os cliente foram atendidos.\n"); /* informa que a fila esta vazia */
                   }
                   else{ /* senao */
                       mostrarFilaEspera(&(*cabeca)); /* imprime no terminal a fila em ordem de chegada */
                   }
                   printf("-------------------------------------------------------------------\n");
                   printf("===================================================================\n");
                   system("pause");
                   system("cls");
                   break;
               case 4: /* Sair da aplicacao, faca: */
                   break;
               default: /* nenhuma das opcoes acima, faca: */
                   system("cls");
                   printf("\n=========================== Fila de Espera ========================\n");
                   printf("-------------------------------------------------------------------\n");
                   printf("Opcao invalida. Por favor, insira uma opcao valida.\n"); /* solicita ao usuario uma opcao valida */
                   printf("-------------------------------------------------------------------\n");
                   printf("===================================================================\n");
                   system("pause");
                   system("cls");
                   break;
           }

    }while(opcao!=4); /* enquanto o usuario nao escolher sair da aplicacao */
    printf("\n===================================================================\n");
    printf("======================= Programa Encerrado ========================\n");
    printf("===================================================================\n\n");
    liberarMemoriaFila(&(*cabeca)); /* desaloca todas as memorias dos elementos da Fila, caso o usuario ainda nao tenha retirado as senhas*/
    system("pause");
    return 0;
} /* fim da funcao main */
