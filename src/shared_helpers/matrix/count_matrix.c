#include "../../../includes/minishell.h"

int count_matrix(char **arr)
{
	int count;

	count = 0;
	if(!arr || !*arr)
		return (0);
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}