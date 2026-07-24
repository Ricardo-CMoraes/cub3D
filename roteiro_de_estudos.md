# Roteiro de Estudos: Arquitetura do cub3D

Este roteiro foi montado seguindo o exato caminho de execução do nosso projeto. Estude os blocos na ordem abaixo para entender como um arquivo de texto (`.cub`) se transforma em um mundo 3D interativo!

---

## 1. O Ponto de Partida e Estrutura Geral
**Arquivos chave:** `src/main.c`, `includes/cub3d.h`

Toda a lógica começa e termina no `main.c`. Aqui você vai entender a espinha dorsal do projeto.
- **Estruturas (Structs):** Dê uma olhada no `t_game` dentro de `cub3d.h`. Tudo no jogo (jogador, mapa, texturas, mlx) está concentrado nesta única variável para evitar globais.
- **Fluxo:** O `main` apenas chama as grandes etapas: `parse`, `init_mlx`, `init_player`, `start_game_loop`. Se der erro em qualquer ponto, ele limpa a memória e sai.

## 2. A Fase do Parser (Transformando texto em dados)
**Pasta chave:** `src/parser/`

Antes de renderizar qualquer coisa, precisamos ter certeza de que o mapa é válido. 
- **Leitura do Arquivo (`parse_file.c`):** Como usamos o `get_next_line` para ler o `.cub` linha por linha.
- **Configurações (`parse_textures.c`, `parse_config.c`):** Como extraímos os caminhos das texturas (`NO`, `SO`, etc.) e as cores do chão e teto (`F`, `C`).
- **O Mapa (`parse_map.c`, `validate_map.c`):** A parte mais chata, mas crucial. Como garantimos que o mapa é fechado por paredes (`1`) e que não há espaços vazios "vazando" para fora? (Lembra do `test.cub` que corrigimos?).

## 3. MinilibX e Eventos (A Janela)
**Arquivos chave:** `src/main.c` (setup), `src/player/input.c`

A MinilibX (MLX) não tem um "game loop" complexo por padrão, nós construímos o nosso.
- **Hooks:** Como registramos funções para escutar o teclado (`mlx_hook` para `KeyPress` e `KeyRelease`) e o "X" da janela.
- **Loop Contínuo (`mlx_loop_hook`):** Essa é a mágica. Nós registramos uma função (`render_frame` ou similar) que roda *o tempo todo, sem parar*. É ela quem redesenha a tela a cada milissegundo.

## 4. O Coração do Motor: Raycasting (A Matemática)
**Arquivo chave:** `src/engine/raycasting.c`

Este é o arquivo mais importante do projeto. É aqui que calculamos o 3D. Estude os passos nesta ordem (pesquise sobre o *Lodev Raycasting Tutorial* para acompanhar):
1. **Camera X:** Como mapeamos a tela (pixel 0 a 800) para coordenadas de câmera (-1 a +1).
2. **Ray Direction:** A direção do raio baseada na direção do jogador + plano da câmera.
3. **DDA Setup (`deltaDist` e `sideDist`):** A preparação para "pular" de quadrado em quadrado na grid do mapa de forma extremamente rápida.
4. **O loop DDA (Digital Differential Analysis):** O "tiro" do raio. Ele avança pela grid do mapa até bater no caractere `'1'`.
5. **Cálculo da Distância Perpendicular (`perpWallDist`):** Por que usamos a distância perpendicular em vez da distância real? (Resposta: para evitar o efeito "olho de peixe" / fisheye).

## 5. A Renderização (Pintando a Tela)
**Arquivos chave:** `src/engine/renderer.c`, `src/engine/textures.c`

O raycasting descobriu *a qual distância* está a parede. Agora precisamos desenhá-la.
- **Altura da Linha:** Como transformamos a `perpWallDist` na altura (em pixels) da linha vertical que será desenhada na tela.
- **Pintura Off-Screen (Image Buffer):** Na MLX, desenhar pixel por pixel na janela é muito lento. Estude como escrevemos todos os pixels em uma imagem (array de bytes na memória) e depois colocamos a imagem inteira de uma vez na tela (`mlx_put_image_to_window`).
- **Texturas:** Como descobrimos a coordenada exata (X, Y) do pixel da textura que corresponde ao pixel da tela.

## 6. Movimentação e Rotação
**Arquivos chave:** `src/player/input.c`, `src/player/movement.c`, `src/player/collision.c`

- **Processamento Suave:** Por que guardamos um array de teclas `game->keys` em vez de mover apenas no evento `KeyPress`? (Para permitir mover em diagonal e não sofrer com o delay de repetição do teclado do sistema operacional).
- **Colisão:** Como checamos se `nova_pos_x` ou `nova_pos_y` é uma parede `'1'` antes de aplicar o movimento.
- **Rotação:** Como multiplicar o vetor de direção (`dir_x`, `dir_y`) e o plano da câmera (`plane_x`, `plane_y`) por uma Matriz de Rotação Trigonométrica (`sin`, `cos`) para virar o personagem.

---
> [!TIP]
> **Dica de Estudo:** Quando for focar no passo 4 (Raycasting), use o **tutorial do Lodev** (Lode's Computer Graphics Tutorial - Raycasting). Toda a matemática que escrevemos no código vem diretamente de lá, incluindo os nomes das variáveis.
