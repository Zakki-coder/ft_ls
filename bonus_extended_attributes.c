/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_extended_attributes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:00:45 by jniemine          #+#    #+#             */
/*   Updated: 2022/09/13 20:49:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
void parse_acl(char *acl, int i)
{
	char buf[256];

	ft_bzero(buf, 256);
	acl += ft_strchr(acl, '\n') + 1 - acl;
	ft_strncpy(buf, acl, ft_strchr(acl, ':') - acl + 1);	
	acl = ft_strchr(ft_strchr(acl, ':') + 1, ':') + 1;
	ft_strncat(buf, acl, ft_strchr(acl, ':') - acl);
	acl = ft_strchr(ft_strchr(acl, ':') + 1, ':') + 1;
	ft_strcat(buf, " ");
	ft_strncat(buf, acl, ft_strchr(acl, ':') - acl);
	acl = ft_strchr(acl, ':') + 1;
	ft_printf(" %d: %s\n", i, buf);
}
*/

void print_extended_attributes(t_file_node *head, int flags)
{
	int			i;
//	int			k;
	int			tab_n;
	int			print_len;
//	acl_entry_t	*entryp = ft_memalloc(sizeof(acl_entry_t));
//	acl_permset_t permsetp;
//	acl_tag_t	*tag_type;
//	ssize_t		len;
//	char		*ret;

	i = 0;
	/* Maybe you already have the lengths saved in struct */
//	tag_type = ft_memalloc(sizeof(*tag_type));
	if(flags & EXT_ATTR && head->ext_attr != NULL)
	{
		while(i < head->ext_attr_len)	
		{
			print_len = getxattr(head->path, head->ext_attr + i, NULL, 0, 0, XATTR_NOFOLLOW);
			print_len = getxattr(head->path, head->ext_attr + i, NULL, 0, 0, XATTR_NOFOLLOW);
			tab_n = ft_strlen(head->ext_attr + i) / 8;
			ft_printf("\t%s", head->ext_attr + i);
			ft_printf("%*ld\n", 13 + tab_n * 8 - ft_strlen(head->ext_attr + i), print_len);
			i += ft_strlen(head->ext_attr + i) + 1;
		}
	}
//	else if(flags & ACL && head->acl)
//	{
//		len = 1;
//		k = 0;
//		i = 0;
//	//	if (acl_get_entry(head->acl, ACL_FIRST_ENTRY, entryp) < 0)
//	//		error_exit();
//		ret = acl_to_text(head->acl, &len);
//			printf("Ret; %s\n", ret);
//		while(k < len) 
//		{
//		//	if(acl_get_permset(entryp, &permsetp) < 0)
//		//		error_exit();
//		//	if(acl_get_tag_type(entryp,	tag_type) < 0)
//		//		error_exit();
//			ret = acl_to_text(head->acl, &len);
//			parse_acl(ret + k, i++);
//			k += ft_strlen(ret) + 1;
//			//	if(acl_get_entry(head->acl, ++i, &entryp) <= 0)
//			//		break ;
//		}
//	}
}
