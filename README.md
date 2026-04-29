# LI3 Flight System

Projeto em C para gestão de companhias aéreas, aeroportos, voos, passageiros e reservas.

## Visão Geral

Este repositório implementa um sistema de consulta e validação de dados de voo, com suporte a:
- leitura de ficheiros de entrada em formato específico
- validação de aeronaves, aeroportos, passageiros, voos e reservas
- diferentes modos de execução: programa principal, testes e interface interativa
- geração de resultados esperados em ficheiros de texto e CSV

## Estrutura do Projeto

- `src/` - código-fonte principal organizado por módulos
  - `entidades/` - entidades do domínio (aeronaves, aeroportos, passageiros, reservas, voos)
  - `gestor_entidades/` - lógica de gestão de entidades e dos gestores
  - `io/` - leitura de ficheiros, output e interface em terminal
  - `queries/` - interpretação de queries e funcionalidades de consulta
  - `utils/` - utilitários auxiliares
  - `validacoes/` - funções de validação para cada tipo de entidade
- `include/` - cabeçalhos do projeto
- `programas/` - entradas principais para os três executáveis
- `resultados/` - resultados gerados e ficheiros CSV de erro
- `resultados-esperados/` - saídas esperadas para comparação e testes
- `Makefile` - regras de compilação e limpeza
