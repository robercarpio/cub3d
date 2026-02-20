# Door Rendering — `door_close.xpm`

## Objetivo

Hacer que el motor de raycasting renderice la textura `img/door_close.xpm` cuando un rayo golpea una celda marcada con `'D'` en el mapa.

---

## Archivos modificados

### 1. `inc/structs.h`

**Cambio 1 — Enum `e_tex_id`**

Se añadió `TEX_DOOR` antes de `TEX_COUNT` para reservar un slot de textura para la puerta:

```c
// ANTES
typedef enum e_tex_id
{
    TEX_NORTH = 0,
    TEX_SOUTH,
    TEX_WEST,
    TEX_EAST,
    TEX_COUNT
} t_tex_id;

// DESPUÉS
typedef enum e_tex_id
{
    TEX_NORTH = 0,
    TEX_SOUTH,
    TEX_WEST,
    TEX_EAST,
    TEX_DOOR,   // <-- nuevo
    TEX_COUNT
} t_tex_id;
```

> `TEX_COUNT` sigue siendo el centinela; ahora vale 5 en lugar de 4.  
> El array `textures.paths[]` e `textures.images[]` en `t_texture` se dimensiona automáticamente con `TEX_COUNT`, por lo que no requieren cambio adicional.

**Cambio 2 — Struct `t_dda_data`**

Se añadió el campo `hit_type` para registrar qué carácter de mapa golpeó el rayo:

```c
// AÑADIDO al final de t_dda_data
char    hit_type;  // '1' = muro normal, 'D' = puerta, etc.
```

---

### 2. `src/raycast/dda.c`

Después del bucle DDA en `raycast_single_column`, se guarda el carácter de la celda golpeada:

```c
// AÑADIDO justo tras el while (hit == 0) { ... }
data->dda.hit_type = data->map->map[data->dda.mapY][data->dda.mapX];
```

Esto hace que `choose_texture()` en el render tenga toda la información necesaria sin tocar la lógica de distancias.

---

### 3. `src/process_map/textures.c`

En `init_textures()`, se asigna hardcoded la ruta de la textura de puerta antes de llamar a `load_textures()`, dado que **no se especifica en el fichero `.cub`**:

```c
// AÑADIDO tras parse_textures(file, data);
data->textures.paths[TEX_DOOR] = "img/door_close.xpm";
```

`load_textures()` ya itera `while (i < TEX_COUNT)`, por lo que cargará el nuevo slot `TEX_DOOR` automáticamente junto con las cuatro texturas de pared.

---

### 4. `src/render/render.c`

En `choose_texture()`, se añadió la comprobación de puerta **antes** de la lógica N/S/E/W:

```c
// AÑADIDO al inicio de choose_texture()
if (ray->hit_type == 'D')
    return (&data->textures.images[TEX_DOOR]);
```

Así, independientemente del lado (`side`) o dirección del rayo, una puerta siempre muestra `door_close.xpm`.

---

### 5. `src/parse/checker_chars.c`

Se añadió `'D'` a los caracteres válidos del mapa para que el parser no rechace ficheros `.cub` con puertas:

```c
// ANTES
if (!only_chars_allow(map[i], "01NSEW "))

// DESPUÉS
if (!only_chars_allow(map[i], "01NSEW D"))
```

---

### 6. `maps/map.cub`

Se sustituyó un `'1'` de muro por `'D'` para crear una puerta visible desde la posición inicial del jugador:

```
// ANTES (línea 13)
100000100001000001000010000001

// DESPUÉS
100000D00001000001000010000001
```

---

## Flujo completo

```
map.cub contiene 'D'
        │
        ▼
checker_chars.c   →  acepta 'D' como char válido
        │
        ▼
raycast_single_column()  →  DDA loop: 'D' > '0', hit = 1
        │
        ▼
dda.hit_type = 'D'        (guardado tras el loop)
        │
        ▼
choose_texture()  →  hit_type == 'D'  →  devuelve TEX_DOOR
        │
        ▼
draw_stripe()     →  renderiza door_close.xpm en pantalla
```

---

## Verificación

```bash
make re
./cub3D maps/map.cub
```

Al ejecutar el juego y mirar hacia la celda `D` del mapa, se renderiza la textura `door_close.xpm` en lugar de las texturas de pared normales.
