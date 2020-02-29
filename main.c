#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  struct matrix * edges = new_matrix(4, 0);
  struct matrix * transform = new_matrix(4, 4);

  // add_edge(edges, 25, 25, 0, 50, 50, 0);
  //
  // printf("doing translate\n");
  // transform = make_translate(100, 150, 75);
  // matrix_mult(transform, edges);
  // print_matrix(edges);
  // printf("\n\n");
  // ident(transform);
  //
  // printf("doing scale\n");
  // transform = make_scale(2, 2, 2);
  // matrix_mult(transform, edges);
  // print_matrix(edges);
  // printf("\n\n");
  // ident(transform);
  //
  // printf("doing x rotation\n");
  // transform = make_rotX(35);
  // matrix_mult(transform, edges);
  // print_matrix(edges);
  // printf("\n\n");
  // ident(transform);
  //
  // printf("doing y rotation\n");
  // transform = make_rotY(27);
  // matrix_mult(transform, edges);
  // print_matrix(edges);
  // printf("\n\n");
  // ident(transform);
  //
  // printf("doing z rotation\n");
  // transform = make_rotZ(48);
  // matrix_mult(transform, edges);
  // print_matrix(edges);
  // printf("\n\n");
  // ident(transform);

// DRAWING STUFF

  ident(edges);

  screen s;
  color c;

  c.red = 0;
  c.green = 0;
  c.blue = 0;

  clear_screen(s);

  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );
  //
  // draw_lines(edges, s, c);
  // display(s);
  // save_ppm_ascii(s, "image.ppm");

  free_matrix( edges );
  free_matrix( transform );
}
