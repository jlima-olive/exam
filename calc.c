#include "calc.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

node *new_node(node n)
{
	node *ret;

	ret = malloc(sizeof(node));
	if (ret == NULL)
		return (NULL);
	*ret = n;
	return (ret);
}

void unexpected(char c)
{
	if (c)
		printf("Detected invalid %c token\n", c);
	else
		printf("Detected unexpected end of input\n");
}

int	inside_parentesis(char *str)
{
	int level = 0;
	int	ind = 0; 

	if (*str == '(')
	{
		while (str[ind])
		{
			if (str[ind] == '(')
				level++;
			if (str[ind] == ')')
				level--;
			if (level == 0 && str[ind + 1])
				return (0);
			ind++;
		}
	}
	else
		return (0);
	str[ind - 1] = '\0';	
	return (1);
}

node *parse_tree(char *str)
{
	node n;

	if (*str == '\0')
		return (unexpected(*str), NULL);
	while (inside_parentesis(str))
		str++;
	if (*(str + 1) == '\0')
	{
		n.val = *str - 48;
		n.type = VAL;
		n.l = NULL;
		n.r = NULL;
		return (new_node(n));
	}
	int ind = strlen(str);
	int temp = ind;
	int level = 0;
	while (--ind >= 0)
	{
		if (str[ind] == '(')
			level--;
		if (str[ind] == ')')
			level++;
		if (level == 0 && str[ind] == '+')
		{
			str[ind] = '\0';
			if ((n.l = parse_tree(str)) == NULL)
				return (NULL);
			if ((n.r = parse_tree(str + ind + 1)) == NULL)
			{
				free(n.l);
				return (NULL);
			}
			n.type = ADD;
			return (new_node(n));
		}
	}
	level = 0;
	ind = temp;
	while (--ind >= 0)
	{
		if (str[ind] == '(')
			level--;
		if (str[ind] == ')')
			level++;
		if (level == 0 && str[ind] == '*')
		{
			str[ind] = '\0';
			if ((n.l = parse_tree(str)) == NULL)
				return (NULL);
			if ((n.r = parse_tree(str + ind + 1)) == NULL)
			{
				free(n.l);
				return (NULL);
			}
			n.type = MULTI;
			return (new_node(n));
		}
	}
	return (NULL);
}

int	parse_str(char *str)
{
	int ind = 0;
	int	count;

	count = 0;
	while (str[ind])
	{
		if (str[ind] != '(' && str[ind] != ')' && !(str[ind] >= '0' && str[ind] <= '9') && str[ind] != '*' && str[ind] != '+')
			return (unexpected(str[ind]), INT_MAX);
		if (str[ind] == '(')
		{
			count++;
			if (str[ind + 1] == ')' || str[ind + 1] == '+' || str[ind + 1] == '*')
				return (unexpected(str[ind + 1]), INT_MAX);
		}
		if (str[ind] == ')')
		{
			count--;
			if (str[ind + 1] == '(' || ((str[ind + 1] >= '0' && str[ind + 1] <= '9')))
				return (unexpected(str[ind + 1]), INT_MAX);
		}
		if (str[ind] >= '0' && str[ind] <= '9')
			if (str[ind + 1] == '(' || (str[ind + 1] >= '0' && str[ind + 1] <= '9'))
				return (unexpected(str[ind + 1]), INT_MAX);
		if (str[ind] == '*' || str[ind] == '+')
			if (str[ind + 1] == ')' || str[ind + 1] == '*' || str[ind + 1] == '+')
				return (unexpected(str[ind + 1]), INT_MAX);
		ind++;
	}
	return (count);
}

int calc_tree(node *tree)
{
	if (tree == NULL)
		return (0);
	switch (tree->type)
	{
	case VAL:
		return tree->val;
		break;
	case ADD: 
		return calc_tree(tree->l) + calc_tree(tree->r);
		break;
	case MULTI:
		return calc_tree(tree->l) * calc_tree(tree->r);
		break;
	}
}

void free_tree(node *tree)
{
	if (tree == NULL)
		return ;
	free_tree(tree->l);
	free_tree(tree->r);
	free(tree);
}

int main(int argc, char **argv)
{
	node	*n;
	int		count;

	if (argc != 2)
		return (1);
	count = parse_str(argv[1]);
	if (count)
	{
		if (count < 0 && count != INT_MAX)
			unexpected(')');
		if (count > 0 && count != INT_MAX)
			unexpected('(');
		return (1);
	}
	n = parse_tree(argv[1]);


	printf("the calculation value is %d\n", calc_tree(n));
	free_tree(n);
}
