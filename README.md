*Este projeto foi criado como parte do currículo da 42 por rida-cos, jnovais.*

# cub3D

## Descrição

O **cub3D** é um projeto da 42 School inspirado no lendário Wolfenstein 3D, o primeiro jogo de tiro em primeira pessoa (FPS) do mundo. O objetivo principal deste projeto é criar um motor gráfico de raycasting 3D em tempo real, escrito puramente em C e utilizando a biblioteca gráfica MiniLibX.

Este projeto permite explorar conceitos fundamentais da computação gráfica, matemática aplicada (trigonometria, vetores e matrizes), gerenciamento de janelas e eventos (inputs), renderização de texturas e otimização de performance. Ele serve como uma introdução robusta ao desenvolvimento de motores gráficos e à programação em baixo nível de interfaces visuais interativas.

## Instruções

### Pré-requisitos

Para compilar e executar o projeto, você precisará das seguintes dependências:

**macOS:**
```bash
# Ferramentas de linha de comando do XCode
xcode-select --install
```

**Linux / WSL2:**
```bash
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

### Instalação

Clone o repositório em sua máquina:

```bash
git clone <repo_url> cub3D
cd cub3D
```

Certifique-se de que a biblioteca MiniLibX está corretamente posicionada no diretório `libs/`. O projeto está estruturado para suportar `mlx_mac` para macOS (Metal) e `mlx_linux` para ambientes Linux.

### Compilação

O projeto inclui um `Makefile` com as seguintes regras disponíveis:
- `make` ou `make all`: Compila o executável `cub3D`.
- `make clean`: Remove os arquivos objeto intermediários.
- `make fclean`: Remove os arquivos objeto e o executável final.
- `make re`: Recompila todo o projeto do zero.
- `make norm`: Executa a ferramenta Norminette nos diretórios fonte (`src/` e `includes/`).

### Execução

Para iniciar o jogo, execute o binário passando o caminho de um mapa válido `.cub` como argumento:

```bash
./cub3D maps/test.cub
```

**Controles Básicos:**
- `W`, `A`, `S`, `D`: Movimentam a perspectiva pelo labirinto (frente, esquerda, trás, direita).
- `←` e `→` (Setas): Rotacionam a câmera (visão) para a esquerda ou direita.
- `ESC` ou botão de fechar a janela: Encerram o programa de forma limpa, sem vazamentos de memória.

## Recursos

### Referências Clássicas
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - O tutorial mais completo e amplamente utilizado para entender e implementar a lógica matemática por trás do DDA e raycasting.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Documentação não-oficial extensa para entender os hooks, eventos e gerenciamento de imagens do MiniLibX.

### Materiais de Estudo do Projeto
- [Simulação de Raycasting no Desmos](https://www.desmos.com/calculator/ipqm4bs6qd) - Simulação interativa criada para ilustrar visualmente o comportamento dos vetores de direção (`dir`) e do plano da câmera (`plan`), bem como o funcionamento da rotação e do cálculo de disparo de raios.

### Uso de Inteligência Artificial

Em consonância com o encorajamento da 42 (*"Desenvolva habilidades de prompt — tanto para codificação quanto para outras tarefas — que beneficiarão sua carreira futura"*), a inteligência artificial foi empregada neste projeto de forma responsável, metodológica e crítica. 

Não utilizamos a IA como um mero gerador de código final (copiar e colar), mas sim como uma ferramenta avançada de aprendizado e orquestração de fluxo de trabalho. As principais aplicações incluíram:

1. **Agentic Development & Pair Programming:** A IA foi integrada ao repositório por meio de regras estritas (arquivos `AGENTS.md`) definindo contratos claros sobre a arquitetura do projeto, convenções da Norminette e responsabilidades individuais dos alunos (`rida-cos` e `jnovais`).
2. **12factor Agentics Ops:** Aplicamos metodologias modernas para gerenciar as "operações" da IA, garantindo que o agente atuasse com determinismo dentro de limites arquiteturais bem definidos e escopos de código isolados, facilitando a validação humana iterativa.
3. **Engenharia de Prompt para Aprendizado:** Utilizamos a IA ativamente para discutir abordagens matemáticas de otimização no DDA e designs de parsing para validação segura de mapas fechados. As discussões geradas eram posteriormente validadas com colegas, refinando a implementação conjunta do grupo e garantindo domínio completo sobre todo código inserido.

#### Referências de Estudo sobre IA e Agentic Ops
- [Anthropic Learn - Guia de aprendizado sobre IA e Engenharia de Prompt](https://www.anthropic.com/learn)
- [12 Factor Agent Ops - Metodologia para agentes de IA](https://www.12factoragentops.com)
- [Artigo Fábio Akita - Como usar IA em projetos de verdade](https://akitaonrails.com/2026/02/20/do-zero-a-pos-producao-em-1-semana-como-usar-ia-em-projetos-de-verdade-bastidores-do-the-m-akita-chronicles/)
- [Vídeo de Referência - IA e Desenvolvimento (YouTube)](https://youtu.be/yDO21vewdes?si=wydUPbgAtf6ZVg7g)
