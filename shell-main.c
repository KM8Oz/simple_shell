#include "utils/main.h"

int main(void)
{
char line[1024];
int input;
int first;
char *cmd;
char *next;

printf("SIMPLE SHELL: Type 'exit' or send EOF to exit.\n");
while (1)
{
printf("$> ");
fflush(NULL);
if (!fgets(line, sizeof(line), stdin))
return (0);
input = 0;
first = 1;
cmd = line;
next = strchr(cmd, '|');
while (next != NULL)
{
*next = '\0';
input = run(cmd, input, first, 0);
cmd = next + 1;
next = strchr(cmd, '|');
first = 0;
}
input = run(cmd, input, first, 1);
}

return (0);
}
