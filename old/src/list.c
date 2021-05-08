#include "minishell.h"

void	list_free(t_list **list)
{
	t_list *nod;
	t_list *next;

	nod = *list;
	while (nod)
	{
		next = nod->next;
		//free(nod->obj);
		free(nod);
		nod = next;
	}
}

void		world_list_add(t_list **list, t_list *new, int type)
{
	t_list *last;

	//new->type = type;
	if (!(*list))
		*list = new;
	last = listlast(*list);
	last->next = new;
	new->next = NULL;
}

t_list	*list_cre(void *obj)
{
	t_list	*re;

	re = (t_list *)malloc(sizeof(t_list));
	if (!re)
		return (0);
	//re->obj = obj;
	re->next = NULL;
	return (re);
}

t_list	*listlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}