#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "test_general.h"


bool test_new_piece_rh() {
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for (bool small=false; !small ; small= !small)
        for (bool horizontal=false; !horizontal ; horizontal= !horizontal) {
          if((y>=4 && !horizontal && !small) || (x>=4 && horizontal && !small)){
            break; 
            /**
             * without this condition and the break, 
             * the program is going to create pieces outside of the board. 
             * It would activate a security in the function new_piece_rh
             */
          }
          int size;
          if (small)
            size = 2;
          else
            size = 3;
          piece p = new_piece_rh(x, y, small, horizontal);
          result = result && test_equality_int(x, get_x(p),"get_x");
          result = result && test_equality_int(y, get_y(p),"get_y");

          if (horizontal) {
            result = result && test_equality_int(1, get_height(p), "get_height");
            result = result && test_equality_int(size, get_width(p), "get_width");
          }
          else {
            result = result && test_equality_int(size, get_height(p), "get_height");
            result = result && test_equality_int(1, get_width(p), "get_width");
          }
          delete_piece(p);
        }
  return result;
}

bool test_intersect() {
  bool result = true;
  set_up();
  for (int i=0; i < NB_PIECES; i++)
    for (int j =0; j<NB_PIECES; j++) {
      result = result && test_equality_bool(i==j, intersect(pieces[i], pieces[j]),"intersect");
    }

  piece pb_piece1 = new_piece_rh(3, 3, false, false);
  piece pb_piece2 = new_piece_rh(3, 1, false, false);
  result = result && test_equality_bool(true, intersect(pieces[0], pb_piece1),"intersect pb1");
  result = result && test_equality_bool(true, intersect(pb_piece2, pb_piece1),"intersect pb2");
  tear_down();
  delete_piece(pb_piece1);
  delete_piece(pb_piece2);
  return result;
}

bool test_move() {
  bool result = true;
  piece p = new_piece_rh(0, 0, true, true);
  set_up();
  for (int dist = 1; dist < NB_PIECES; dist++)
    for (int i=0; i < NB_PIECES; i++) {
      copy_piece(pieces[i],p);
      move_piece(p, LEFT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])-dist,get_x(p),"move LEFT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move LEFT");
      copy_piece(pieces[i],p);
      move_piece(p, RIGHT, dist);
      if (is_horizontal(pieces[i]))
        result = result && test_equality_int(get_x(pieces[i])+dist,get_x(p),"move RIGHT");
      else
        result = result && test_equality_int(get_x(pieces[i]),get_x(p),"move RIGHT");
      copy_piece(pieces[i],p);
      move_piece(p, UP, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])+dist,get_y(p),"move UP");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move UP");
      copy_piece(pieces[i],p);
      move_piece(p, DOWN, dist);
      if (!is_horizontal(pieces[i]))
        result = result && test_equality_int(get_y(pieces[i])-dist,get_y(p),"move DOWN");
      else
        result = result && test_equality_int(get_y(pieces[i]),get_y(p),"move DOWN");
    }
  tear_down();
  delete_piece(p);
  return result;
}

bool test_copy() {
  piece p = new_piece_rh(0, 0, true, true);
  bool result = true;
  set_up();
  for (int i = 0 ; i < NB_PIECES; i++) {
    copy_piece(pieces[i],p);
    result = result && test_equality_int(get_height(pieces[i]), get_height(p), "copy get_height");
    result = result && test_equality_int(get_width(pieces[i]), get_width(p), "copy get_width");
    result = result && test_equality_int(get_x(pieces[i]), get_x(p), "copy get_x");
    result = result && test_equality_int(get_y(pieces[i]), get_y(p), "copy get_y");
    result = result && test_equality_bool(is_horizontal(pieces[i]), is_horizontal(p), "copy is_horizontal");
  }
  tear_down();
  delete_piece(p);
  return result;
}

int main (int argc, char *argv[])
{
  bool result= true;

  result = result && test_equality_bool(true, test_new_piece_rh(), "new_piece_hr");
  result = result && test_equality_bool(true, test_intersect(), "intersect");
  result = result && test_equality_bool(true, test_move(), "move");
  result = result && test_equality_bool(true, test_copy(), "copy");

  if (result) {
    printf("Youpi !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
