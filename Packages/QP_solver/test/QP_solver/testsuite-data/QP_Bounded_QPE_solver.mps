* Number-type: integer
* Description: Some simple QP example
* Generated-by: Generated by QP_Bounded_QPE_solver.mw
NAME QP_Bounded_QPE_solver
ROWS
 N obj
 G c1
COLUMNS
  x1  obj  0
  x2  obj  0
  x1  c1  1
  x2  c1  -1
RHS
  rhs  c1  2
DMATRIX
  x1  x1  1
  x1  x2  0
  x2  x1  0
  x2  x2  0
ENDATA
