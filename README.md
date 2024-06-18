# agendamentos_clinicos
Mini projeto criado como nota final da disciplina de Estrutura de dados


# Documentação do Sistema de Agendamentos

## Introdução

Este documento apresenta a documentação para um sistema de agendamentos desenvolvido em C++. O sistema permite agendar, marcar como concluído e consultar agendamentos de pacientes, priorizando-os de acordo com a gravidade (normal, intermediária e grave).

## Estrutura do Projeto

O código está organizado em uma única implementação principal (`main.cpp`), contendo funções auxiliares e principais para gerenciar a fila de agendamentos.

## Componentes Principais

### Estrutura `gerenciador`

A estrutura `gerenciador` representa um nó na fila de agendamentos, armazenando as informações do paciente e um ponteiro para o próximo nó na fila.

#### Atributos:

- `string nome`: Nome do paciente.
- `int idade`: Idade do paciente.
- `string cpf`: CPF do paciente no formato XXX.XXX.XXX-XX.
- `string espec`: Especialidade do atendimento.
- `int prioridade`: Prioridade do atendimento (1 - Normal, 2 - Intermediária, 3 - Grave).
- `gerenciador *prox`: Ponteiro para o próximo paciente na fila.

### Funções Auxiliares

#### `void menu()`

Exibe o menu de opções para o usuário.

#### `void limpaTela()`

Limpa a tela do console. Usa `system("cls")` para Windows e `system("clear")` para Linux/macOS (comentado).

#### `void pausa()`

Pausa a execução do programa. Usa `system("pause")` para Windows.

#### `void verificaEntrada()`

Verifica se a entrada de dados falhou e limpa o buffer de entrada. Lança uma exceção em caso de entrada inválida.

#### `bool validarCPF(const string &cpf)`

Valida se o CPF está no formato correto (XXX.XXX.XXX-XX) usando expressões regulares.

#### `bool verificaPrioridade(int &prioridade)`

Verifica se a prioridade está dentro do intervalo válido (1 a 3).

#### `void obterDados(string &nome, int &idade, string &cpf, string &espec, int &prioridade)`

Obtém os dados do paciente, garantindo que as entradas sejam válidas e, se necessário, solicita novamente.

### Funções Principais

#### `void criarFila(gerenciador *&ini, gerenciador *&fim)`

Inicializa a fila de agendamentos, definindo os ponteiros de início e fim como NULL.

#### `bool vazia(gerenciador *&ini, gerenciador *&fim)`

Verifica se a fila de agendamentos está vazia.

#### `void inserirElemento(gerenciador *&ini, gerenciador *&fim, string nome, int idade, string CPF, string espec, int prioridade)`

Insere um novo paciente na fila, respeitando a ordem de prioridade. Pacientes com maior prioridade são inseridos no início da fila.

#### `void removeElemento(gerenciador *&ini, gerenciador *&fim)`

Remove o paciente do início da fila. Se a fila estiver vazia, exibe uma mensagem apropriada.

#### `void mostrarFila(gerenciador *ini)`

Exibe todos os pacientes na fila, listando suas informações e prioridades.

### Função `main()`

A função principal do programa. Configura a localidade, inicializa a fila, exibe o menu e processa as opções do usuário até que ele decida sair do sistema.

#### Fluxo da Função `main()`

1. **Configuração Inicial**: Define a localidade para permitir caracteres especiais e inicializa a fila de agendamentos.
2. **Loop Principal**:
    - Exibe o menu.
    - Captura e valida a opção do usuário.
    - Executa a ação correspondente:
        - **Opção 0**: Sai do sistema.
        - **Opção 1**: Obtém dados do paciente e insere na fila.
        - **Opção 2**: Remove o paciente do início da fila.
        - **Opção 3**: Mostra todos os pacientes na fila.
        - **Opção Inválida**: Exibe mensagem de erro e retorna ao menu.

## Conclusão

Este sistema de agendamentos desenvolvido em C++ proporciona uma maneira eficiente de gerenciar a fila de pacientes, priorizando-os de acordo com a gravidade de seus casos. A estrutura modular e as verificações robustas de entrada garantem a integridade dos dados e a facilidade de uso.
