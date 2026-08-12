*Este projeto foi criado como parte do currículo da 42 por rida-cos e jnovais.*

# cub3D

Uma recriação de um raycaster em primeira pessoa, inspirada em Wolfenstein 3D e desenvolvida em C com a MiniLibX.

## Descrição

O `cub3D` renderiza uma representação 3D do interior de um labirinto a partir da perspetiva do jogador. O projeto aplica ray-casting para transformar um mapa 2D em paredes texturizadas, com texturas distintas para Norte, Sul, Este e Oeste, e cores configuráveis para o chão e o teto.

O programa recebe uma cena no formato `.cub`. Antes de iniciar a janela, valida a configuração, os caminhos das texturas, as cores RGB, o mapa, a posição inicial do jogador e se o labirinto está totalmente fechado por paredes. Quando encontra uma configuração inválida, termina de forma limpa e apresenta uma mensagem de erro.

## Funcionalidades

- Ray-casting em tempo real com MiniLibX.
- Texturas de parede por orientação (`NO`, `SO`, `WE` e `EA`).
- Cores RGB independentes para chão (`F`) e teto (`C`).
- Movimento com `W`, `A`, `S` e `D`, e rotação com as setas esquerda e direita.
- Encerramento limpo com `ESC` ou pelo botão de fechar da janela.
- Validação de mapas e ficheiros de cena `.cub`.
- Bónus disponível com minimapa através de `make bonus`.

## Instruções

### Pré-requisitos

É necessário um compilador C, `make`, a MiniLibX e as dependências da plataforma.

**macOS**

```bash
xcode-select --install
```

**Linux / WSL2**

```bash
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev
```

As bibliotecas MiniLibX e Libft devem estar presentes nas pastas esperadas pelo `Makefile` (`libs/minilibx-linux` no Linux ou `libs/minilibx_macos_metal` no macOS, e `libs/libft`).

### Compilação

```bash
make          # compila a parte obrigatória: ./cub3D
make bonus    # compila a versão com minimapa: ./cub3D_bonus
make clean    # remove os ficheiros objeto
make fclean   # remove objetos e binários
make re       # recompila tudo
make norm     # verifica src/ e includes/ com a Norminette
```

### Execução

```bash
./cub3D maps/test.cub
```

Para a versão bónus:

```bash
./cub3D_bonus maps/test.cub
```

O primeiro argumento tem de ser um ficheiro com extensão `.cub`. O mapa deve ser o último bloco do ficheiro, usar apenas `0`, `1`, `N`, `S`, `E`, `W` e espaços, conter exatamente uma posição inicial e estar completamente fechado por paredes.

### Controlos

| Tecla | Ação |
| --- | --- |
| `W` / `S` | Avançar / recuar |
| `A` / `D` | Mover para a esquerda / direita |
| `←` / `→` | Rodar a câmara |
| `ESC` | Fechar o programa |

### Estrutura do ficheiro `.cub`

Antes do mapa, a cena define quatro texturas e duas cores. Os elementos de configuração podem aparecer em qualquer ordem; cada tipo de elemento deve ser separado por uma ou mais linhas vazias. O mapa tem sempre de ser o último bloco do ficheiro.

```text
NO ./textures/north_red.xpm

SO ./textures/south_blue.xpm

WE ./textures/west_green.xpm

EA ./textures/east_yellow.xpm

F 220,100,0

C 225,30,0

11111
10001
10N01
11111
```

## Recursos

- [Enunciado do cub3D da 42](https://cdn.intra.42.fr/pdf/pdf/177242/en.subject.pdf) - requisitos do projeto e regras do formato `.cub`.
- [MiniLibX para Linux](https://github.com/42Paris/minilibx-linux) - biblioteca gráfica utilizada pelo projeto.
- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html) - referência para os princípios de ray-casting.
- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) - contexto histórico e inspiração do projeto.

### Uso de IA

Nesta documentação, a IA foi usada para analisar o enunciado fornecido, identificar os requisitos obrigatórios do `README.md` e reorganizar este documento. A revisão humana continua necessária para confirmar que os comandos, dependências e funcionalidades documentados correspondem ao estado atual do projeto. Nenhuma alegação sobre a implementação em C deve ser aceite sem leitura, testes e revisão pelos autores.

## Equipa

| Login | Responsabilidade principal |
| --- | --- |
| `rida-cos` | Motor gráfico, ray-casting, MiniLibX e movimento do jogador |
| `jnovais` | Parser, validação e leitura de ficheiros `.cub` |
