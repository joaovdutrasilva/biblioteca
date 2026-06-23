#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

void selecionarLivro() {

    FILE *arquivo = fopen("livros.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");
    string nome;
    string autor;
    char linha[100];
    char nomeLivro[100];
    char autorLivro[100];
    char ano[20];
    int disponivel;
    bool encontrado = false;

    cout << "Digite o nome do livro que deseja selecionar: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite o nome do autor do livro que deseja selecionar: ";
    getline(cin, autor);

    if (arquivo == NULL) {
        cout << endl << "Erro ao abrir o arquivo!" << endl;
        fclose(arquivoTemp);
        fclose(arquivo);
        remove("temp.txt");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%99[^|]|%99[^|]|%19[^|]|%d", nomeLivro, autorLivro, ano, &disponivel);

        if (nome == nomeLivro && autor == autorLivro) {
            if (disponivel == 0) {
                cout << "Livro indisponivel no momento." << endl;
                fclose(arquivo);
                fclose(arquivoTemp);
                remove("temp.txt");
                return;
            }
        cout << "____________________________________________" << endl << endl;
        cout << linha;
        cout << "Livro emprestado com sucesso!" << endl;
        cout << "____________________________________________" << endl;

        disponivel = 0;
        encontrado = true;

        fprintf(arquivoTemp, "%s|%s|%s|%d\n", nomeLivro, autorLivro, ano, disponivel);

        } else {
            fputs(linha, arquivoTemp);
        }
    }

    if (!encontrado) {
        cout << "Livro nao encontrado." << endl;
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("livros.txt");
    rename("temp.txt", "livros.txt");

    if (remove("livros.txt") == 0 ) {
        cout << "Arquivo removido com sucesso." << endl;
    } else {
        cout << "Erro ao remover o arquivo." << endl;
    }
}

void buscarLivroPorDisponibilidade() {
    FILE *arquivo = fopen("livros.txt", "r");
    char linha[100];
    char nomeLivro[100];
    char autor[100];
    char ano[20];
    int disponivel;
    bool encontrado = false;

    if (arquivo == NULL) {
        cout << endl << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    cout << "____________________________________________" << endl
         << endl;
    cout << endl << "Livros disponiveis" << endl;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        sscanf(linha, "%99[^|]|%99[^|]|%19[^|]|%d", nomeLivro, autor, ano, &disponivel);

        if (disponivel == 1) {
            cout << "____________________________________________" << endl
                 << endl;
            cout << linha;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Livro nao encontrado." << endl;
    }

    fclose(arquivo);
}

void buscarLivroPorAutor() {
    FILE *arquivo = fopen("livros.txt", "r");
    string autor;
    char linha[100];
    char nomeLivro[100];
    char autorLivro[100];
    char ano[20];
    int disponivel;
    bool encontrado = false;
    cout << "____________________________________________" << endl
         << endl;
    cout << "Digite o autor do livro que deseja buscar: ";
    cin.ignore();
    getline(cin, autor);

    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        sscanf(linha, "%99[^|]|%99[^|]|%19[^\n]|%d", nomeLivro, autorLivro, ano, &disponivel);

        if (autor == autorLivro) {
            cout << "____________________________________________" << endl
                 << endl;
            cout << linha;
            cout << "____________________________________________" << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Livro nao encontrado." << endl;
    }

    fclose(arquivo);
}

void buscarLivroPorNome() {
    FILE *arquivo = fopen("livros.txt", "r");
    string nome;
    char linha[100];
    char nomeLivro[100];
    char autor[100];
    char ano[20];
    int disponivel;
    bool encontrado = false;
    cout << "____________________________________________" << endl
         << endl;
    cout << "Digite o nome do livro que deseja buscar: ";
    cin.ignore();
    getline(cin, nome);

    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        sscanf(linha, "%99[^|]|%99[^|]|%19[^\n]|%d", nomeLivro, autor, ano, &disponivel);

        if (nome == nomeLivro){
            cout << "____________________________________________" << endl
                 << endl;
            cout << linha;
            cout << "____________________________________________" << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Livro nao encontrado." << endl;
    }

    fclose(arquivo);
}

void listarlivros() {
    FILE *arquivo = fopen("livros.txt", "r");
    ;
    char linha[100];
    char escolha;

    if (arquivo == NULL) {
        cout << "____________________________________________" << endl;
        cout << "Nao foi possivel abrir o arquivo." << endl;
        cout << "____________________________________________" << endl;
        return;
    }

    cout << "____________________________________________" << endl;
    cout << endl
         << "LIVROS CADASTRADOS" << endl;

    while (fgets(linha, sizeof(linha), arquivo)) {
        cout << "____________________________________________" << endl
             << endl;
        cout << linha << endl;
    }

    cout << "____________________________________________" << endl
         << endl;
    cout << "Deseja selecionar algum livro? (s/n): ";
    cin >> escolha;

    if (escolha == 's' || escolha == 'S') {
        selecionarLivro();
    }

    fclose(arquivo);
}

void cadastrarLivro() {
    FILE *arquivo = fopen("livros.txt", "a");

    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string nome, autor, ano;
    int disponivel = 1;
    cout << "CADASTRO DE LIVRO______________________________" << endl;
    cin.ignore();

    cout << "Digite o nome do livro: ";
    getline(cin, nome);

    cout << "Digite o nome do autor: ";
    getline(cin, autor);

    cout << "Digite o ano de publicacao: ";
    getline(cin, ano);

    fprintf(arquivo, "%s|%s|%s|%d\n", nome.c_str(), autor.c_str(), ano.c_str(), disponivel);
    fclose(arquivo);
    cout << endl
         << "LIVRO CADASTRADO COM SUCESSO!" << endl;
}

int main() {
    int escolha;
    while (true) {
        cout << endl
             << "BIBLIOTECA________________________________" << endl;
        cout << "1. Cadastrar livro" << endl;
        cout << "2. Listar livros" << endl;
        cout << "3. Buscar livro por nome" << endl;
        cout << "4. Buscar livro por autor" << endl;
        cout << "5. Buscar livros disponiveis" << endl;
        cout << "6. Devolver livro" << endl;
        cout << "7. Remover livro" << endl;
        cout << "___________________________________________" << endl
             << endl;

        cin >> escolha;

        switch (escolha) {
        case 1:
            cadastrarLivro();
            break;
        case 2:
            listarlivros();
            break;
        case 3:
            buscarLivroPorNome();
            break;
        case 4:
            buscarLivroPorAutor();
            break;
        case 5:
            buscarLivroPorDisponibilidade();
            break;
        default:
            break;
        }
    }

    return 0;
}