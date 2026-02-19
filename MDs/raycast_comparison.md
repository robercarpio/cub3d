# Comparación: `raycast_dda` vs `raycast_single_column`

Este documento analiza las diferencias entre las dos funciones de raycasting presentes en `src/raycast/dda.c` y explica por qué una es viable para el renderizado y la otra no.

## 1. `raycast_dda` (La función "inviable")

Esta función tiene problemas estructurales que impiden su uso directo en el bucle de renderizado principal:

### Problemas Críticos:
1.  **Sobreescritura de Datos**:
    - La función ejecuta un bucle `while` que calcula múltiples rayos.
    - Sin embargo, guarda el resultado de **cada** rayo en la misma estructura compartida (`data->dda`).
    - **Consecuencia**: Al terminar la función, solo tienes la información del *último* rayo calculado. Toda la información de los rayos anteriores (necesaria para dibujar el resto de la pantalla) se pierde antes de poder usarse.

2.  **Límite del Bucle Incorrecto**:
    - Itera desde `0` hasta `data->map->m_width` (el ancho del mapa en casillas, ej. 20).
    - **Consecuencia**: Solo calcularía unos pocos rayos (20) en lugar de los necesarios para llenar la pantalla (ej. 1200 píxeles). La mayor parte de la pantalla quedaría negra.

3.  **Falta de Integración de Dibujado**:
    - No llama a ninguna función de dibujo dentro de su bucle. Simplemente calcula datos y los descarta.

---

## 2. `raycast_single_column` (La opción correcta)

Esta función está diseñada específicamente para trabajar dentro del bucle de renderizado principal de un motor estilo Wolf3D.

### Ventajas y Funcionamiento:
1.  **Unidad de Trabajo Atómica**:
    - Calcula **un solo rayo** para una coordenada `x` específica de la pantalla.
    - Esto permite al bucle principal (`ft_render_frame`) gestionar el flujo de trabajo paso a paso:
        1.  Pedir cálculo del rayo para la columna `x`.
        2.  Usar los datos (*ahora válidos*) para elegir la textura.
        3.  Dibujar la línea vertical (`draw_stripe`).
        4.  Pasar a la siguiente columna.

2.  **Uso Correcto de Recursos**:
    - No desperdicia cálculos. Cada rayo calculado es inmediatamente utilizado para pintar píxeles en pantalla.

---

## Veredicto

**Debes usar `raycast_single_column`.**

Para usar `raycast_dda`, tendrías que reestructurarla completamente para que incluya las llamadas de dibujo dentro de su propio bucle y corregir los límites de iteración, lo cual básicamente la convertiría en una copia de la lógica que ya tienes en `render.c`. Es más limpio y modular mantener el bucle en `render.c` y llamar a `raycast_single_column`.
