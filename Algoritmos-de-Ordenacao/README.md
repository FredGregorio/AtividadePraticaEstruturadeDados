# Projeto de Comparação de Algoritmos de Ordenação

Este projeto implementa e compara o desempenho de diferentes algoritmos de ordenação em C, além de incluir uma versão didática do Gnome Sort.

## Estrutura de Arquivos

- `sort.h`: Cabeçalho com declarações das funções de ordenação
- `sort.c`: Implementações dos algoritmos de ordenação
- `comparativo.c`: Programa principal que compara o tempo de execução
- `gnomeSortDidatico.c`: Demonstração passo a passo do Gnome Sort

### Conteúdo do sort.h
```c
void gnomeSort(int *vetor, int tamanho);
void insertionSort(int *vetor, int tamanho);
void bubbleSort(int *vetor, int tamanho);
void quickSort(int *vetor, int left, int right);
void mergeSort(int *vetor, int left, int right);
```

## Algoritmos Implementados

1. **Gnome Sort** (`gnomeSort`)
2. **Insertion Sort** (`insertionSort`)
3. **Bubble Sort** (`bubbleSort`)
4. **Quick Sort** (`quickSort`)
5. **Merge Sort** (`mergeSort`)

## Como Compilar e Executar

### Requisitos
- Compilador GCC
- Sistema Linux (recomendado)

### Compilação
```bash
# Compilar todos os programas
gcc -c sort.c -o sort.o
gcc comparativo.c sort.o -o comparativo
gcc gnomeSortDidatico.c sort.o -o gnome_didatico
```

### Execução
**Programa Comparativo:**
```bash
./comparativo
```

**Saída Esperada:**
```
Gnome Sort: X.XXXXXX segundos
Quick sort: X.XXXXXX segundos
Merge sort: X.XXXXXX segundos
Insertion sort: X.XXXXXX segundos
Bubble sort: X.XXXXXX segundos
```

**Versão Didática do Gnome Sort:**
```bash
./gnome_didatico
```
Gera um arquivo `GnomeSort.txt` com o estado do vetor em cada iteração.

## Resultados Esperados (Exemplo)
Para um vetor de 50.000 elementos:

| Algoritmo       | Tempo Médio (s) |
|-----------------|-----------------|
| Quick Sort      | 0.005           |
| Merge Sort      | 0.008           |
| Insertion Sort  | 0.550           |
| Gnome Sort      | 1.200           |
| Bubble Sort     | 5.800           |

## Funcionalidades Didáticas
O programa `gnomeSortDidatico.c` inclui:
- Três cenários de teste:
  - Vetor aleatório: `{3,7,6,4,8,5,9,2}`
  - Melhor caso (ordenado): `{2,3,4,5,6,7,8,9}`
  - Pior caso (invertido): `{9,7,6,5,4,3,2}`
- Geração de arquivo de log com o estado do vetor em cada passo
- Implementação detalhada para fins educacionais

## Observações
1. Os tempos de execução podem variar dependendo do hardware
2. O Bubble Sort e Gnome Sort são significativamente mais lentos para grandes conjuntos
3. O Quick Sort geralmente apresenta melhor desempenho para dados aleatórios
4. O arquivo `GnomeSort.txt` é sobrescrito a cada execução

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).