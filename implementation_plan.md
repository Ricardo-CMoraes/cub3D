# Plano de correção da Norminette — parser

1. Extrair a normalização do mapa e seus auxiliares de `parse_map.c` para um
   novo módulo do parser.
2. Dividir a validação de tiles/paredes em módulos com até cinco funções por
   arquivo e funções com no máximo 25 linhas.
3. Atualizar os protótipos internos e o `Makefile`, preservando a interface
   pública de `parser.h`.
4. Compilar e executar a Norminette nos arquivos alterados.
