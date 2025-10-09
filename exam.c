#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

void	print_comb(char **av, int *comb, int ammout)
{
	int constructor;

	constructor = -1;;
	while (++constructor < ammout)
	{
		printf("%s", av[comb[constructor]]);
		if (constructor < ammout - 1)
			printf(" ");
	}
	printf("\n");
}

void	incriment(int *comb, int ammount, int max)
{
	comb[ammount]++;
	if (ammount == 0)
		return ;
	if (comb[ammount] > max)
	{
		incriment(comb, ammount - 1, max - 1);
		comb[ammount] = comb[ammount - 1] + 1;
	}
}

int	check_values(int result, int *comb, int ammount, char **av)
{
	int constructor;
	int total;

	total = 0;
	constructor = -1;;
	while (++constructor < ammount)
		total += atoi(av[comb[constructor]]);
	return (total == result);
}

int	get_comb(int result, char **av, int ammout, int max)
{
	int	*comb;
	int	constructor;

	comb = malloc(ammout * sizeof(int));
	constructor = 0;
	while (++constructor <= ammout)
		comb[constructor - 1] = constructor + 1;
	while (comb[ammout - 1] <= max)
	{
		if (check_values(result, comb, ammout, av))
			print_comb(av, comb, ammout);
		incriment(comb, ammout - 1, max);
	}
	free(comb);
}

int	main(int ac, char **av)
{
	int ind;

	if (ac < 3)
		return (1);
	ind = 0;
	while (++ind <= ac - 2)
		get_comb(atoi(*(av + 1)), av, ind, ac - 1);
}
