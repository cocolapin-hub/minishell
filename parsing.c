/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochkaoul <ochkaoul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:18:14 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/03 10:58:53 by ochkaoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*parsing*/

/* PARSING MINISHELL */

// 1. Analyse de l'input
//    - Récupération de la ligne de commande brute depuis l'utilisateur (readline)
//    - Gestion des cas particuliers :
//         - ligne vide → ignorer et afficher prompt suivant
//         - EOF (Ctrl-D) → quitter le shell
//         - caractères spéciaux non valides ou non imprimables
//         - longueur excessive
//         - gestion des espaces et tabulations
//         - gestion des guillemets et échappements

// 2. Tokenisation
//    - Découpage de la ligne en tokens (mots, opérateurs, redirections, pipes)
//    - Remplissage de la liste chaînée t_token
//        - type : WORD, PIPE, REDIR_IN, REDIR_OUT, REDIR_APPEND, REDIR_HEREDOC
//        - quote : Q_NONE, Q_SINGLE, Q_DOUBLE
//        - value : texte exact du token (avec quotes si présentes)
//    - Chaque token garde l’information sur les quotes pour l’étape suivante

// 3. Expansion et quote removal sur t_token
//    - Parcourir chaque token de type WORD
//    - Si quote != Q_SINGLE : remplacer les variables d’environnement ($VAR, $?) par leur valeur
//    - Supprimer les quotes entourant le token pour obtenir la valeur finale utilisable par execve

// 4. Analyse syntaxique
//    - Vérification de la validité de la syntaxe :
//         - pas de pipe au début ou à la fin
//         - pas de double pipe consécutif
//         - chaque redirection est suivie d’un token WORD valide
//    - Gestion des erreurs et affichage des messages utilisateurs

// 5. Construction de la structure interne
//    - Organisation des tokens en commandes (t_command)
//    - Pour chaque commande :
//         - args : tableau des mots de la commande (argv)
//         - redir : liste chaînée des redirections (<, >, >>, <<)
//         - next : commande suivante si pipe
//    - Préparation des structures pour l’exécution ultérieure


// // avec "" ls -l -a " le parsing aura produit :
	cmd = "ls"
	args = {"ls", "-l", "-a", NULL} // le tableau doit etre termin par NULL et argv[0] = cmd
	find_in_path("ls", envp) doit renvoyer : /bin/ls
		// Pour ça, il faut :
			Trouver la ligne PATH=... dans envp.
			Découper la valeur (/usr/local/bin:/usr/bin:/bin:...) avec ft_split (":").
			Pour chaque dossier, construire dir + "/" + cmd (/bin/ls, /usr/bin/ls, …).
			Vérifier avec access(path, X_OK) si le fichier existe et est exécutable.
			Retourner le premier trouvé.