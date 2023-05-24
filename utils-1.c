/**
 * _strcpy - copy the string pointed by src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
    char *dest_start = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return dest_start;
}