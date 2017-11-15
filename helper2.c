#include "header.h"
/**
 * _realloc - reallocs a mem block
 * @ptr: ptr to old mem
 * @old_size: # of bytes allocated for sp in ptr
 * @new_size: # of bytes in new mem block
 * Return: new ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	for (i = 0; i < new_size && i < old_size; i++)
		new[i] = ((char *) ptr)[i];
	free(ptr);
	return (new);
}
