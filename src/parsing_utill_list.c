#include "minishell_parsing.h"

t_list	*ft_lstnew(char **cmd)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->has_pip = 0;
	new->has_red = 0;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!*lst)
		*lst = new;
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->next = NULL;
}