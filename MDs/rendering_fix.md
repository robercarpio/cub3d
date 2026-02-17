# Documentación del Arreglo de Renderizado en Cub3D

## El Problema: Plano de Cámara Paralelo

El problema original era que el **plano de la cámara** (`plane`) se inicializó paralelo al **vector de dirección** del jugador (`dir`).

En el algoritmo de Raycasting (wolf3d), el plano de la cámara debe ser **perpendicular** a la dirección para crear un campo de visión (FOV) 2D. 

### Estado Anterior (Erróneo)
El jugador miraba al **Norte** (`dir_y = -1`), pero el plano también apuntaba al **Norte** (`plane_y = 0.66`).

| Vector | X | Y | Descripción |
| :--- | :--- | :--- | :--- |
| **Dirección** | `0.0` | `-1.0` | Mirando hacia arriba (Norte) |
| **Plano (Antes)** | `0.0` | `0.66` | **Paralelo** a la dirección (Mal) |

Esto causaba que el cálculo de `rayDirX` (la dispersión horizontal de los rayos) fuera siempre 0:
```c
rayDirX = dir_x + plane_x * cameraX
rayDirX = 0 + 0 * cameraX = 0
```
Como resultado, todos los rayos se lanzaban en una línea recta vertical, sin ancho horizontal, creando las "rayas" visuales.

---

## La Solución: Plano de Cámara Perpendicular

Para arreglarlo, rotamos el vector del plano 90 grados para que sea perpendicular a la dirección. Si miramos al Norte (Y), el plano debe extenderse Este-Oeste (X).

### Estado Actual (Corregido)

| Vector | X | Y | Descripción |
| :--- | :--- | :--- | :--- |
| **Dirección** | `0.0` | `-1.0` | Mirando hacia arriba (Norte) |
| **Plano (Ahora)** | `0.66` | `0.0` | **Perpendicular** a la dirección (Bien) |

Ahora el cálculo es correcto:
```c
rayDirX = dir_x + plane_x * cameraX
rayDirX = 0 + 0.66 * cameraX = (valor variable)
```
Esto permite que los rayos se abran en abanico, creando la perspectiva 3D correcta.

## Código Modificado
Archivo: `src/movement/player.c`

```diff
- data->player.plane_x = 0.0;
- data->player.plane_y = 0.66;
+ data->player.plane_x = 0.66;
+ data->player.plane_y = 0.0;
```
