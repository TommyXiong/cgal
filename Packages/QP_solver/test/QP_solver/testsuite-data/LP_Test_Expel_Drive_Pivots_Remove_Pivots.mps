* Number-type: integer
* Description: Example not having full row rank and optimal initial basic feasible solution having all artificial variables in the basis, thus forcing the expel procedure to pivot some of the artificial variables out of the basis and remove the remaining ones together with their corresponding constraints
* Generated-by: Generated by LP_Test_Expel_Drive_Pivots_Remove_Pivots.mw
NAME LP_Test_Expel_Drive_Pivots_Remove_Pivots
ROWS
 N obj
 E c1
 E c2
 E c3
COLUMNS
  x1  obj  -1
  x2  obj  -1
  x3  obj  -1
  x1  c1  -1
  x2  c1  0
  x3  c1  0
  x1  c2  0
  x2  c2  -1
  x3  c2  0
  x1  c3  0
  x2  c3  -1
  x3  c3  0
RHS
  rhs  c1  0
  rhs  c2  0
  rhs  c3  0
ENDATA
