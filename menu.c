
/* Algoritmo de menu interativo com o teclado em C*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Includes de ferramentas padrão do C

#include <windows.h>
#include <conio.h>
// Includes que contém as ferramentas necessárias pra manipulação do console e das cores do Windows.

#include <locale.h>
// Include que permite setar o método de exibição dos caracteres



void linhaCol(int lin, int col); // Parâmetros: Linha, Coluna
// Protótipo da função que posiciona o cursor de entrada de texto no console
void textColor(int letras, int fundo); // Parâmetros: Cor da letra, cor do fundo
// Protótipo da função que muda a cor do texto exibido
void box(int lin1, int col1, int lin2, int col2); // Parâmetros: Linha inicial, coluna inicial, linha final, coluna final (x1, y1; x2, y2)
// Protótipo da função que desenha o esqueleto do menu
int menu(int lin1, int col1, int qtd, char lista[][256]); // Parâmetros: Linha inicial, coluna inicial, quantidade de itens, lista de itens
// Protótipo da função que exibe a lista de opções dentro do menu e controla o sistema de seleção via teclado
void enter(void);
// Protótipo da função que faz uma pausa no programa e espera o usuário pressionar ENTER para continuar



// Enumeradores das cores:
enum{
    BLACK,                 //0
    BLUE,                  //1
    GREEN,                 //2
    CYAN,                  //3
    RED,                   //4
    MAGENTA,               //5
    BROWN,                 //6
    LIGHTGRAY,             //7
    DARKGRAY,              //8
    LIGHTBLUE,             //9
    LIGHTGREEN,            //10
    LIGHTCYAN,             //11
    LIGHTRED,              //12
    LIGHTMAGENTA,          //13
    YELLOW,                //14
    WHITE                  //15
};
// Cor da Letra

enum{
    _BLACK=0,                  //0
    _BLUE=16,                  //1
    _GREEN=32,                 //2
    _CYAN=48,                  //3
    _RED=64,                   //4
    _MAGENTA=80,               //5
    _BROWN=96,                 //6
    _LIGHTGRAY=112,            //7
    _DARKGRAY=128,             //8
    _LIGHTBLUE=144,            //9
    _LIGHTGREEN=160,           //10
    _LIGHTCYAN=176,            //11
    _LIGHTRED=192,             //12
    _LIGHTMAGENTA=208,         //13
    _YELLOW=224,               //14
    _WHITE=240                 //15       
};  
// Cor do fundo



// Enumeradores da Tabela ASCII:
enum{
    cedilhaMai = 128,       // Ç
    eAgudoMin = 130,        // é
    aCircunflexoMin = 131,  // â
    aGraveMin = 133,        // à
    cedilhaMin = 135,       // ç
    eCircunflexoMin = 136,  // ê
    eAgudoMai = 144,        // É
    oCircunflexoMin = 147,  // ô
    aAgudoMin = 160,        // á
    oAgudoMin = 162,        // ó
    uAgudoMin = 163,        // ú
    nTilMin = 164,          // ñ
    nTilMai = 165,          // Ñ
    aAgudoMai = 181,        // Á
    aCircunflexoMai = 182,  // Â
    aGraveMai = 183,        // À
    aTilMin = 198,          // ã
    aTilMai = 199,          // Ã
    eCircunflexoMai = 210,  // Ê
    iAgudoMai = 214,        // Í
    oAgudoMai = 224,        // Ó
    oCircunflexoMai = 226,  // Ô
    oTilMin = 228,          // õ
    oTilMai = 229,          // Õ
    uAgudoMai = 233         // Ú
};
// Letras

enum{
    retaVertical1 = 179,            // │
    teeEsquerdo1 = 180,             // ┤
    cantoSuperiorDireito1 = 191,    // ┐
    cantoInferiorEsquerdo1 = 192,   // └
    teeCima1 = 193,                 // ┴
    teeBaixo1 = 194,                // ┬
    teeDireito1 = 195,              // ├
    retaHorizontal1 = 196,          // ─
    cruz1 = 197,                    // ┼
    cantoInferiorDireito1 = 217,    // ┌
    cantoSuperiorEsquerdo1 = 218,   // 	┘
    teeEsquerdo2 = 185,             // ╣
    retaVertical2 = 186,            // ║
    cantoSuperiorDireito2 = 187,    // ╗
    cantoInferiorDireito2 = 188,    // ╝
    cantoInferiorEsquerdo2 = 200,   // ╚
    cantoSuperiorEsquerdo2 = 201,    // ╔
    teeCima2 = 202,                 // ╩
    teeBaixo2 = 203,                // ╦
    teeDireito2 = 204,              // ╠
    retaHorizontal2 = 205,          // ═
    cruz2 = 206                     // ╬
};
// Estrutura de menu

enum{
    teclaEnter = 13,
    teclaEsc = 27,
    teclaSetaCima = 72,
    teclaSetaBaixo = 80,
    teclaSetaEsquerda = 37,
    teclaSetaDireita = 39,
    teclaEspaco = 32,
    teclaBackspace = 8,
    teclaHome = 36,
    teclaDelete = 46
};
// Teclas do teclado



void textColor(int letra, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
    // Altera o atributo de texto para as cores selecionadas
}
// Função responsável pela cor do texto

void linhaCol(int lin, int col){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){col-1,lin-1});
    // Usa as coordenadas recebidas para posicionar o cursor
     
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    // Esse trecho é responsável por deixar o cursor invisível
}
// Função responsável por posicionar o cursor na tela

void box(int lin1, int col1, int lin2, int col2){
    int i, j;
    // Variáveis de controle de laços

    int tamlin, tamcol;
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;
    // Variáveis que determinam o tamanho do box (o esqueleto)
     
    //Montagem do Box:
    for(i=col1; i<=col2; i++){
        linhaCol(lin1,i);
        printf("%c", retaHorizontal2);
        linhaCol(lin2,i);
        printf("%c", retaHorizontal2);
    } // Linhas horizontais
        
    for(i=lin1; i<=lin2; i++){
        linhaCol(i,col1);
        printf("%c", retaVertical2);
        linhaCol(i,col2);
        printf("%c", retaVertical2);
    } // Colunas verticais

    for(i=lin1+1;i<lin2;i++){
        for(j=col1+1;j<col2;j++){
           linhaCol(i,j);printf(" ");
        }
    } // Espaços vazios no meio do esqueleto

    //Posição dos cantos:
    linhaCol(lin1,col1);
    printf("%c", cantoSuperiorEsquerdo2);
    // Canto superior esquerdo
    linhaCol(lin1,col2);
    printf("%c", cantoSuperiorDireito2);
    // Canto superior direito
    linhaCol(lin2,col1);
    printf("%c", cantoInferiorEsquerdo2);
    // Canto inferior esquerdo
    linhaCol(lin2,col2);
    printf("%c", cantoInferiorDireito2);
    // Canto inferior direito     
}
// Função responsável por montar o esqueleto do menu



int menu(int lin1, int col1, int qtd, char lista[][256]){
    int i; 
    // Variável de controle para laços
    int lin2, col2, tamMaxItem;
    // Variáveis para cálculo de posição
    int  opcao = 1, linha, teclaPressionada;
    
    // Cálculo das coordenadas:
    tamMaxItem = strlen(lista[0]);
    // Define um valor inicial pra comparar o tamanho máximo dos itens da lista pra assim criar um esqueleto compatível
    for(i=1; i<qtd;i++){
        if(strlen(lista[i])>tamMaxItem){
            tamMaxItem = strlen(lista[i]);
            // Atualiza o valor máximo até o momento caso seja encontrado um valor maior do que o anterior 
        }
    }
    // Compara o tamanho máximo de todos os itens da lista até achar o maior
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;
    // Determina o segundo valor de linhas e colunas
    
    // Montagem da tela:
    textColor(WHITE, _RED);
    setlocale(LC_ALL,"C"); // Bota os valores da tabela ASCII para o padrão do C
    box(lin1,col1,lin2,col2);
    
    // Laço das Opções
    while(1){
        linha = lin1 + 2;
        for(i=0;i<qtd;i++){           
           if(i+1 == opcao) textColor(BLACK, _WHITE);
           else textColor(WHITE, _RED);
        linhaCol(linha, col1 + 2);
        printf("%s", lista[i]);
        linha+=2;
        }
        // Destaca a opção selecionada com outra cor
       
        linhaCol(1, 1);
        teclaPressionada = getch();
        // Recebe a tecla
        linhaCol(22,1);
        
        // Opções:
        if(teclaPressionada == teclaEsc){ 
            opcao = 0; 
            break;
        } // Tecla ESC
        else if(teclaPressionada == teclaEnter){
            break;
        } // Tecla ENTER
        else if(teclaPressionada == teclaSetaCima){
            if(opcao > 1) opcao--; 
            // Se a opção for maior que 1, ou seja, for o segundo item ou algum item adiante, ele retorna ao item anterior
        } // Seta para cima
        else if(teclaPressionada == teclaSetaBaixo){
            if(opcao < qtd) opcao++;
            // Se a opção for menor do que a quantidade de itens, ou seja, não for o último item, ele avanca para o item seguinte
        } //Seta para baixo
    }
    return opcao;
    // Retorna o valor da opção selecionada ao pressionar ENTER
} 
// Função responsável por preencher o menu



void enter(){
    int teclaPressionada = 0;
    printf("\nPressione [ENTER] para continuar\n");
    do{
        teclaPressionada = getch();
        // Recebe qual tecla é pressionada
    } while(teclaPressionada != teclaEnter);
    // Roda o laço até que a tecla ENTER seja pressionada
    // Depois encerra a função e continua o programa
}
// Interrompe a execução do programa até que a tecla ENTER seja pressionada



int main(){
    system("MODE con cols=80 lines=40 ");
    // Modifica o tamanho da janela do console pra melhorar a exibição de acordo com a quantidade de linhas e de colunas
    system("color 80");
    // Muda a cor do fundo do console (atrás do menu)
    /* Cores disponíveis:
    0 = Preto        8 = Cinza
    1 = Azul         9 = Azul claro
    2 = Verde        A = Verde claro
    3 = Verde-água   B = Verde-água claro
    4 = Vermelho     C = Vermelho claro
    5 = Roxo         D = Lilás
    6 = Amarelo      E = Amarelo claro
    7 = Branco       F = Branco brilhante
    */

    int opcaoSelecionada, tamanhoLista = 5; // Alterar o valor "5" para o numero de itens da lista
    char lista[5][256] = {"Item 1", "Item 2", "Item 3", "Item 4", "Item 5"}; // Alterar o valor "5" para o numero de itens da lista
    // Lista com os itens que serão exibidos no menu

    while(true){
        opcaoSelecionada = menu(10, 10, tamanhoLista, lista);
        // Chama a função que dá início à exibição e recebe o valor da opção selecionada do menu
        if(opcaoSelecionada == 0){
            break;
        }
        // Se a opção for ESC (0), ele encerra o laço
    
        linhaCol(1, 1);
        textColor(WHITE, _MAGENTA);
        printf("\nEscolheu a op%c%co %d", cedilhaMin, aTilMin, opcaoSelecionada);
        // OPCIONAL: Exibe a opção selecionada no canto superior esquerdo da tela

        // Aplicação: Na maioria dos casos, é neste ponto em que você implementa o SEU código de acordo com a opção selecionada
    }
    // Laço que executa o menu e o sistema de seleção até que a tecla ESC seja pressionada
    /* Alternativa: O laço pode ser feito com um do{}while(opcaoSelecionada != 0) que executará
    o laço uma vez e se a opção selecionada for ESC (0), ele não entrará no laço novamente*/

    textColor(WHITE, _BLACK);
    linhaCol(24, 1);
    printf("");
    // Manda o cursor pro fim da tela e põe o texto na cor padrão para exibir a tela de finalização do programa
  
    return 0;
}
/* Função principal do menu, ela que dá início à exibição, ao sistema de seleção e tudo, portanto, a implementação de outro código
deverá ser feita dentro dos blocos já predefinidos*/


