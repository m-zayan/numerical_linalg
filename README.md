# Numerical Linear Algebra C++/API

### Summation Algorithms: Error Reduction 

```c++

max_size_t test_size = static_cast<max_size_t>(1e6);

test_api::test_sum_alg(test_size);

```

```c++

vector :[1, 2.1, 3.2, 4.3, 5.5]

========================
naive_summation :16.1
kahan_summation :16.1
shift_reduce_sum :16.1
pairwise_selection_sum :16.1
========================

shift_reduce_sum - in range [1, 4)  :9.6

========================
apply_in_range vec1d: 
------------------------
vector :[1, 2, 3, 4, 5]
vector^2 :[1, 4, 9, 16, 25]
========================

############# Test ############

========================
Execution Time of Naive Sum :5 ms
Execution Time of Kahan Sum :9 ms
Execution Time of Pairwise Sum :4 ms
Execution Time of Shift Reduce Sum :5 ms
Execution Time of Pairwise Selection Sum :8 ms
========================

absolute - difference :
------------------------
kahan - naive : 4.64551
pairwise - naive : 4.64532
shift_reduce_sum - naive : 4.64551
pairwise_selection_sum - naive : 4.64319
========================

summation - result:
------------------------
naive : 5.01747e+11
kahan : 5.01747e+11
pairwise : 5.01747e+11
shift_reduce_sum : 5.01747e+11
pairwise_selection_sum : 5.01747e+11

========================
Generated Test Case - TXT - File :test_api/gen_test_cases.txt
========================

```

### N-Dimensional Matrix Allocation (C contiguous)
----

```c++

	shape_t shape = { 3, 3 };

	nd::matrix<int> mat = nd::random::uniform<int>(1, 10, shape); // low = 1, high = 10

	std::cout << "shape :" << mat.shape() << ln;
	std::cout << "Chunk storage size :" << mat.size() << ln;

	std::cout << "=======================\n";
	mat.print_matrix();

	std::cout << "========== matrix[0] ============\n";
	mat[0].print_matrix();

	std::cout << "========== matrix[1] ============\n";
	mat[1].print_matrix();

	std::cout << "========== matrix[2] ============\n";
	mat[2].print_matrix();

	std::cout << "========== Updated: op: diag(matrix) = 0 ============\n";

	for (max_size_t i = 0; i < 3; i++) {
		mat.assign( { i, i }, 0);
	}

	mat.print_matrix();

	std::cout
			<< "============ op: (matrix * matrix) - (matrix + matrix) =========\n";
	((mat * mat) - (mat + mat)).print_matrix();

	std::cout << "============ Matrix (3, 3, 2)==========\n";

	shape_t shape2 = { 3, 3, 2 };

	nd::matrix<int> mat2 = nd::random::uniform(1, 10, shape2); // low = 1, high = 10
	mat2.print_matrix();

	std::cout << "----------------\n";

	std::cout << std::boolalpha;
	std::cout << "mat2 - own-data :" << mat2.own_data() << ln;
	std::cout << "mat2[0] - own-data :" << mat2[0].own_data() << ln;

	std::cout << "========== [1]: Identity - {3, 3} =======\n";

	shape_t shape_01 = { 3, 3 };
	nd::matrix<int> mat_01 = nd::linalg::eye<int>(shape_01);

	mat_01.print_matrix();

	std::cout << "========== [2]: Diag(matrix) = 3 - {3, 3} =======\n";

	shape_t shape_02 = { 3, 3 };
	nd::matrix<int> mat_02 = nd::linalg::eye<int>(shape_02);

	mat_02 *= 3;
	mat_02.print_matrix();

	std::cout << "========== Stack [1], [2] =======\n";

	nd::matrix<int> result = nd::stack<int>( { mat_01, mat_02 });

	result.print_matrix();

```
  
  
  ```c++

shape :(3,3)
Chunk storage size :9
=======================

[[2, 5, 7]
[2, 9, 3]
[10, 10, 2]]

========== matrix[0] ============

[2, 5, 7]

========== matrix[1] ============

[2, 9, 3]

========== matrix[2] ============

[10, 10, 2]

========== Updated: op: diag(matrix) = 0 ============

[[0, 5, 7]
[2, 0, 3]
[10, 10, 0]]

============ op: (matrix * matrix) - (matrix + matrix) =========

[[0, 15, 35]
[0, 0, 3]
[80, 80, 0]]

============ Matrix (3, 3, 2)==========

[[[4, 1]
[10, 6]
[3, 3]]

[[9, 9]
[2, 7]
[8, 4]]

[[6, 5]
[1, 8]
[5, 5]]]

----------------

mat2 - own-data :true
mat2[0] - own-data :false

========== [1]: Identity - {3, 3} =======

[[1, 0, 0]
[0, 1, 0]
[0, 0, 1]]

========== [2]: Diag(matrix) = 3 - {3, 3} =======

[[3, 0, 0]
[0, 3, 0]
[0, 0, 3]]

========== Stack [1], [2] =======

[[[1, 0, 0]
[0, 1, 0]
[0, 0, 1]]

[[3, 0, 0]
[0, 3, 0]
[0, 0, 3]]]

```

-----------------------


### N-Dimensional Sequential Iterator
```c++

shape_t shape = { 4, 3, 2, 2 };
max_size_t ndim = shape.size();

SequentialNdIterator seqIter(shape);

max_size_t count = 0;

seqIter.icurrent().print_vec1d(0, ndim);
std::cout << " : " << count++ << ln;

while (!seqIter.isLoked()) {

	seqIter.next().print_vec1d(0, ndim);
	std::cout << " : " << count++ << ln;
}

```
-----------------------

### N-Dimensional Matrix Multiplication (C contiguous)
----
  ```c++

nd::matrix<int> mat1 = nd::random::uniform<int>(1, 10, { 3, 3, 2 });

nd::matrix<int> mat2 = nd::random::uniform<int>(1, 10, { 2, 4 });

std::cout << "=============== (3, 3, 2) ================\n";

mat1.print_matrix();

std::cout << "=============== (2, 4) ================\n";

mat2.print_matrix();

std::cout << "============= matmul: (3, 3, 2) - (2, 4) ================\n";
nd::matrix<int> result = nd::linalg::matmul<int>(mat1, mat2);

std::cout << "shape :" << result.shape() << " -- own-data :"
		<< result.own_data() << ln;
std::cout << "---------------------\n";

result.print_matrix();

  ```
  

 ```c++
=============== (3, 3, 2) ================

[[[6, 3]
[7, 2]
[10, 4]]

[[10, 3]
[7, 2]
[8, 10]]

[[5, 10]
[2, 1]
[4, 4]]]

=============== (2, 4) ================

[[9, 6, 9, 3]
[9, 1, 9, 2]]

============= matmul: (3, 3, 2) - (2, 4) ================

shape :(3,3,4) -- own-data :1
---------------------

[[[81, 39, 81, 24]
[81, 44, 81, 25]
[126, 64, 126, 38]]

[[117, 63, 117, 36]
[81, 44, 81, 25]
[162, 58, 162, 44]]

[[135, 40, 135, 35]
[27, 13, 27, 8]
[72, 28, 72, 20]]]

```
 
-----------------------

### N-Dimensional Matrix Dot Product (C contiguous)
----
  ```c++

nd::matrix<int> mat1 = nd::random::uniform<int>(0, 3, { 3, 3, 2 });

nd::matrix<int> mat2 = nd::random::uniform<int>(0, 3, { 3, 2, 3 });

std::cout << "=============== (3, 3, 2) ================\n";

mat1.print_matrix();

std::cout << "=============== (3, 2, 3) ================\n";

mat2.print_matrix();

std::cout << "============= dot: (3, 3, 2) - (3, 2, 3) ================\n";
nd::matrix<int> result = nd::linalg::dot<int>(mat1, mat2);

std::cout << "shape :" << result.shape() << " -- own-data :"
		<< result.own_data() << ln;

std::cout << "---------------------\n";

result.print_matrix();

  ```



 ```c++
 
=============== (3, 3, 2) ================

[[[3, 1]
[3, 3]
[1, 2]]

[[0, 1]
[1, 3]
[1, 1]]

[[0, 2]
[0, 2]
[2, 2]]]

=============== (3, 2, 3) ================

[[[0, 0, 3]
[1, 3, 1]]

[[1, 1, 2]
[0, 0, 0]]

[[0, 1, 3]
[3, 0, 1]]]

============= dot: (3, 3, 2) - (3, 2, 3) ================

shape :(3,3,3,3) -- own-data :1
---------------------

[[[[1, 3, 10]
[3, 3, 6]
[3, 3, 10]]

[[3, 9, 12]
[3, 3, 6]
[9, 3, 12]]

[[2, 6, 5]
[1, 1, 2]
[6, 1, 5]]]


[[[1, 3, 1]
[0, 0, 0]
[3, 0, 1]]

[[3, 9, 6]
[1, 1, 2]
[9, 1, 6]]

[[1, 3, 4]
[1, 1, 2]
[3, 1, 4]]]


[[[2, 6, 2]
[0, 0, 0]
[6, 0, 2]]

[[2, 6, 2]
[0, 0, 0]
[6, 0, 2]]

[[2, 6, 8]
[2, 2, 4]
[6, 2, 8]]]]

 ```

 ### N-Dimensional Matrix Transpose (C contiguous)
----
  ```c++

	
  ```
  

 ```c++
 
 ```


-----------------------