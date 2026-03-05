# Sistema de Gerenciamento Clínico Médico

## Visão Geral
Este sistema oferece um **gerenciamento completo** para clínicas médicas, incluindo cadastro de médicos e pacientes, agendamento de consultas e geração de relatórios. Desenvolvido em C com foco em **estruturas de dados eficientes** e **manipulação segura de arquivos**, o sistema organiza informações médicas críticas de forma confiável.

## Funcionalidades Principais

### 👨‍⚕️ Módulo Médicos
- Cadastro de médicos com CRM único
- Atualização de especialidades e contatos
- Listagem completa de profissionais
- Remoção segura de registros

### 👨 Módulo Pacientes
- Cadastro com validação de CPF
- Atualização de dados pessoais
- Busca por ID ou CPF
- Gerenciamento de contatos

### 📅 Módulo Consultas
- Agendamento com validação de data/hora
- Controle de status (agendada/realizada/cancelada)
- Relação médico-paciente integrada
- Pesquisa por especialidade

### 📊 Módulo Relatórios
- Consultas por paciente/médico
- Estatísticas por especialidade
- Agenda diária automática
- Exportação para arquivos texto

## Estrutura Técnica
```bash
SistemaClinico/
├── Arquivos/               # Armazenamento de dados
├── Codigos/
│   ├── Main.c              # Menu principal
│   ├── Medico.c            # Gestão de médicos
│   ├── Paciente.c          # Gestão de pacientes
│   ├── Consulta.c          # Agendamento
│   ├── Relatorios.c        # Geração de relatórios
│   ├── Auxiliar.c          # Funções utilitárias
│   ├── tipos.h             # Definições de estruturas
│   ├── Medico.h
│   └── ... 
└── README.md               # Documentação
```

## Pré-requisitos
- Compilador C (GCC recomendado)
- Sistema operacional Linux/Windows/macOS
- 5MB de espaço em disco

## Compilação e Execução
```bash
# Compilar o projeto
gcc -o clinica Codigos/*.c -I Codigos/Headers

# Executar o sistema
./clinica
```

## Documentação Técnica
| Conceito               | Implementação                                                                 |
|------------------------|-------------------------------------------------------------------------------|
| **Alocação Dinâmica**  | Uso de `malloc`/`realloc` em vetores expansíveis                              |
| **Manipulação de Arquivos** | Armazenamento em CSV com funções de leitura/escrita (`fscanf`, `fprintf`) |
| **Structs**            | `Medico`, `Paciente` e `Consulta` como estruturas principais                 |
| **Enums**              | `ESPECIALIDADE` e `statusConsulta` para controle de estados                  |
| **Validação**          | Funções dedicadas para CPF, CRM, datas e nomes                               |

## Exemplos de Uso
1. **Cadastrar novo médico:**
   - Selecione "Médicos" > "Cadastrar"
   - Informe nome, CRM válido (6 dígitos), especialidade e contato

2. **Agendar consulta:**
   - Acesse "Consultas" > "Agendar"
   - Informe CPF do paciente e CRM do médico
   - Insira data/hora no formato DD/MM/AAAA HH:MM

3. **Gerar relatório:**
   - Navegue até "Relatórios"
   - Escolha entre:
     * Consultas por paciente
     * Agenda diária
     * Estatísticas por especialidade

## Licença
Este projeto está licenciado sob a [MIT License](https://opensource.org/licenses/MIT).
