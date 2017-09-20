#include "../include/lem-in.h"
#include "../libft/includes/libft.h"

int	main(int argc, char ** argv)
{
	t_struct	s;

	init_struct(&s);
	if (!pars_args(argc, argv, &s))
	{
		ft_printf("ERROR\n");
		return(1);
	}
	ft_printf("OK\n");
	return (0);
}
