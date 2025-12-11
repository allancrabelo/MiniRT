#include "minirt.h"

/**
 * @brief Allocates zero-initialized memory with garbage collection.
 * 
 * Allocates memory and adds it to the garbage collection list.
 * 
 * @param mini Pointer to main program structure.
 * @param size Size in bytes to allocate.
 * @return void* Pointer to allocated memory, or NULL on failure.
 */
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

/**
 * @brief Frees a specific pointer from garbage collection.
 * 
 * Searches for and removes a specific pointer from the GC list,
 * freeing both the pointer and its GC node.
 * 
 * @param rt Pointer to main program structure containing GC list.
 * @param ptr Pointer to free from garbage collection.
 */
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
			if (cur->ptr)
				free(cur->ptr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/**
 * @brief Frees all garbage-collected memory.
 * 
 * Iterates through the garbage collection list and frees all allocated memory.
 * 
 * @param rt Pointer to main program structure containing GC list.
 */
void	gc_free_all(t_rt *rt)
{
	t_gc	*cur;
	t_gc	*next;

	cur = rt->gc;
	while (cur)
	{
		next = cur->next;
		if (cur->ptr)
			free(cur->ptr);
		free(cur);
		cur = next;
	}
	rt->gc = NULL;
}
