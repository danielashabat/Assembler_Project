#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#define firstStr 5

void passTwoMain(int argc, char* argv[])
{
	char firstString[5] = { 0 };
	char immBefore[51] = { 0 }; //last spot for \0
	char cl = '0';
	int adress = 0;
	int count = 0;
	HashTable* table = NULL;
	table = passoneMain();
	//in args: test.txt write.txt memin.txt
	FILE *f1 = fopen(argv[2], "r");
	FILE *memin = fopen(argv[3], "w");

	if (f1 == NULL || memin == NULL)
	{
		printf("Cant open the file\n");
		free_table(table);
		exit(1);
	}
	while (!feof(f1))
	{
		fscanf(f1, firstString); //string untill space opcode-rd-rs-rt
		//fscanf(f1, "%s",immBefore); //take original imm
		//HOW TO PUT \0 IN THE RIGHT SPOT?
		count = 0;
		while ((cl = getc(f1)) != '\n') //get imm - as a string (\0)
		{
			if (cl != ' ') //if it continues after the fscanf including the space
			{
				immBefore[count] = cl;
				count++;
			}
		}
		immBefore[count] = '\0';

		fprintf(memin, "%s", firstString); //write to memin all the line but the imm

		//check if label or number
		//if label - returns code from table, else returns -1
		adress=get_adress_from_label(table, immBefore);
		
		if (adress == -1) //if number
		{
			//if it was already a number it was in hexa
			fprintf(memin, "%03s\n", immBefore); //only the first 3 chars? no \0
		}
		else //if label
		{
			//adress is int, write as hexa
			fprintf(memin, "%03X\n", adress);
		}
	}

	fclose(f1);
	fclose(memin);

	free_table(table);
}