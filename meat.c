/* Name: Leul Mesfin
 * Start Date: Jul 1st, 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256 


/* 
 * The purpose of this function is to
 * reduce code duplication. This function
 * checks if count1 or count are 0 or not,
 * and then closes either the unordered list
 * or ordered list. It also resets the count 
 * to 0. This function returns nothing. 
 */
static void count_func(FILE **fp, int *c1, int *c2) {

  if (*c1!= 0) { 
    fprintf(*fp, "%s\n", "</ul>");
    *c1 = 0;
  }

  if (*c2 != 0) {
    fprintf(*fp, "%s\n", "</ol>"); 
    *c2 = 0;
  }

  return;
}


/* 
 * The purpose of this code example is to
 * open a text file, and convert its 
 * contents into an html file. I am
 * implementing a markdown to HTML tool.
 * Through this project, I am able to practice
 * file handling, text parsing, string manipulation, 
 * dynamic memory allocation, and the use of pointers.
 * I created this project to allow those with little 
 * to no programming experience to be able to craft 
 * simple websites. 
 **/
int main(void) {

  FILE *fp1 = NULL, *fp2 = NULL;
  char line[SIZE];
  char *ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL, *new_str1 = NULL;
  char *new_str2 = NULL, *new_str3 = NULL;
  int count = 0, count2 = 0;

  /* open both files for I/O*/
  fp1 = fopen("markdown.txt", "r");
  fp2 = fopen("html_doc.html", "w");

  if (fp1 != NULL && fp2 != NULL) {

    while (fgets(line, SIZE, fp1) != NULL) {

        /* removes the trailing new line*/	    
	line[strlen(line) - 1] = '\0';
        ptr1 = &line[1]; /* ignore the beginning symbol */
        ptr2 = &line[2]; /* ignores first 2 symbols */
	ptr3 = &line[3]; /* ignores first 3 symbols */

	/* allocate mem for new strings: allocate SIZE - 1*/
	/* copy contents from ptr to new str */
	new_str1 = malloc(SIZE - 1);
        if (new_str1 != NULL) {
	  strcpy(new_str1, ptr1);
	}

        new_str2 = malloc(SIZE - 2);
	if (new_str2 != NULL) {
          strcpy(new_str2, ptr2);
	}

	new_str3 = malloc(SIZE - 3);
	if (new_str3 != NULL) {

	  strcpy(new_str3, ptr3);
	}

	/* parses the line and applies the necessary
	 * html tags */

	/* include text after the symbols */
	if (line[0] == '#' && line[1] == '#' && line[2] == '#') {
          
	  /* include text after '###' */
	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<h3>", new_str3, "</h3>");

	}else if (line[0] == '#' && line[1] == '#' && line[2] != '#') {

	  /* include text after '##' */	
	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<h2>", new_str2, "</h2>");

	} else if (line[0] == '#' && line[1] != '#') {
        
	  /* include text after '#' */	
	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<h1>", new_str1, "</h1>");

	} else if (line[0] == '-') {
        
	  /* '-' means to italicize */     	
	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<em>", new_str1, "</em>");

        } else if (line[0] == '~') {
       
	  /* '~' means to bold */     	
	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<strong>", new_str1, "</strong>");

        } else if (line[0] == '*' && count == 0) {

          /* If this line is the first bullet point
	   * of an unordered list. */

          if (count2 != 0) {
            fprintf(fp2, "%s\n", "</ol>"); 
            count2 = 0;
          }

          fprintf(fp2, "%s\n%s%s%s\n", "<ul>", "<li>", new_str1, "</li>");
	  count++;

	} else if (line[0] == '*' && count != 0) {

          /* If this line is NOT the first bullet point
	   * of an unordered list. */

	  if (count2 != 0) {
            fprintf(fp2, "%s\n", "</ol>"); 
            count2 = 0;
          }

          fprintf(fp2, "%s%s%s\n", "<li>", new_str1, "</li>");
	  
	} else if (line[0] == '.' && count2 == 0) {

          /* The first bullet point of an ordered list. */

          if (count != 0) { 
            fprintf(fp2, "%s\n", "</ul>");
	    count = 0;
	  }

          fprintf(fp2, "%s\n%s%s%s\n", "<ol>", "<li>", new_str1, "</li>");
	  count2++;

	} else if (line[0] == '.' && count2 != 0) {

          /* NOT the first bullet point of an ordered list. */
          
	  if (count != 0) { 
            fprintf(fp2, "%s\n", "</ul>");
	    count = 0;
	  }

          fprintf(fp2, "%s%s%s\n", "<li>", new_str1, "</li>");

	} else if (line[0] == '!') {

          /* displays an image. Must be in the parser sub-directory */		
	  fprintf(fp2, "%s%s%s%s%s%s%s%s%s\n", "<img src =\"", new_str1, "\" alt=\"", 
			  new_str1, "\" ", "width= \"", "200\" ", "height= \"", "200\">");

	} else if (line[0] != '\0') {

          /* this conditional excludes paragraph tags
	   * for blank lines. */

	  count_func(&fp2, &count, &count2);
          fprintf(fp2, "%s%s%s\n", "<p>", line, "</p>");

	}

	/* free all allocated memory */
	free(new_str1);
	free(new_str2);
	free(new_str3);
    }
   
   /* close files to prevent leaks */ 
    fclose(fp2);
    fclose(fp1);
  }


  return 0;
}
