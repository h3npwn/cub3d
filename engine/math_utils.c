#include "../headers/cub3d.h"
#include <math.h>

double	normalize_angle(double angle)
{
	const double	two_pi = 2.0 * M_PI;

	while (angle < 0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}
