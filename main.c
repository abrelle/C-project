#include <stdio.h>
#include <stdlib.h>
#include "hw.h"

//***********************************************

void name_validation(char *name);
void song_title(Song *s);
void song_duration(Song *s);
void release_date(Song *s);
void del_el(Song s[],int j);
void edit_el_choice(Song s[],int j);
void all_data(Song s[], int j);
int empty_file();
void to_continue(Song s[], int j);
void filter_array_choice(Song s[], int j);
void filter_artist(Song s[], int j);
void filter_title(Song s[], int j);
void filter_duration(Song s[], int j);
void filter_years(Song s[], int j);
//***********************************************
int main()
{
    int mem_num = 2;   //variable for multiplying memory
    int choice;        //meniu options
    int j = 0;         //amount of structs
    int con;           //defines choice if continue
    int num;           //list number
    Song *s = NULL;
    s = (Song*)calloc(SIZE, sizeof(Song));
    if (s == NULL)
    {
        free (s);
        printf("Failed to allocate memory");
    }
    from_file(s, &j, &mem_num);  //getting info from bin file
    printf("\n\n");
    printf("***********************PROGRAM COLLECTS AND STORES DATA ABOUT SONGS***********************\n\n\n");
    while(1)
    {
    printf("\n**************************MENU OPTIONS:**********************\n\n");
    printf("1. Enter new data.\n2. Edit data.\n3. Delete data of one song.\n4. Delete all data.\n5. Display song list.\n6. Exit the program.\n7. Filter the data.\n\n");
        printf("Enter the number of menu option and press enter button: ");
        if(scanf("%1d", &choice) == 1 && (getchar() == '\n'))
        {
            switch(choice)
            {
                case 1:
                    if (j >= 50)
                    {
                       s = (Song*)realloc(s, SIZE * mem_num * sizeof(Song));
                       mem_num++;
                    }
                    s[j].num_list = j;
                    printf("\nEnter the name of the artist and press enter button\n");
                    name_validation(&(s[j]).name);
                    printf("\nEnter the title of the song and press the enter button\n");
                    name_validation(&s[j].title);
                    printf("\nEnter the duration of the song exactly in this format hh:mm:ss and press the enter button\n");
                    song_duration(&s[j]);
                    printf("\nEnter the song release date and press enter button\n");
                    release_date(&s[j]);
                    printf("\n-------------------------ENTERED DATA:-------------------------\n");
                    printf("\nNAME OF AN ARTIST:\t%s", s[j].name);
                    printf("\nTHE TITLE OF A SONG:\t%s", s[j].title);
                    printf("\nDURATION:\t%s", s[j].duration);
                    printf("\nRELEASE YEAR:\t%d\n", s[j].date);
                    j++;
                    to_continue(s, j);
                    break;

                //********************************************************************************************************************
                case 2:
                    all_data(s, j);
                    edit_el_choice(s, j);
                    to_continue(s, j);
                    break;
                //********************************************************************************************************************
                case 3:
                    all_data(s, j);
                    printf("\nEnter the list number of the song you would like to delete and press enter \n");
                        while(1)
                        {
                            if(scanf("%d", &num) == 1 && getchar() == '\n' && num > 0 && num < j + 1)
                                {
                                del_el(s, num);
                                printf("\nSuccess!\n");
                                break;
                                }
                             else
                                {
                                while(getchar()!= '\n')
                                    ;
                                printf("\nThis option is invalid! Try again!\n");
                                }
                        }
                    j--;
                    to_continue(s, j);
                    break;
                //********************************************************************************************************************
                case 4:
                    while(1)
                    {
                        printf("\n\nDo you really want to delete ALL data?\nEnter the option number\n1. Yes\n2. No\n");
                        if (scanf("%1d", &con) == 1 && con < 3 && con > 0 && getchar() == '\n')
                        {
                            if(con == 1)
                            {
                                if (empty_file() == 1)
                                {
                                   printf("\nData was deleted successfully!\n\n");
                                    break;
                                }
                                else
                                {
                                    printf("Error! Could not delete data from file\n");
                                }
                                j = 0;         // rewriting array from beginning
                            }
                        }
                        else
                        {
                            while(getchar() != '\n')
                            ;
                            printf("\nInput error! You must enter 1 or 2!\n");
                        }
                    }
                    to_continue(s, j);
                    break;
                //**********************************************************************************************************************
                case 5:
                    printf("\t\t\n\n*************SONG LIST:*****************\n\n");
                    printf("Nr || Artist || Title || Duration || Release date\n\n");
                    all_data(s, j);
                    to_continue(s, j);
                    break;
                //**********************************************************************************************************************
                case 6:
                    while(1)
                    {
                        printf("\n\nWould you like to save data?\nEnter the option number\n1. Yes\n2. No\n");
                        if (scanf("%d", &con) == 1 && con < 3 && con > 0 && getchar() == '\n')
                        {
                            if(con == 1)
                            {
                               if(to_file(s, j) != 1)
                               {
                                free(s);
                                exit(0);
                               }
                            else
                                printf("Failed to open the file for writing!\n");
                                break;
                            }
                        }
                        else
                        {
                            while(getchar() != '\n')
                                ;
                            printf("\nInput error! You must enter 1 or 2!\n");
                        }
                    }
                        printf("All data has been saved! Program is closed! Goodbye.\n");
                        break;
                //**********************************************************************************************************************
                case 7:
                    filter_array_choice(s, j);
                    to_continue(s, j);
                    break;
                //**********************************************************************************************************************
                default:
                    printf("\nThis option does not exist!\n");
            }
        }
        else
        {
            printf("\nThis option does not exist!\n");
            while(getchar() != '\n')
            ;

        }
    }
}

  //************************************ ARTIST **********************************************
void name_validation(char * name)
 {
    int l;  //lenght of a string
    while (1)
    {
        gets(name);
        l = strlen(name);
        if (l > MAX_STR)
            printf("\nArtist name is too long\n");  //checking if in range
        else
        {
            if(isspace(name[0]))                                         //if first char is whites space
            {
                printf("\nError! Name must start with some kind of symbol\n");
            }
            else
            {
                printf("\nSuccess!\n");
                break;
            }
        }
    }
 }

  //************************************ TITLE **********************************************
 void song_title(Song *s)
 {
    int l;   //lenght of a string
    while (1)
    {
        gets(s->title);
        l = strlen(s->title);
            if (l > MAX_STR)
                printf("\nTitle is too long\n");
            else
            {
                if(isspace(s->title[0]))
                {
                printf("\nError! Title must begin with some kind of symbol!\n");
                }
                else
                {
                printf("\nSuccess!\n");
                break;
                }
            }
    }
 }


 //************************************ DURATION **********************************************
void song_duration(Song *s)
{
    int l;
        while(1)
        {
            gets(s->duration);
            l = strlen(s->duration);                                //cheking if right size
            if (l != TIME)
                printf("\nInput error! Try again.\n");
            else
            {
                if(isspace(s->duration[0]))
                {
                   printf("\nError! Duration must start with some kind of symbol\n");

                }
                else if (isdigit(s->duration[0]) == 0 || isdigit(s->duration[3]) == 0 || isdigit(s->duration[6]) == 0) //if numbers
                {
                    printf(" Error. Check if all right numbers\n");
                }
                else if(s->duration[3] > 53 || s->duration[6] > 53)    //if possible values of h/min
                {
                    printf("Number of minutes or hours must be less than 60 \n ");
                }
                else if (isdigit(s->duration[1]) == 0 || isdigit(s->duration[4]) == 0 || isdigit(s->duration[7]) == 0) //if number
                {
                    printf(" Error. Check if all right numbers\n");
                }
                else if (s->duration[2] != ':' || s->duration[5] != ':')  //if right format
                {
                  printf(" Error. Check if all right symbols\n");
                }
                else
                {
                printf("\nSuccess!\n");
                break;
                }
            }
    }
}


 //************************************ RELEASE DATE **********************************************
void release_date(Song *s)
 {
    while(1)
    {
       if((scanf("%d", &s->date) == 1) && (getchar() == '\n'))
       {
         if(s->date > MIN_YEARS && s->date <= MAX_YEARS)
         {
             printf("\nSuccess!\n");
             break;
         }
         else printf("\nError! Imput is not valid.\n");
       }

       else
       {
           while(getchar() != '\n')
           ;
           printf("\nImput error! Try once again.\n");
       }
    }
 }

  //************************************ EDITING THE ENTRY **********************************************
void edit_el_choice(Song s[],int j)
{
  int num, choice;
  printf("\nEnter the list number of the song you would like to edit and press enter \n");
  while(1)
  {
      if((scanf("%1000d", &num) == 1) && (getchar() == '\n') && num > 0 && num <= j)  //if correct input
      {
          while(1)
            {
                printf("\n-------------------------What would you like to change?-------------------------\n\n");
                printf("1.Artist name.\n2.Song title\n3.Song duration.\n4.Date of release.\n5.All information\n");
                if(scanf("%1d", &choice) == 1 && (getchar() == '\n'))
                {
                    switch(choice)
                    {
                        case 1:
                        name_validation(&s[num-1].name);        // [num - 1], because array starts from 0 and diplayed data starts from 1
                        break;

                        case 2:
                        song_title(&s[num-1]);
                        break;

                        case 3:
                        song_duration(&s[num-1]);
                        break;

                        case 4:
                        release_date(&s[num-1]);
                        break;

                        case 5:
                        name_validation(&s[num-1].name);
                        song_title(&s[num-1]);
                        song_duration(&s[num-1]);
                        release_date(&s[num-1]);
                        break;

                        default:
                    printf("\nThis option is invalid!\n");
                    }
                    break;
                }
            else
                {
                    printf("\nThis option is invalid!\n");
                    while(getchar() != '\n')
                        ;
                }
        }
      break;

    }
      else
      {
          printf("\nThis option is invalid! Try again!\n");
          while(getchar() != '\n')
            ;
      }
  }
}

 //************************************ DELETING ELEMENT **********************************************
void del_el(Song s[],int num)
{

    int i;
    for(i = num - 1; i < num; i++)
      {
          s[i] = s[i+1];
          s[i].num_list--;
      }
}

 //************************************ PRINTING ALL DATA **********************************************
void all_data(Song s[], int j)
 {
     int i;
     for (i = 0; i < j; i++)
     {
         printf("%d | %s | %s | %s | %d\n", s[i].num_list + 1, s[i].name, s[i].title, s[i].duration, s[i].date);
     }
 }
  //************************************ DELETING ALL DATA **********************************************
int empty_file()
{
    FILE* f = fopen(FILE_NAME, "wb");
    if (f == NULL)
    {
        fclose(f);
        return 0;     //  error
    }
    else
    {
        return 1;    //  success
    }
}

 //************************************ CHEKING IF CONTINUE **********************************************
void to_continue(Song s[], int j)
{
    int con;    //defines choice if continue
    while(1)
    {
        printf("\n\nWould you like to continue the work?\nEnter the option number\n1. Yes\n2. No\n");
        if (scanf("%1d", &con) == 1 && con < 3 && con > 0 && getchar() == '\n')
        {
            if(con == 2)
            {
                to_file(s, j);
                exit(0);
            }
            break;
        }
        else
        {
            while(getchar() != '\n')
                ;
            printf("\nInput error! You must enter 1 or 2!\n");
        }
    }
}

//********************************FILTER*******************************
void filter_array_choice(Song s[], int j)
{
    int op;
    printf("Choose what do you want to filter:\n");
    printf("\n1. Song artist\n2. Song title\n3. Duration\n4. Release year\n");
    while(1)
    {
        if(scanf("%1d", &op) == 1 && op > 0 && op < 5 && getchar() == '\n')
        {
            switch(op)
            {
                case 1:
                    filter_artist(s, j);
                break;
                case 2:
                    filter_title(s, j);
                break;
                case 3:
                    filter_duration(s, j);
                    break;
                case 4:
                    filter_years(s, j);
                    break;
            }
            break;
        }
        else
        {
            while(getchar() != '\n')
                ;
            printf("Invalid option. Try again!\n");
        }
    }
}
void filter_artist(Song s[], int j)
{
    int i;
    int sk = 0;
    char temp_arr[MAX_STR];
    gets(temp_arr);
    for (i = 0; i < j; i++)
    {
        if(strncmp(s[i].name, temp_arr, MAX_STR) == 0)
        {
            printf("%d | %s | %s | %s | %d \n", i + 1, s[i].name, s[i].title, s[i].duration, s[i].date);
            sk++;
        }
    }
    if (sk == 0) printf("No elements\n");
}
void filter_title(Song s[], int j)
{
    int i;
    int sk = 0;
    char temp_arr[MAX_STR];
    printf("Enter the title of a song:\n");
    gets(temp_arr);
    for (i = 0; i < j; i++)
    {
        if(strncmp(s[i].title, temp_arr, MAX_STR) == 0)
        {
         printf("%d | %s | %s | %s | %d \n", i + 1, s[i].name, s[i].title, s[i].duration, s[i].date);
         sk++;
        }
    }
    if (sk == 0) printf("No elements\n");
}
void filter_duration(Song s[], int j)
{
    int i, l, sk = 0;
    long int sum1, sum2, sum3;
    char temp_arr[17];
    while(1)
    {
            printf("Enter the interval in this format hh:mm:ss-hh:mm:ss without spaces:\n");
            gets(temp_arr);
            l = strlen(temp_arr);//cheking if right size
            if (l != (TIME * 2) + 1) printf("\nInput error! Try again.\n");
            else
            {
                if(isspace(temp_arr[0]));
                else if (isdigit(temp_arr[0]) == 0 || isdigit(temp_arr[1]) == 0 || isdigit(temp_arr[3]) == 0)//if numbers
                {
                    printf("Check if imputs are numbers\n");
                }
                else if (isdigit(temp_arr[4]) == 0 || isdigit(temp_arr[6]) == 0 || isdigit(temp_arr[7]) == 0) //if numbers
                {
                    printf("Check if imputs are numbers\n");
                }
                else if (isdigit(temp_arr[9]) == 0 || isdigit(temp_arr[10]) == 0 || isdigit(temp_arr[12]) == 0) //if numbers
                {
                    printf("Check if imputs are numbers\n");
                }
                else if (isdigit(temp_arr[13]) == 0 || isdigit(temp_arr[15]) == 0 || isdigit(temp_arr[16]) == 0) //if number
                {
                    printf("Check if imputs are numbers\n");
                }
                else if(temp_arr[3] > 53 || temp_arr[6] > 53 || temp_arr[12] > 53 || temp_arr[15] > 53)  //if possible values of h/min
                {
                    printf("Check if minutes and hours are not bigger than 59\n");
                }
                else if (temp_arr[2] != ':' || temp_arr[5] != ':' || temp_arr[8] != '-' || temp_arr[11] != ':' || temp_arr[14] != ':' ) //if right format
                {
                    printf("Check if symbols are right\n");
                }
                /*else if(temp_arr[0] > temp_arr[9] || temp_arr[1] > temp_arr[10] || temp_arr[3] > temp_arr[12])
                {
                    printf("Second time imput has to be bigger\n");
                }
                else if(temp_arr[4] > temp_arr[13] || temp_arr[6] > temp_arr[15] || temp_arr[7] > temp_arr[16])
                {
                    printf("Second time imput has to be bigger\n");
                }*/
                else
                {
                printf("\nSuccess!\n");
                break;
                }
            }
    }
        sum2 = ((temp_arr[0] - '0') * ADD_ZERO + (temp_arr[1] - '0')) * HOUR_SECS;
        sum2 = sum2 + ((temp_arr[3] - '0') * ADD_ZERO + (temp_arr[4] - '0')) * MIN_SECS;
        sum2 = sum2 + (temp_arr[6] - '0') * ADD_ZERO + (temp_arr[7] - '0');
        sum3 = ((temp_arr[9] - '0') * ADD_ZERO + (temp_arr[10] - '0')) * HOUR_SECS;
        sum3 = sum3 + ((temp_arr[12] - '0') * ADD_ZERO + (temp_arr[13] - '0')) * MIN_SECS;
        sum3 = sum3 + (temp_arr[15] - '0') * ADD_ZERO + (temp_arr[16] - '0');
    for(i = 0; i < j; i++)
    {
        sum1 = ((s[i].duration[0] - '0') * ADD_ZERO + (s[i].duration[1] - '0')) * HOUR_SECS;
        sum1 = sum1 + ((s[i].duration[3] - '0') * ADD_ZERO + (s[i].duration[4] - '0')) * MIN_SECS;
        sum1 = sum1 + (s[i].duration[6] - '0') * ADD_ZERO + (s[i].duration[7] - '0');
        if(sum1 >= sum2 && sum1 <= sum3)
        {
            printf("%d | %s | %s | %s | %d \n", i + 1, s[i].name, s[i].title, s[i].duration, s[i].date);
                  sk++;
        }
    }
    if(sk == 0)
      {
        printf("No elements!\n");
      }
}

void filter_years(Song s[], int j)
{
    int i, num1, num2, sk = 0;
    while(1)
    {
      printf("Enter the interval in this format xxxx-xxxx without spaces:\n");
       if(scanf("%4d", &num1) == 1 && getchar() == '-' && scanf("%4d", &num2) && num1 <= num2 && num1 >= MIN_YEARS && num2 <= MAX_YEARS && getchar() == '\n')
       {
          for (i = 0; i < j; i++)
          {
              if (s[i].date >= num1 && s[i].date <= num2)
              {
                  printf("%d | %s | %s | %s | %d \n", i + 1, s[i].name, s[i].title, s[i].duration, s[i].date);
                  sk++;
              }
          }
          if(sk == 0)
          {
            printf("No elements!\n");
          }
          break;
       }
       else
       {
           while (getchar() != '\n')
            ;
           printf("Invalid format. Try again!\n");
       }
    }
}
