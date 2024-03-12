#include <stdio.h>
#include <stdlib.h>
#include <stack>
//verificar se a posição esta dentro da matriz antes de testar as posições e depois so ir chamando o walk novamente 
// Matriz de char representando o labirinto
char** maze; 

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;


// Representação de uma posição
struct pos_t {
    int i;
    int j;
};

// Estrutura de dados contendo as próximas
// posições a serem exploradas no labirinto
std::stack<pos_t> valid_positions;

// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
    pos_t initial_pos;
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", &num_rows, &num_cols);
    maze = (char**)malloc(num_rows * sizeof(char*));
    for (int i = 0; i < num_rows; ++i) {
        maze[i] = (char*)malloc((num_cols + 1) * sizeof(char));
        fscanf(file, "%s", maze[i]);
        for (int j = 0; j < num_cols; ++j) {
            if (maze[i][j] == 'e') {
                initial_pos.i = i;
                initial_pos.j = j;
            }
        }
    }
    fclose(file);
    return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
    for (int i = 0; i < num_rows; ++i) {
        printf("%s\n", maze[i]);
    }
}

// Função responsável pela navegação.
// Recebe como entrada a posição inicial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
    while (!valid_positions.empty()) {
        pos = valid_positions.top();
        valid_positions.pop();
        maze[pos.i][pos.j] = '.';
        // Limpa a tela - pode não funcionar em todos os sistemas operacionais
        system("clear");
        print_maze();
        
        if (maze[pos.i][pos.j] == 's') {
            return true;
        }else{

        if (pos.i > 0 && maze[pos.i - 1][pos.j] != 'x') {
            valid_positions.push({pos.i - 1, pos.j});
        }
        if (pos.i < num_rows - 1 && maze[pos.i + 1][pos.j] != 'x') {
            valid_positions.push({pos.i + 1, pos.j});
        }
        if (pos.j > 0 && maze[pos.i][pos.j - 1] != 'x') {
            valid_positions.push({pos.i, pos.j - 1});
        }
        if (pos.j < num_cols - 1 && maze[pos.i][pos.j + 1] != 'x') {
            valid_positions.push({pos.i, pos.j + 1});
        }
		}
    }
    return false;
}

int main(int argc, char* argv[]) {

	const char* name ="/workspaces/maze_runner/data/maze.txt";
    // carregar o labirinto com o nome do arquivo recebido como argumento
    pos_t initial_pos = load_maze(name);
	print_maze();
    // chamar a função de navegação
    //bool exit_found = walk(initial_pos);

    // Tratar o retorno (imprimir mensagem)
    /*if (exit_found) {
        printf("Saída encontrada!\n");
    } else {
        printf("Saída não encontrada.\n");
    }
	*/
    // Liberar memória alocada para a matriz
    for (int i = 0; i < num_rows; ++i) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
