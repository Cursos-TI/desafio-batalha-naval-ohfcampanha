#include <stdio.h>
#include <stdlib.h>

// Definicoes de tamanho e valores
#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5 // 5x5 para as habilidades
#define VALOR_AGUA '0'
#define VALOR_NAVIO '3'
#define VALOR_HABILIDADE '5'

// Funcao para criar e preencher a matriz da habilidade CONE (5x5)
void criar_cone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    printf("-> Criando Habilidade: CONE (%dx%d)\n", TAM_HABILIDADE, TAM_HABILIDADE);
    int centro = TAM_HABILIDADE / 2; // Centro da matriz (2)

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Logica do Cone: Quanto mais distante do topo (i=0), mais largo fica.
            // O cone aponta para baixo (i=0 e i=1 tem 1 celula, i=2 tem 3, etc.)
            // A largura do cone é 2*i + 1
            if (abs(j - centro) <= i) {
                 habilidade[i][j] = 1; // 1 = Afetado
            } else {
                 habilidade[i][j] = 0; // 0 = Não Afetado
            }
        }
    }
}

// Funcao para criar e preencher a matriz da habilidade CRUZ (5x5)
void criar_cruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    printf("-> Criando Habilidade: CRUZ (%dx%d)\n", TAM_HABILIDADE, TAM_HABILIDADE);
    int centro = TAM_HABILIDADE / 2; // Centro da matriz (2)

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Logica da Cruz: A linha e a coluna central são marcadas.
            if (i == centro || j == centro) {
                habilidade[i][j] = 1; // 1 = Afetado
            } else {
                habilidade[i][j] = 0; // 0 = Não Afetado
            }
        }
    }
}

// Funcao para criar e preencher a matriz da habilidade OCTAEDRO/LOSANGO (5x5)
void criar_octaedro(int habilidade[TAM_HABILIDADE][TAM_TABULEIRO]) {
    printf("-> Criando Habilidade: OCTAEDRO (Losango) (%dx%d)\n", TAM_HABILIDADE, TAM_HABILIDADE);
    int centro = TAM_HABILIDADE / 2; // Centro da matriz (2)

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Logica do Losango (Octaedro): A soma das distâncias ao centro deve ser <= centro
            // abs(i - centro) é a distância vertical ao centro
            // abs(j - centro) é a distância horizontal ao centro
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1; // 1 = Afetado
            } else {
                habilidade[i][j] = 0; // 0 = Não Afetado
            }
        }
    }
}

// Funcao para sobrepor a matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                        int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                        int origem_linha, int origem_coluna) {
    
    int offset = TAM_HABILIDADE / 2; // Deslocamento para centralizar a habilidade (2)

    // Percorre a matriz da habilidade
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            
            // Se a celula da habilidade está marcada (valor 1)
            if (habilidade[i][j] == 1) {
                
                // Calcula as coordenadas reais no tabuleiro (centralizando)
                int tab_linha = origem_linha + i - offset;
                int tab_coluna = origem_coluna + j - offset;

                // Condicional para garantir que a área de efeito permaneça dentro dos limites do tabuleiro
                if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO && 
                    tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                    
                    // Sobreescreve apenas se a posição não for um navio (valor 3), 
                    // garantindo que os navios sejam visualmente priorizados se estiverem na area de efeito
                    if (tabuleiro[tab_linha][tab_coluna] != 3) {
                         tabuleiro[tab_linha][tab_coluna] = VALOR_HABILIDADE - '0'; // Marcamos com 5
                    }
                }
            }
        }
    }
}

// Funcao principal
int main() {
    
    // Arrays de coordenadas para exibicao
    char coluna [TAM_TABULEIRO] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int linha [TAM_TABULEIRO] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 1. Definicao do Tabuleiro (com navios)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0}; // Inicializa tudo com 0

    // Posicionamento dos Navios (valor 3)
    tabuleiro[0][1] = 3; tabuleiro[0][2] = 3; tabuleiro[0][3] = 3; // Horizontal
    tabuleiro[3][6] = 3; tabuleiro[4][6] = 3; tabuleiro[5][6] = 3; // Vertical
    tabuleiro[7][7] = 3; tabuleiro[8][8] = 3; tabuleiro[9][9] = 3; // Diagonal
    
    printf("----------------------------------------\n");
    printf("--- Simulador de Habilidades de Area ---\n");
    printf("----------------------------------------\n\n");
    
    // 2. Criacao das Matrizes de Habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);
    
    printf("\n");

    // 3. Integrar Habilidades ao Tabuleiro (Definindo Pontos de Origem)
    
    // CONE: Ponto de Origem na posicao (Linha 5, Coluna 2)
    int origem_cone_l = 5;
    int origem_cone_c = 2;
    printf("-> Aplicando CONE na origem: %c%d\n", coluna[origem_cone_c], linha[origem_cone_l]);
    aplicar_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);

    // CRUZ: Ponto de Origem na posicao (Linha 1, Coluna 8) - Onde ja existe um Navio
    int origem_cruz_l = 1;
    int origem_cruz_c = 8;
    printf("-> Aplicando CRUZ na origem: %c%d\n", coluna[origem_cruz_c], linha[origem_cruz_l]);
    aplicar_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);

    // OCTAEDRO: Ponto de Origem na posicao (Linha 8, Coluna 4)
    int origem_octa_l = 8;
    int origem_octa_c = 4;
    printf("-> Aplicando OCTAEDRO na origem: %c%d\n", coluna[origem_octa_c], linha[origem_octa_l]);
    aplicar_habilidade(tabuleiro, octaedro, origem_octa_l, origem_octa_c);

    printf("\n");

    // 4. Exibir o Tabuleiro Final
    printf("--- Tabuleiro Final com Habilidades ---\n");
    printf("Legenda: %c=Agua, %c=Navio, %c=Area de Efeito\n\n", VALOR_AGUA, VALOR_NAVIO, VALOR_HABILIDADE);
    
    // Imprime as Colunas (1 a 10)
    printf("   "); 
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf(" %d", linha[i]);
    }
    printf("\n"); 

    // Imprime as Linhas (A a J) e o Conteudo
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        // Imprime a letra da linha
        printf(" %c ", coluna[j]); 
        
        for (int i = 0; i < TAM_TABULEIRO; i++){
            
            
            if (tabuleiro[j][i] == 3) {
                printf(" %c", VALOR_NAVIO);
            } else if (tabuleiro[j][i] == 5) {
                printf(" %c", VALOR_HABILIDADE);
            } else {
                printf(" %c", VALOR_AGUA);
            }
        }
        printf("\n"); 
    }

    return 0;
}
