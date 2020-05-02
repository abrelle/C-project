#include <stdio.h>
#include <stdlib.h>
#include "hw.h"

//************************************ DATA FROM FILE **********************************************
void from_file(Song * s, int *j, int *mem_num)
 {
	int i, nj, no_structs = 0, rand = *mem_num;
	FILE* f = fopen(FILE_NAME,"rb");
	if (f == NULL)
    {
		printf("New file was created.\n");                  //couldnt open -> new file
		f = fopen(FILE_NAME,"wb");
		fwrite(&no_structs, sizeof(int), 1, f);
    }
	fread(&nj, sizeof(int), 1, f);                             //first int is the amount of structs
	//printf("NJ%d\n", rand);
	if (nj > SIZE)                                           //allocates memory when starting program, so this is only for reallocating
    {
        while(nj / SIZE >= 1)                                   //how many times bigger
        {
            rand++;
        }

        s = (Song*) realloc(s, SIZE * rand * sizeof(Song));

        if (s == NULL)
        {
            free (s);
            printf("Failed to allocate memory");
        }
    }
    else if(nj == 0)
    {
        fclose(f);                 // not changing j in program
    }
    else
    {
    *j = nj;                     //changing j in program
    //printf("JJ%d\n", *j);
        for (i = 0; i < nj; i++)
            fread(&s[i], sizeof(Song), 1, f);
    //printf("%d\n", *j);
	/*printf("\nAll previously saved data:\n");
	for (i = 0; i < nj; i++)
    {
		printf("%d | %s | %s | %s | %d\n", s[i].num_list + 1, s[i].name, s[i].title, s[i].duration, s[i].date); //printin to ensure if data is right
	}
	*mem_num = rand;*/
	fclose(f);
    }
 }
//************************************ SAVING TO FILE ***************************************************
 int to_file(Song s[], int j)
 {
    int i;
    FILE* f = fopen(FILE_NAME, "wb");
    if (f == NULL)
    {
        return -1;    //could not open the file
    }

    fwrite(&j, sizeof(int), 1, f);

    for (i = 0; i < j; i++)
    {
        fwrite(&(s[i]), sizeof(Song), 1, f);
    }
    fclose(f);
    return 0;        //success
 }

