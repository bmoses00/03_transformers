#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename
          struct matrix * transform,
          struct matrix * pm,
          screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix -
               takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
         ident: set the transform matrix to the identity matrix -
         scale: create a scale matrix,
                then multiply the transform matrix by the scale matrix -
                takes 3 arguments (sx, sy, sz)
         translate: create a translation matrix,
                    then multiply the transform matrix by the translation matrix -
                    takes 3 arguments (tx, ty, tz)
         rotate: create a rotation matrix,
                 then multiply the transform matrix by the rotation matrix -
                 takes 2 arguments (axis, theta) axis should be x y or z
         apply: apply the current transformation matrix to the edge matrix
         display: clear the screen, then
                  draw the lines of the edge matrix to the screen
                  display the screen
         save: clear the screen, then
               draw the lines of the edge matrix to the screen
               save the screen to a file -
               takes 1 argument (file name)
         quit: end parsing

See the file script for an example of the file format

IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename,
                  struct matrix * transform,
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 )
    f = stdin;
  else
    f = fopen(filename, "r");

  char ** args;
  while ( fgets(line, 255, f) != NULL ) {

    line[strlen(line)-1]='\0';

    if (!strcmp(line, "line")) {
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      args = parse_args(line);
      add_edge(edges,
                 atof(args[0]), atof(args[1]), atof(args[2]),
                 atof(args[3]), atof(args[4]), atof(args[5]));
    }
    else if (!strcmp(line, "ident")) {
      ident(transform);
    }
    else if (!strcmp(line, "scale")) {
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      args = parse_args(line);
      matrix_mult(
        make_scale(atof(args[0]), atof(args[1]), atof(args[2])),
        transform);
    }
    else if (!strcmp(line, "move")) {
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      args = parse_args(line);
      matrix_mult(
        make_translate(atof(args[0]), atof(args[1]), atof(args[2])),
        transform);
    }
    else if (!strcmp(line, "rotate")) {
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      args = parse_args(line);
      if      (!strcmp(args[0], "x")) matrix_mult(make_rotX(atof(args[1])), transform);
      else if (!strcmp(args[0], "y")) matrix_mult(make_rotY(atof(args[1])), transform);
      else if (!strcmp(args[0], "z")) matrix_mult(make_rotZ(atof(args[1])), transform);
    }
    else if (!strcmp(line, "apply")) {
      print_matrix(edges);

      matrix_mult(transform, edges);
      print_matrix(edges);
    }
    else if (!strcmp(line, "display")) {
      clear_screen(s);
      color c;
      c.red = 0;
      c.green = 0;
      c.blue = 0;
      draw_lines(edges, s, c);
      display(s);
    }
    else if (!strcmp(line, "save")) {
      clear_screen(s);
      color c;
      c.red = 0;
      c.green = 0;
      c.blue = 0;
      draw_lines(edges, s, c);
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      save_extension(s, line);
    }
    else if (!strcmp(line, "quit")) {
      exit(0);
    }
  }
  free(args);
}

char ** parse_args(char * line) {
	char ** args = calloc(100, 1);
	int i;
	for (i = 0; line != NULL; i++) {
		args[i] = calloc(10, 1);
		args[i] = strsep(&line, " ");
	}
	args[i] = NULL;
	return args;
}
