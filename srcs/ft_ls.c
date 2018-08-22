/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 23:28:42 by toliver           #+#    #+#             */
/*   Updated: 2018/08/22 22:25:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_test(t_param env)
{
	t_file	*tmp;

//	ft_printf("flags = %b\n", env.flags);

	/*
	tmp = env.filelist;
	ft_printf("printing FILES :\n");
	while (tmp)
	{
		ft_printf("name = %s\n", tmp->name);
		freenode(tmp);
		tmp = tmp->next;
	}
	*/
	tmp = env.list;
	ft_printf("printing DIRECTORIES :\n");
	while (tmp)
	{
		ft_printf("name = %s\n", tmp->name);
		/*
		ft_printf("id du peripherique contenant le fichier : %d\n", tmp->stat.st_dev);
		ft_printf("numero inode %llu\n", tmp->stat.st_ino);
		ft_printf("protection %d\n", tmp->stat.st_mode);
		ft_printf("nb liens materiels %d\n", tmp->stat.st_nlink);
		ft_printf("UID proprietaire %d\n", tmp->stat.st_uid);
		ft_printf("GID proprietaire %d\n", tmp->stat.st_gid);
		ft_printf("ID peripherique %d\n", tmp->stat.st_rdev);
		ft_printf("Taille totale en octet %lld\n", tmp->stat.st_size);
		ft_printf("Taille de bloc pour E/S %d\n", tmp->stat.st_blksize);
		ft_printf("Nombre de blocs alloues %lld\n", tmp->stat.st_blocks);
		ft_printf("Heure dernier acces %ld\n", tmp->stat.st_atime);
		ft_printf("Heure reniere modification %ld\n", tmp->stat.st_mtime);
		ft_printf("Heure dernier changement etat %ld\n", tmp->stat.st_ctime);
		ft_printf("Premiere lettre du type de fichier : %c\n", tmp->infos.permissions[0]);
		*/
		tmp = tmp->next;
	}

	/*
	tmp = env.errorlist;
	ft_printf("ERROR files :\n");
	while (tmp)
	{
		ft_printf("name = %s\n", tmp->name);
		freenode(tmp);
		tmp = tmp->next;
	}
	*/
	return (1);
}

int			main(int argc, char **argv)
{
	t_param	env;

	envinit(&env);
	parsing(argc, argv, &env);
	first_check(&env);
	listorder(&env.list, env.flags);
//	ft_test(env);
	return (1);
}

// je range correctement les fichiers passes en parametres, jaffiche correctement les fichiers qui n'existent pas, dans le bon ordre, et ma fonction de tri de liste est nickel.
// reste a faire le remplissage des dir passes en parametres et le print des arguments ainsi que les options a la con
