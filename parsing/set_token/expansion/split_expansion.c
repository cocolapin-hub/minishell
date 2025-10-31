
#include "../../../minishell.h"

static char	**make_splits(char *str, char *key, int start, char *key_value)
{
	size_t	key_len;
	size_t	str_len;
	char	**splits;

	splits = malloc(sizeof(char *) * 3);
	if (!splits)
		return (NULL);
	if (key[0] == '$')
		key_len = strlen(key);
	else
		key_len = strlen(key) + 1;
	str_len = strlen(str);
	if (start == 0)
		splits[0] = ft_strdup("");
	else
		splits[0] = ft_strdup_m(str, 0, start);
	splits[1] = ft_strdup(key_value);
	if (start + key_len < str_len)
		splits[2] = ft_strdup_m(str, start + key_len, str_len - (start + key_len));
	else
		splits[2] = ft_strdup("");
	return (splits);
}

char	*split_expansion(char *str, char *key, int start, char *key_value)
{
	char	**splits;
	char	*tmp;
	char	*result;

	splits = make_splits(str, key, start, key_value);
	if (!splits)
		return (NULL);
	tmp = ft_strjoin(splits[0], splits[1]);
	result = ft_strjoin(tmp, splits[2]);
	free(splits[0]);
	free(splits[1]);
	free(splits[2]);
	free(tmp);
	// free(str);
	free(splits);
	return (result);
}
