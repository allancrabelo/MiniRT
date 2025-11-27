#include "minirt.h"


// Allocates the requested memory and redirects the pointer to the garbage collector
void	*gc_calloc(t_rt *mini, size_t size)
{
	void	*ptr;
	t_gc	*node;

	ptr = ft_calloc(size, 1);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = mini->gc;
	mini->gc = node;
	return (ptr);
}

// Used to free a single allocated memory pointer
void	gc_free_one(t_rt *rt, void *ptr)
{
	t_gc	*cur;
	t_gc	*prev;

	cur = rt->gc;
	prev = NULL;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				rt->gc = cur->next;
			free(cur->ptr);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

// Used to free all allocated memory
void	gc_free_all(t_rt *rt)
{
	t_gc	*cur;
	t_gc	*next;

	cur = rt->gc;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	rt->gc = NULL;
}
