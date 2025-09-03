/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claffut <claffut@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:21:07 by ochkaoul          #+#    #+#             */
/*   Updated: 2025/09/03 10:17:22 by claffut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*parsing*/

// 1. Analyse de l'input
//    - Récupération de la ligne de commande brute depuis l'utilisateur
//    - Gestion des cas particuliers
//			- ligne vide
//			- EOF
//			- Caractères spéciaux non valides ou non imprimables
//			- Longueur excessive
//			- Gestion des espaces et tabulations
//			- Gestion des guillemets et échappements


// 2. Tokenisation
//    - Découpage de la ligne en tokens (mots, opérateurs, redirections, pipes)
//    - Utilisation de l'enum t_token_type pour identifier le type de chaque token
//    - Création d'une liste chaînée de t_token


// 3. Analyse syntaxique
//    - Vérification de la validité de la syntaxe (ex : pas de pipe en fin de ligne)
//    - Vérification que chaque redirection est suivie d'un fichier valide
//    - Gestion des erreurs et messages utilisateurs


// 4. Construction de la structure interne
//    - Organisation des tokens en commandes (t_command)
//    - Attribution des arguments, redirections, et liens entre commandes (pour les pipes)
//    - Préparation des structures pour l'exécution ultérieure

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