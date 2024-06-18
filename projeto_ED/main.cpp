#include <iostream>
#include <cstdlib> // Necessário para usar o 'system'
#include <unistd.h> // Necessário para usar o 'sleep'
#include <locale> // Necessário para usar setlocale
#include <limits> // Necessário para usar numeric_limits
#include <regex> // Necessário para usar regex

using namespace std;

struct gerenciador {
    string nome;
    int idade;
    string cpf;
    string espec;
    int prioridade; // 1 - ok, 2 - medio, 3 - grave
    gerenciador *prox;
};

// FUNÇÕES AUXILIARES
void menu(){
    cout << "====== Agendamentos =====" << endl;
    cout << "1 - Agendar" << endl;
    cout << "2 - Marca como concluído" << endl;
    cout << "3 - Consultar agendamentos" << endl;
    cout << "0 - Sair do sistema" << endl;
    cout << "R: ";
}

void limpaTela() {
    system("cls"); // Para Windows
    // system("clear"); // Para Linux, macOS
}

void pausa() {
    system("pause"); // Para Windows
}

// Função para verificar se a entrada de dados falhou e limpar o buffer
void verificaEntrada() {
    if (cin.fail()) {
        cin.clear(); // Limpa o estado de falha
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora os caracteres no buffer até a nova linha
        throw invalid_argument("Entrada inválida. Tente novamente.");
    }
}

// Função para validar o CPF no formato XXX.XXX.XXX-XX
bool validarCPF(const string &cpf) {
    const regex padraoCPF("\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2}");
    return regex_match(cpf, padraoCPF);
}

// Verificar se a prioridade esta presente nas existentes no sistema
bool verificaPrioridade(int &prioridade){
    if(prioridade > 3 || prioridade < 1){
        return false;
    }else{
        return true;
    }
}

// Função auxiliar para obter dados do candidato
void obterDados(string &nome, int &idade, string &cpf, string &espec, int &prioridade) {
    bool entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Digite o nome: ";
            getline(cin >> ws, nome);
            verificaEntrada();
            entradaValida = true;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
    entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Digite a idade: ";
            cin >> idade;
            verificaEntrada();
            entradaValida = true;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
    entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Digite o CPF (no formato XXX.XXX.XXX-XX): ";
            cin >> cpf;
            verificaEntrada();
            if (!validarCPF(cpf)) {
                throw invalid_argument("Formato de CPF inválido. Tente novamente.");
            }
            entradaValida = true;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
    entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Digite a especialidade: ";
            getline(cin >> ws, espec);
            verificaEntrada();
            entradaValida = true;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
    entradaValida = false;
    while (!entradaValida) {
        try {
            cout << "Digite a prioridade: ";
            cin >> prioridade;
            verificaEntrada();
            if(!verificaPrioridade(prioridade)){
                throw invalid_argument("Prioridade inexistente, verifique a tabela:\n1 - Normal\n2 - Intermediária\n3 - Grave\nTente novamente.");
            }
            entradaValida = true;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
}

// FUNÇÕES PRINCIPAIS
void criarFila(gerenciador *&ini, gerenciador *&fim) {
    ini = NULL;
    fim = NULL;
}

bool vazia(gerenciador *&ini, gerenciador *&fim) {
    return ini == NULL && fim == NULL;
}

void inserirElemento(gerenciador *&ini, gerenciador *&fim, string nome, int idade, string CPF, string espec, int prioridade) {
    gerenciador *novo = new gerenciador;
    novo->nome = nome;
    novo->idade = idade;
    novo->cpf = CPF;
    novo->espec = espec;
    novo->prioridade = prioridade;
    novo->prox = NULL;
    // verificando se está vazia
    if (vazia(ini, fim)) {
        ini = novo;
        fim = novo;
    } else {
        if (prioridade > ini->prioridade) {
            novo->prox = ini;
            ini = novo;
        } else {
            gerenciador *atual = ini;
            gerenciador *anterior = NULL;

            while (atual != NULL && atual->prioridade >= prioridade) {
                anterior = atual;
                atual = atual->prox;
            }

            novo->prox = atual;

            if (anterior != NULL) {
                anterior->prox = novo;
            }

            if (atual == NULL) {
                fim = novo;
            }
        }
    }
}

// remove do início
void removeElemento(gerenciador *&ini, gerenciador *&fim){
    if (ini == NULL){
        cout << "Não há agendamentos." << endl;
    }else if (ini == fim){
        gerenciador * aux = ini;
        ini = NULL;
        fim = NULL;
        delete aux;
    }else{
        gerenciador *aux = ini;
        ini = ini->prox;
        delete aux;
    }
}

void mostrarFila(gerenciador *ini) {
    gerenciador *aux = ini;
    if(aux != NULL){
        int cont = 1;
        while (aux != NULL) {
            cout << "Paciente #" << cont << ": \nNOME: " << aux->nome << "\nIDADE " << aux->idade << "\nCPF: " << aux->cpf << "\nESPECIALIDADE: " << aux->espec << "\nPRIORIDADE: " << aux->prioridade << endl;
            cout << "==================================================" << endl;
            aux = aux->prox;
            cont++;
        }
    }else{
        cout << "Nenhum agendamento cadastrado." << endl;
    }
}

int main() {
    setlocale(LC_ALL, ""); // Permite caracteres especiais

    gerenciador *ini;
    gerenciador *fim;

    criarFila(ini, fim);

    string nome, cpf, espec;
    int idade, prioridade, op;

    do {
        bool entradaValida = false;
        while (!entradaValida) {
            menu();
            try {
                cin >> op;
                verificaEntrada();
                entradaValida = true;
            } catch (const invalid_argument &e) {
                cout << e.what() << endl;
                pausa();
            }
            limpaTela();
        }

        switch (op) {
            case 0:
                cout << "Saindo do sistema..." << endl;
                sleep(3); // delay
                break;
            case 1:
                obterDados(nome, idade, cpf, espec, prioridade);
                inserirElemento(ini, fim, nome, idade, cpf, espec, prioridade);
                pausa();
                limpaTela();
                break;
            case 2:
                removeElemento(ini, fim);
                pausa();
                limpaTela();
                break;
            case 3:
                mostrarFila(ini);
                pausa();
                limpaTela();
                break;
            default:
                cout << "Opção inválida, tente novamente!" << endl;
                pausa();
                limpaTela();
        }
    } while (op != 0);

    return 0;
}
