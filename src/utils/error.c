#include "cub3d.h"

/*
** ft_error — write error message to stderr.
*/
void	ft_error(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
}
