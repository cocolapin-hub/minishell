//PARSING:

	/* ____PRINT CHECK____*/
	// while(list)
	// {
	// 	printf("type: %d\ncmd: %s\n\n", list->type,  list->value);
	// 	list = list->next;
	// }

	/*_____PRINT CMD_____*/
	// t_command *cmd_ptr = cmd;

	// while (cmd_ptr)
	// {
	// 	if (cmd_ptr->args)
	// 	{
	// 		for (int i = 0; cmd_ptr->args[i]; i++)
	// 			printf("arg[%d] = \"%s\"\n", i, cmd_ptr->args[i]);
	// 	}
	// 	else
	// 		printf("args = NULL\n");

	// 	t_token *tok = cmd_ptr->elements;
	// 	if (!tok)
	// 		printf("elements = NULL\n");
	// 	while (tok)
	// 	{
	// 		if (!tok->value)
	// 			printf("!! NULL value at tok %p !!\n", (void*)tok);
	// 		else
	// 			printf("[%s:%d] ", tok->value, tok->type);

	// 		tok = tok->next;
	// 	}
	// 	printf("\n---\n");

	// 	cmd_ptr = cmd_ptr->next;
	// }