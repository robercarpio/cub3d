# Full-Map Overlay con Tab

## Objetivo

Al pulsar **Tab**, se muestra el mapa completo centrado en pantalla (sin tapar toda la vista) con un efecto de oscurecimiento del fondo. El movimiento del jugador sigue funcionando mientras el mapa está visible.

---

## Archivos modificados

### 1. `inc/structs.h`

**Define `TAB_KEY`** (keycode X11 = 65289):

```c
# define TAB_KEY 65289
```

**Campo `show_bigmap` en `t_data`** — flag que controla si el mapa grande está visible:

```c
// AÑADIDO en t_data
int     show_bigmap;
```

`ft_bzero` en `ft_alloc_data` lo inicializa a `0` automáticamente.

---

### 2. `inc/cub.h`

Prototipo de la nueva función:

```c
void    draw_bigmap(t_data *data);
```

---

### 3. `src/inputs/inputs.c`

Toggle de `show_bigmap` en `key_press()`. El movimiento nunca se bloquea porque `game_loop` lee las teclas de movimiento **antes** de llamar al render:

```c
// AÑADIDO en key_press()
if (key == TAB_KEY)
    data->show_bigmap = !data->show_bigmap;
```

---

### 4. `src/movement/minimap.c`

Se añadieron dos nuevas funciones al final del fichero:

#### `bigmap_draw_overlay(t_data *data)` *(static)*

Oscurece todos los píxeles ya renderizados a la mitad de su brillo haciendo un bit-shift a la derecha sobre el buffer directamente:

```c
*px = (*px >> 1 & 0x7F7F7F);
```

Así la vista 3D sigue siendo visible pero oscurecida, dando un efecto de overlay semitransparente sin necesidad de alpha blending real.

#### `draw_bigmap(t_data *data)`

- Calcula el tamaño de cada tile para que todo el mapa quepa en el **70% del alto** de pantalla.
- Centra el mapa con `off_x` y `off_y`.
- Dibuja cada celda: `'1'` → gris claro, `'D'` → naranja, pasillo → gris oscuro.
- Dibuja el jugador como un cuadrado rojo de 8×8 px en su posición real.

---

### 5. `src/render/render.c`

Al final de `ft_render_frame()`, tras la minimap habitual, se llama a `draw_bigmap` condicionalmente:

```c
// AÑADIDO al final, antes de mlx_put_image_to_window
if (data->show_bigmap)
    draw_bigmap(data);
```

---

## Flujo de la tecla Tab

```
Tecla Tab pulsada
       │
       ▼
key_press()  →  show_bigmap = !show_bigmap
       │
       ▼
game_loop()  →  movimiento procesado normalmente (WASD/flechas)
       │
       ▼
ft_render_frame()
   ├─ draw_floor_ceiling()
   ├─ raycast + draw_stripe() (columnas)
   ├─ draw_minimap() / border / player
   └─ (si show_bigmap) draw_bigmap()
           ├─ bigmap_draw_overlay()  ← oscurece el frame
           ├─ bucle tiles del mapa
           └─ punto rojo del jugador
```

---

## Colores del mapa grande

| Celda | Color |
|-------|-------|
| `'1'` (muro) | Gris claro `0xDDDDDD` |
| `'D'` (puerta) | Naranja `0xFF8800` |
| `'0'` / pasillo | Gris oscuro `0x222222` |
| Jugador | Rojo `0xFF2222` |

---

## Verificación

```bash
make re
./cub3D maps/map.cub
# Pulsa Tab para abrir/cerrar el mapa grande
# Muévete con WASD mientras el mapa está abierto
```
