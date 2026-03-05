# Sistema de Gerenciamento de Livros em C

Este projeto é um sistema de gerenciamento de livros desenvolvido em linguagem C, que permite carregar, atualizar e salvar informações de livros em um arquivo texto.

## Funcionalidades Principais

- **Carregar livros** de um arquivo CSV
- **Atualizar informações** de livros existentes (ISBN, título, autor, gênero)
- **Salvar alterações** no arquivo de dados
- **Gerenciamento de IDs** automático para novos livros
- **Interface interativa** para modificação de campos

## Estrutura do Projeto

```
📁 projeto-livros/
├── 📁 arquivos/
│   └── 📝 livros.txt        # Arquivo de dados dos livros
├── 📝 biblioteca.h          # Definições de estruturas e protótipos
├── 📝 livro.c               # Implementação das funções
└── 📝 main.c                # Programa principal
```

## Formato do Arquivo de Dados (`livros.txt`)

```csv
id,ISBN,titulo,autor,genero
1,9788532530783,O Senhor dos Anéis,J.R.R. Tolkien,1
2,9788532530837,Harry Potter,J.K. Rowling,2
3,9788576572008,O Hobbit,J.R.R. Tolkien,1
```

Colunas:
1. **id**: Identificador único (inteiro)
2. **ISBN**: Código do livro (13 caracteres)
3. **titulo**: Título do livro (string)
4. **autor**: Autor do livro (string)
5. **genero**: Código numérico do gênero (enumeração)

## Como Usar

1. **Atualizar um livro**:
   - O sistema solicitará o ISBN do livro
   - Permite modificar campos individuais:
     - ISBN
     - Título
     - Autor
     - Gênero
   - Oferece opção de salvar ou descartar alterações

2. **Fluxo de trabalho**:
   ```mermaid
   graph TD
     A[Início] --> B[Carregar livros]
     B --> C[Solicitar ISBN]
     C --> D{Encontrado?}
     D -->|Sim| E[Modificar campos]
     D -->|Não| F[Livro não encontrado]
     E --> G{Salvar?}
     G -->|Sim| H[Atualizar arquivo]
     G -->|Não| I[Descartar alterações]
     H & I --> J[Liberar memória]
   ```

## Requisitos para Compilação

- Compilador C (gcc, clang, etc.)
- Sistema operacional: Windows, Linux ou macOS

## Compilação e Execução

```bash
# Compilar o programa
gcc -o gerenciador_livros main.c livro.c

# Executar o programa
./gerenciador_livros
```

## Estruturas de Dados

```c
enum GENERO {
    FICCAO,
    FANTASIA,
    ROMANCE,
    TERROR,
    BIOGRAFIA,
    HISTORIA
};

typedef struct {
    int id;
    char ISBN[14];
    char titulo[100];
    char autor[100];
    enum GENERO genero;
} Livros;
```

## Funções Implementadas

1. **`void atualizarLivro()`**  
   Gerencia todo o processo de atualização de livros

2. **`void carregarLivros(Livros **livros, int *total)`**  
   Carrega livros do arquivo para memória

3. **`void salvarLivros(Livros *livros, int total)`**  
   Salva os livros no arquivo CSV

4. **`int gerarNovoId(const char *caminhoArquivo)`**  
   Gera um novo ID único para livros

5. Funções auxiliares:
   - `void receberISBN(char *isbn)`
   - `void receberTitulo(char *titulo)`
   - `void receberNome(char *nome)`
   - `void receberGenero(enum GENERO *genero)`
   - `const char* generoParaTexto(enum GENERO genero)`

## Melhorias Futuras

- Implementar CRUD completo (Criar, Ler, Atualizar, Deletar)
- Adicionar pesquisa por título/autor
- Implementar interface gráfica
- Adicionar sistema de empréstimos
- Desenvolver módulo de relatórios estatísticos

## Contribuição

Contribuições são bem-vindas! Siga os passos:
1. Faça um fork do projeto
2. Crie uma branch com sua feature (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Abra um Pull Request

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.