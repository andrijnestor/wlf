/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:37:24 by anestor           #+#    #+#             */
/*   Updated: 2018/03/06 13:16:55 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ray_casting(t_wolf *data)
{
    for(int y = 0; y < WIN_W; y++)
    {
      //calculate ray position and direction
   //   double cameraX = 2 * y / (double)WIN_W - 1; //x-coordinate in camera space
      data->cast.ray.x = PDIR_X + PLANE_X * (2 * y / (double)WIN_W - 1);
      data->cast.ray.y = PDIR_Y + PLANE_Y * (2 * y / (double)WIN_W - 1);
      //which box of the map we're in
      MPX = (int)POX;
      MPY = (int)POY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = ABS(1 / data->cast.ray.x);
      double deltaDistY = ABS(1 / data->cast.ray.y);
	  

      //what direction to step in x or y-direction (either +1 or -1)
     // int stepX;
     // int stepY;

     // int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
	  
	if (data->cast.ray.x < 0)
      {
        data->cast.step.x = -1;
        sideDistX = (POX - MPX) * deltaDistX;
      }
      else
      {
        data->cast.step.x = 1;
        sideDistX = (MPX + 1.0 - POX) * deltaDistX;
      }
      if (data->cast.ray.y < 0)
      {
        data->cast.step.y = -1;
        sideDistY = (POY - MPY) * deltaDistY;
      }
      else
      {
        data->cast.step.y = 1;
        sideDistY = (MPY + 1.0 - POY) * deltaDistY;
      }
      while (1)
      {
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          MPX += data->cast.step.x;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          MPY += data->cast.step.y;
          side = 1;
        }
        if (data->map.arr[MPX][MPY] > 0)
			break ;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      double perpWallDist;
	  if (side == 0)
		  perpWallDist = (MPX - POX + (1 - data->cast.step.x) / 2) / data->cast.ray.x;
      else
		  perpWallDist = (MPY - POY + (1 - data->cast.step.y) / 2) / data->cast.ray.y;

	  data->slice[y].start = -(int)(WIN_H / perpWallDist) / 2 + WIN_H / 2; // if <0
	  data->slice[y].end = (int)(WIN_H / perpWallDist) / 2 + WIN_H / 2; // if > WIN_W
	  data->slice[y].col = data->map.col[data->map.arr[MPX][MPY] - 1];
      //give x and y sides different brightness
	  if (side == 1)
		  data->slice[y].col = data->slice[y].col / 2;
	}
}
