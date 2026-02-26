# Ocultar el cursor en Cub3D

Para mejorar la inmersión en el juego, se ha implementado una funcionalidad que oculta el cursor del ratón cuando la ventana del juego está activa.

## Pasos realizados

### 1. Identificación de la función MLX
Se utilizó la función `mlx_mouse_hide` proporcionada por la librería MiniLibX. Esta función toma como parámetros la instancia de MLX (`data->mlx`) y el puntero a la ventana (`data->win`).

### 2. Modificación del código
La modificación se realizó en el archivo `src/play.c`, específicamente dentro de la función `start_window`.

**Antes:**
```c
mlx_mouse_move(data->mlx, data->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
mlx_loop(data->mlx);
```

**Después:**
```c
mlx_mouse_hide(data->mlx, data->win);
mlx_loop(data->mlx);
```

### 3. Justificación
Se decidió colocar `mlx_mouse_hide` justo antes de iniciar el bucle principal del juego (`mlx_loop`) para asegurar que el cursor se oculte en cuanto se cree y se muestre la ventana del juego.

## Verificación
Para verificar el cambio, sigue estos pasos:
1. Compila el proyecto: `make`
2. Ejecuta el juego: `./cub3d [nombre_del_mapa].cub`
3. Observa que el cursor ya no es visible sobre la ventana del juego.
