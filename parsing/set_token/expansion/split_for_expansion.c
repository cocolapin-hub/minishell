#include "../../../minishell.h"

char 	*split_for_expansion(char *str, char *key, int start, char *key_value)
{
    char *split1 = NULL;
    char *split2 = NULL;
    char *split3 = NULL;
    char *tmp;
    char *result;
    size_t key_len;
    size_t str_len;

    if (key[0] == '$')
		key_len = strlen(key);
	else
		key_len = strlen(key) + 1;  // +1 pour le $

    str_len = strlen(str);

    if (start == 0)
        split1 = ft_strdup("");
    else
        split1 = ft_strdup_m(str, 0, start);

    split2 = ft_strdup(key_value);

    if (start + key_len < str_len)
        split3 = ft_strdup_m(str, start + key_len, str_len - (start + key_len));
    else
        split3 = ft_strdup("");

    tmp = ft_strjoin(split1, split2);
    result = ft_strjoin(tmp, split3);


    // free(split1);
    // free(split2);
    // free(split3);
    // free(tmp);
    // free(str);
    return (result);
}
