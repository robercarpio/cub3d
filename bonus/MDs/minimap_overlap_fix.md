# Problema: Paredes sobre el Minimapa

## La Causa: Orden de Dibujado (Z-Order)

En gráficos por computadora, el orden en que dibujas las cosas es crucial. Lo que dibujas al final se pinta "encima" de lo que dibujaste primero.

### Tu código actual en `src/render/render.c`:

```c
int ft_render_frame(t_data *data)
{
    // ...
    draw_floor_ceiling(data);     // 1. Fondo
    draw_minimap(data);           // 2. Minimapa (¡Aquí está el problema!)
    draw_minimap_border(data);    // 3. Borde
    draw_minimap_player(data);    // 4. Jugador en minimapa
    // ...
    while (x < data->width)
    {
        raycast_single_column(data, x);
        // ...
        draw_stripe(data, x, &data->dda, tex); // 5. Paredes 3D
        x++;
    }
    // ...
}
```

**Lo que está pasando:**
1.  Pintas el minimapa.
2.  Luego, pintas las paredes 3D.
3.  **Resultado**: Las paredes se dibujan *encima* del minimapa, tapándolo cuando te acercas.

## La Solución: Invertir el Orden

El minimapa es un elemento de la interfaz de usuario (HUD). El HUD siempre debe dibujarse al **final**, después de todo el renderizado 3D, para que flote "sobre" la acción.

### Código Corregido:

```c
int ft_render_frame(t_data *data)
{
    // ...
    // 1. Primero el fondo y las paredes 3D
    draw_floor_ceiling(data);
    
    x = 0;
    while (x < data->width)
    {
        raycast_single_column(data, x);
        tex = choose_texture(data, &data->dda);
        draw_stripe(data, x, &data->dda, tex);
        x++;
    }

    // 2. AL FINAL, pintamos el minimapa (HUD)
    draw_minimap(data);
    draw_minimap_border(data);
    draw_minimap_player(data);
    draw_ray(data); // Si quieres ver los rayos en el minimapa
    
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return (0);
}
```

Al mover las llamadas de `draw_minimap` al final de la función, garantizas que siempre se pinten sobre las paredes, sin importar lo cerca que estés de ellas.
