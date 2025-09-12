/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:14:23 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/12 16:10:39 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			skip_space_and_tabs(char *line, int x)
{
	while (line[x] == 32 || line[x] == 9)
		x++;

	return(x);
}

int			handles_special_char(char *line, int x, t_token **list)
{
	t_token	*new;
	char	*cmd;
	int		y;

	y = x;

	/*saves the pipe*/
	if (line[x] == 124)
		cmd = ft_strdup_m(line, x, 1);

	/*saves arrows*/
	else if (line[x] == 60 || line[x] == 62)
	{
		if (line[x + 1] == line[x])
		{
			cmd = ft_strdup_m(line, x, 2);
			y++;
		}
		else
			cmd = ft_strdup_m(line, x, 1);
	}

	/*creats the 1st list element*/
	new = ft_lstnew_token(cmd);
	if (!*list)
		*list = new;

	/*creats others list element*/
	else
		ft_lstadd_back(list, new);

	return (y + 1);
}

int			handles_command(char *line, int x, t_token **list, t_SHELL **all)
{
	t_token	*new;
	char    *tmp;
	char	*cmd;
	char	quote;
	int		y;


	y = x;
	cmd = ft_strdup("");
	while(line[x])
	{
		/*condition de fin*/

		if (line[x] == 32 || line[x] == 9 || line[x] == 124 || line[x] == 60 || line[x] == 62)
			break;

		/*attrape entre guillemet*/
		else if (line[x] == 39 || line [x] == 34)
		{
			quote = line[y];
			y++;
			while (line[y] && line[y] != quote)
				y++;

			if (line[y] == '\0')
			{
				write(2, "syntax error: unclosed quote\n", 29);
				(*all)->last_status = 258;
				return NULL;
			}

			else if (line[y] == quote)
				y++;

			/*saves the cmd*/
			tmp = ft_strdup_m(line, x + 1, y - x - 2);
			tmp = expansion((*all)->env, (*all)->last_status, tmp, quote); //removes the quotes too
			cmd = ft_strjoin(cmd, tmp);
			x = y;
			free(tmp);
		}

		/*attrape en dehors des guillemet*/
		else
		{
			while (line[y] && line[y] != 34 && line[y] != 39 && line[y] != 32 && line[y] != 9
			&& line[y] != 60 && line[y] != 62 && line[y] != 124)
				y++;

			tmp = ft_strdup_m(line, x, y - x);
			tmp = expansion((*all)->env, (*all)->last_status, tmp, quote);
			cmd = ft_strjoin(cmd, tmp);
			x = y;
			free(tmp);
		}

	}

		//step 2: send the cmd in the the chained list with no quotes

		/*creats the 1st list element*/
		new = ft_lstnew_token(cmd);
		if (!*list)
			*list = new;

		/*creats others list element*/
		else
			ft_lstadd_back(list, new);

		return (y);
}


void		tokenisation(char *line, t_token **list, t_SHELL **all)
// cat -n < in.txt | grep "hello   hello" > out.txt
{
	int 	x = 0;

	while(line[x])
	{
		x = skip_space_and_tabs(line, x);

		if (line[x] == '|' || line[x] == '<' || line[x] == '>')
			x= handles_special_char(line, x, list);

		else
			x = handles_command(line, x, list, all);
	}
	free(line);
}




/*Here’s a compact summary you can keep as notes for your minishell expansion:

---

### ✅ Your expansion is already correct for:

* `'...'` → no expansion.
* `"..."` → expansion happens.
* Outside quotes → expansion happens.
* `$?` → replaced with last status.
* `$VAR` → replaced with env value if found.

---

### ⚠️ Missing vs Bash:

1. **Undefined var** → Bash returns `""`, you keep `$VAR`.
2. **Concatenation**: `$HOMEfoo` should stay literal, not try to expand `HOMEfoo`.
3. **Splicing**: `hello$USERworld` should expand into `helloOmarworld`.
4. **Empty vars**: must expand to empty string, not disappear.
5. (Bonus) Word splitting & globbing not handled — not mandatory at 42.

---

### ⚠️ Bugs in your current code:

* In *outside quotes branch*, you pass `quote` uninitialized → UB.
  ➝ Pass `0` instead.

---

### ✅ Minimum fixes for 42:

* Return `""` if var not found.
* Always initialize `quote` (0 when not quoted).
* Parse var name correctly (alnum + `_`), stop at first invalid char.

---

Would you like me to also give you a **regex-like rule** for valid variable names in Bash (so you can implement the parsing correctly)?
*/
