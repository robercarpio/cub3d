/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:50:19 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/18 14:50:22 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

// #define COLOR_RESET   "\033[0m"
// #define COLOR_RED     "\033[1;31m"
// #define COLOR_GREEN   "\033[1;32m"
// #define COLOR_YELLOW  "\033[1;33m"
// #define COLOR_BLUE    "\033[1;34m"
// #define COLOR_MAGENTA "\033[1;35m"
// #define COLOR_CYAN    "\033[1;36m"
// #define COLOR_WHITE   "\033[1;37m"

int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img,
				int x,int y)
{
  GC	gc;

  gc = win->gc;
  if (img->gc)
    {
      gc = img->gc;
      XSetClipOrigin(xvar->display, gc, x, y);
    }
  if (img->type==MLX_TYPE_SHM)
    XShmPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
		 img->width,img->height,False);
  if (img->type==MLX_TYPE_XIMAGE)
    XPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
	      img->width,img->height);
  XCopyArea(xvar->display,img->pix,win->window, gc,
	    0,0,img->width,img->height,x,y);
  if (xvar->do_flush)
    XFlush(xvar->display);
}


// int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img,
// 				int x,int y)
// {
//   GC	gc;

//   printf(COLOR_CYAN "[DEBUG mlx_put_image_to_window] START\n" COLOR_RESET);
  
//   printf(COLOR_BLUE "[DEBUG] Checking xvar: %p\n" COLOR_RESET, (void*)xvar);
//   if (!xvar)
//   {
//     printf(COLOR_RED "[ERROR] xvar is NULL!\n" COLOR_RESET);
//     return (-1);
//   }
  
//   printf(COLOR_BLUE "[DEBUG] Checking xvar->display: %p\n" COLOR_RESET, (void*)xvar->display);
//   if (!xvar->display)
//   {
//     printf(COLOR_RED "[ERROR] xvar->display is NULL!\n" COLOR_RESET);
//     return (-1);
//   }
  
//   printf(COLOR_BLUE "[DEBUG] Checking win: %p\n" COLOR_RESET, (void*)win);
//   if (!win)
//   {
//     printf(COLOR_RED "[ERROR] win is NULL!\n" COLOR_RESET);
//     return (-1);
//   }
  
//   printf(COLOR_BLUE "[DEBUG] Checking img: %p\n" COLOR_RESET, (void*)img);
//   if (!img)
//   {
//     printf(COLOR_RED "[ERROR] img is NULL!\n" COLOR_RESET);
//     return (-1);
//   }
  
//   printf(COLOR_BLUE "[DEBUG] win->gc: %p\n" COLOR_RESET, (void*)win->gc);
//   gc = win->gc;
  
//   printf(COLOR_BLUE "[DEBUG] Checking img->gc: %p\n" COLOR_RESET, (void*)img->gc);
//   if (img->gc)
//     {
//       printf(COLOR_YELLOW "[DEBUG] Using img->gc\n" COLOR_RESET);
//       gc = img->gc;
//       printf(COLOR_YELLOW "[DEBUG] Calling XSetClipOrigin with x=%d, y=%d\n" COLOR_RESET, x, y);
//       XSetClipOrigin(xvar->display, gc, x, y);
//     }
  
//   printf(COLOR_MAGENTA "[DEBUG] img->type: %d (MLX_TYPE_SHM=%d, MLX_TYPE_XIMAGE=%d)\n" COLOR_RESET, 
//          img->type, MLX_TYPE_SHM, MLX_TYPE_XIMAGE);
  
//   if (img->type==MLX_TYPE_SHM)
//   {
//     printf(COLOR_YELLOW "[DEBUG] Checking img->pix: %p\n" COLOR_RESET, (void*)img->pix);
//     printf(COLOR_YELLOW "[DEBUG] Checking img->image: %p\n" COLOR_RESET, (void*)img->image);
//     printf(COLOR_YELLOW "[DEBUG] img dimensions: width=%d, height=%d\n" COLOR_RESET, img->width, img->height);
//     printf(COLOR_GREEN "[DEBUG] Calling XShmPutImage...\n" COLOR_RESET);
//     XShmPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
// 		 img->width,img->height,False);
//     printf(COLOR_GREEN "[DEBUG] XShmPutImage completed\n" COLOR_RESET);
//   }
  
//   if (img->type==MLX_TYPE_XIMAGE)
//   {
//     printf(COLOR_YELLOW "[DEBUG] Checking img->pix: %p\n" COLOR_RESET, (void*)img->pix);
//     printf(COLOR_YELLOW "[DEBUG] Checking img->image: %p\n" COLOR_RESET, (void*)img->image);
//     printf(COLOR_YELLOW "[DEBUG] img dimensions: width=%d, height=%d\n" COLOR_RESET, img->width, img->height);
//     printf(COLOR_GREEN "[DEBUG] Calling XPutImage...\n" COLOR_RESET);
//     XPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
// 	      img->width,img->height);
//     printf(COLOR_GREEN "[DEBUG] XPutImage completed\n" COLOR_RESET);
//   }
  
//   printf(COLOR_BLUE "[DEBUG] Checking win->window: %p\n" COLOR_RESET, (void*)win->window);
//   printf(COLOR_GREEN "[DEBUG] Calling XCopyArea with x=%d, y=%d, width=%d, height=%d\n" COLOR_RESET,
//          x, y, img->width, img->height);
//   XCopyArea(xvar->display,img->pix,win->window, gc,
// 	    0,0,img->width,img->height,x,y);
//   printf(COLOR_GREEN "[DEBUG] XCopyArea completed\n" COLOR_RESET);
  
//   printf(COLOR_BLUE "[DEBUG] xvar->do_flush: %d\n" COLOR_RESET, xvar->do_flush);
//   if (xvar->do_flush)
//   {
//     printf(COLOR_GREEN "[DEBUG] Calling XFlush...\n" COLOR_RESET);
//     XFlush(xvar->display);
//     printf(COLOR_GREEN "[DEBUG] XFlush completed\n" COLOR_RESET);
//   }
  
//   printf(COLOR_CYAN "[DEBUG mlx_put_image_to_window] END\n" COLOR_RESET);
//   return (0);
// }
