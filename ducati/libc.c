/*
 * "Minimal" libc functions.
 * Author: Vincent Stehlé <v-stehle@ti.com>
 *
 * We supply our own minimal libc, for easier build.
 * Redifining the memory allocation functions has the benefit to make them
 * "task" aware.
 *
 * Another alternative is to use e.g. newlib.
 */

#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"

void *malloc(size_t size)
{
	return pvPortMalloc(size);
}

void free(void *ptr)
{
	vPortFree(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
	void *r = pvPortMalloc(nmemb * size);

	if (r)
		memset(r, 0, nmemb * size);

	return r;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	unsigned u;

	for (u = 0; u < n; u++)
		((char *)dest)[u] = ((const char *)src)[u];

	return dest;
}

size_t strlen(const char *s)
{
	unsigned u;

	for (u = 0; s[u] != '\0'; u++);

	return u;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	unsigned u;

	for (u = 0; u < n && src[u] != '\0'; u++)
		dest[u] = src[u];

	for (; u < n; u++)
		dest[u] = '\0';

	return dest;
}

void *memset(void *s, int c, size_t n)
{
	unsigned u;

	for (u = 0; u < n; u++)
		((char *)s)[u] = c;

	return s;
}
