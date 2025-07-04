! RUN: %python %S/test_errors.py %s %flang_fc1 -pedantic -Werror
! Check out-of-range subscripts
subroutine subr(da)
  real a(10), da(2,1), empty(1:0,1)
  integer, parameter :: n(2) = [1, 2]
  integer unknown
  !ERROR: DATA statement designator 'a(0_8)' is out of range
  !ERROR: DATA statement designator 'a(11_8)' is out of range
  data a(0)/0./, a(10+1)/0./
  !ERROR: subscript 0 is less than lower bound 1 for dimension 1 of array
  print *, a(0)
  !ERROR: subscript 0 is less than lower bound 1 for dimension 1 of array
  print *, a(1-1)
  !ERROR: subscript 11 is greater than upper bound 10 for dimension 1 of array
  print *, a(11)
  !ERROR: subscript 11 is greater than upper bound 10 for dimension 1 of array
  print *, a(10+1)
  !ERROR: Subscript value (0) is out of range on dimension 1 in reference to a constant array value
  print *, n(0)
  !ERROR: Subscript value (3) is out of range on dimension 1 in reference to a constant array value
  print *, n(4-1)
  print *, a(1:12:3) ! ok
  !ERROR: subscript 13 is greater than upper bound 10 for dimension 1 of array
  print *, a(1:13:3)
  print *, a(10:-1:-3) ! ok
  !ERROR: subscript -2 is less than lower bound 1 for dimension 1 of array
  print *, a(10:-2:-3)
  print *, a(-1:-2) ! empty section is ok
  print *, a(0:11:-1) ! empty section is ok
  !ERROR: subscript 0 is less than lower bound 1 for dimension 1 of array
  print *, a(0:0:unknown) ! lower==upper, can ignore stride
  !ERROR: subscript 11 is greater than upper bound 10 for dimension 1 of array
  print *, a(11:11:unknown) ! lower==upper, can ignore stride
  !ERROR: subscript 0 is less than lower bound 1 for dimension 1 of array
  print *, da(0,1)
  !ERROR: subscript 3 is greater than upper bound 2 for dimension 1 of array
  print *, da(3,1)
  !ERROR: subscript 0 is less than lower bound 1 for dimension 2 of array
  print *, da(1,0)
  !WARNING: subscript 2 is greater than upper bound 1 for dimension 2 of array
  print *, da(1,2)
  print *, empty([(j,j=1,0)],1) ! ok
  print *, empty(1:0,1) ! ok
  print *, empty(:,1) ! ok
  print *, empty(i:j,k) ! ok
  !WARNING: Empty array dimension 1 should not be subscripted as an element or non-empty array section [-Wsubscripted-empty-array]
  print *, empty(i,1)
end
