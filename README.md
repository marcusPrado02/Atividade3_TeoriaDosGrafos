# Atividade3_TeoriaDosGrafos

# Atribuição de Médicos para Feriados

Este projeto implementa um algoritmo para atribuir médicos a plantões durante feriados, garantindo que todas as restrições sejam atendidas.

## Estrutura do Projeto

O projeto consiste em dois modos de execução:

1. **Modo Usuário**: Permite ao usuário fornecer uma lista de feriados e informações sobre médicos disponíveis e suas preferências de férias.
2. **Modo Teste**: Executa um conjunto de testes predefinidos para validar a lógica do algoritmo.

## Estrutura do Código

### Arquivo `main.cpp`

O arquivo principal contém as seguintes funções:

- `bool atribuirMedico(...)`: Verifica se um médico pode ser atribuído a um dia específico.
- `bool encontrarAtribuicao(...)`: Encontra uma atribuição válida de médicos para os feriados.
- `void modoUsuario()`: Modo interativo para o usuário fornecer dados de entrada.
- `void mostrarCronograma(...)`: Exibe o cronograma completo das atribuições.
- `void executarTestes()`: Executa um conjunto de testes predefinidos.
- `int main(...)`: Função principal que decide qual modo executar com base nos argumentos fornecidos.

## Como Executar

### Compilação

Compile o código utilizando um compilador C++. Por exemplo, com `g++`:

```bash
g++ main.cpp -o programa
```

### Execução

#### Modo Usuário

Para executar no modo usuário, apenas execute o programa sem argumentos:

```bash
./programa
```

O programa solicitará as seguintes informações:
1. Lista de feriados.
2. Número de médicos disponíveis.
3. Dias disponíveis e de férias para cada médico.
4. Valor de `c` (número máximo de dias que cada médico pode trabalhar).

#### Modo Teste

Para executar no modo teste, passe o argumento `test`:

```bash
./programa test
```

O modo teste executará uma série de testes predefinidos e exibirá os resultados.

## Estrutura dos Testes

### Teste 1
- **Feriados**: `{1, 43, 44, 88, 112, 122, 151, 251, 286, 307, 320, 360}`
- **Médicos**: 8 médicos com diferentes dias disponíveis e de férias.
- **Capacidade (c)**: `2`

### Teste 2
- **Feriados**: `{5, 23, 47, 89, 123}`
- **Médicos**: 6 médicos com diferentes dias disponíveis e de férias.
- **Capacidade (c)**: `2`

### Teste 3
- **Feriados**: `{12, 45, 78, 134, 167, 201}`
- **Médicos**: 5 médicos com diferentes dias disponíveis e de férias.
- **Capacidade (c)**: `2`

### Teste 4
- **Feriados**: `{21, 56, 101, 149, 198, 254, 312}`
- **Médicos**: 6 médicos com diferentes dias disponíveis e de férias.
- **Capacidade (c)**: `2`

### Teste 5
- **Feriados**: `{13, 29, 63, 97, 142, 176, 221, 269, 315, 350}`
- **Médicos**: 6 médicos com diferentes dias disponíveis e de férias.
- **Capacidade (c)**: `3`

## Exemplo de Saída

### Modo Usuário

```
Você deseja usar a lista de feriados padrão (1) ou fornecer sua própria lista (2)? 1
Quantos médicos estão disponíveis? 3
Quantos dias o médico 0 está disponível para trabalhar em feriados? 3
Digite os dias disponíveis para o médico 0: 1 43 112
Quantos dias de férias o médico 0 escolheu? 2
Digite os dias de férias para o médico 0: 150 200
Digite o valor de c (número máximo de dias que cada médico pode trabalhar): 2

Atribuição possível:
Dia 1: Medico 0
Dia 43: Medico 0
Dia 44: Medico 1
...
```

### Modo Teste

```
Executando Teste 1
Tentando atribuir médico para o dia 1
Atribuindo médico 0 ao dia 1
...
Teste 1 passou!
Cronograma de Atribuições:
Dia 1: Médico 0
Dia 43: Médico 1
...
Todos os testes passaram!
```
