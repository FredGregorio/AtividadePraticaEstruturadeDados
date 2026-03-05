# Jogo de Cartas em C (Terminal)

## Descrição

Este é um projeto simples em linguagem C que implementa um jogo de cartas para 2 a 4 jogadores, jogado no terminal. Os jogadores compram e descartam cartas, seguindo a regra de que a carta descartada deve ter o mesmo valor ou naipe da carta no topo da pilha de descarte.

---

## Como Compilar

Para compilar o jogo, use o seguinte comando no terminal:


```bash
gcc -Wall -o jogo Main.c Deck.c Player.c Actions.c StackCards.c QueueActions.c Game.c
```

Isso irá compilar todos os arquivos `.c` e gerar um executável chamado `jogo`.

---

## Como Jogar

1. Execute o jogo:

```bash
./jogo
```

2. No menu inicial, escolha iniciar um novo jogo e informe o número de jogadores (entre 2 e 4).

3. Durante o jogo, na sua vez, você verá:
   - Suas cartas
   - A carta no topo da pilha de descarte

4. Escolha uma ação:

   - **1: Comprar uma carta** - Pega uma carta do baralho.
   - **2: Descartar uma carta** - Descarta uma carta da sua mão que seja compatível (mesmo valor ou mesmo naipe que a carta do topo do descarte).

5. O objetivo é ficar sem cartas na mão. O primeiro jogador que descartar todas as suas cartas vence!

---

## Estrutura do Projeto

O projeto está organizado nos seguintes arquivos:

- `main.c` - Controla o menu inicial e o fluxo geral do jogo
- `Game.c` - Implementa a lógica principal do jogo
- `Player.c` - Gerencia as ações e informações do jogador
- `Deck.c` - Cria e embaralha o baralho
- `StackCards.c` - Implementa as operações de pilha para as cartas
- `QueueActions.c` - Gerencia a fila de jogadores (quem joga em cada turno)
- `Actions.c` - Implementa as ações de comprar e descartar cartas
- `types.h` - Define as estruturas de dados e tipos usados no jogo

---

## Regras do Jogo

1. **Compatibilidade de Cartas**: Para descartar uma carta, ela deve ter:
   - O mesmo **valor** (por exemplo: 'A', '2', 'K') OU
   - O mesmo **naipe** (por exemplo: 'H' para Copas, 'D' para Ouros) 
   que a carta no topo da pilha de descarte.

2. **Reciclagem do Baralho**: Se o baralho principal acabar:
   - Todas as cartas da pilha de descarte (exceto a carta do topo) são viradas e embaralhadas
   - Formam um novo baralho para continuar o jogo

3. **Vitória**: O primeiro jogador que ficar sem cartas na mão vence o jogo!


## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).