/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerconstruct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:20:59 by abahja            #+#    #+#             */
/*   Updated: 2025/12/23 21:49:58 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void player_inits(t_cub *cub)
{
	
	t_player	*player;

	player = &cub->cfg->player;
    
    player->pos[X] += 0.5;
    player->pos[Y] += 0.5;
    player->width = 5;
    player->height = 5;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = M_PI / 2;
    player->walkSpeed = 100;
    player->turnSpeed = 45 * (M_PI / 180);
}