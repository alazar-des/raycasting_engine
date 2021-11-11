#include "parse.h"

/**
 * parseMap - parse map from file
 */
void parseMap(void)
{
	int i = 0, j = 0;
	FILE *fp;
	size_t fp_size, rd_size;
	char *buffer, *row_toke[MAP_WIDTH], *str_val, *str_toke;

	fp = fopen("src/map", "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "File opening error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	fp_size = ftell(fp);
	rewind(fp);

	buffer = malloc(sizeof(char) * fp_size);
	rd_size = fread(buffer, 1, fp_size, fp);
	if (rd_size != fp_size)
	{
		fprintf(stderr, "File reading error\n");
		exit(1);
	}

	str_toke = strtok(buffer, "{}");
	while (str_toke != NULL)
	{
		if (strcmp(str_toke, ",\n"))
			row_toke[i++] = str_toke;
		str_toke = strtok(NULL, "{}");
	}
	i = 0;
	while (i < MAP_HEIGHT)
	{
		str_val = strtok(row_toke[i], ",\n");
		j = 0;
		while (str_val != NULL)
		{
			Map.map[i][j++] = atoi(str_val);
			str_val = strtok(NULL, ",\n");
		}
		i++;
	}
	Map.disp = 1;
	Map.mapTime = 10;
	fclose(fp);
	free(buffer);
}
