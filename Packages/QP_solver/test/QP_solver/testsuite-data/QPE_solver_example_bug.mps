* Number-type: integer
* Description: Original example where the omission first occured. Forces an Z1 update
* Generated-by: Generated by QPE_solver_example_bug.mw
NAME QPE_solver_example_bug
ROWS
 N obj
 G c1
 G c2
COLUMNS
  x1  obj  0
  x2  obj  0
  x3  obj  0
  x1  c1  -4
  x2  c1  2
  x3  c1  0
  x1  c2  0
  x2  c2  1
  x3  c2  1
RHS
  rhs  c1  -8
  rhs  c2  2
DMATRIX
  x1  x1  64
  x1  x2  -16
  x1  x3  0
  x2  x1  -16
  x2  x2  4
  x2  x3  2
  x3  x1  0
  x3  x2  -2
  x3  x3  0
ENDATA
