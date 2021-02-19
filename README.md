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

### N-Dimensional Matrix Allocation (C contiguous)
----

```c++

shape_t shape = { 3, 3, 3 };

nd::matrix<int> mat = nd::random::uniform<int>(1, 3, shape); // low = 1, high = 3

std::cout << "shape :" << mat.shape() << ln;
std::cout << "Chunk storage size :" << mat.size() << ln;

std::cout << "=======================\n";
nd::out::print_matrix(mat);

std::cout << "\n========== matrix[0] ============\n";
nd::out::print_matrix(mat[0]);

std::cout << "========== matrix[0][1] ============\n";
nd::out::print_matrix(mat[0][1]);

std::cout << "\n========== matrix[1] ============\n";
nd::out::print_matrix(mat[1]);

std::cout << "========== matrix[1][2] ============\n";
nd::out::print_matrix(mat[1][2]);

std::cout << "\n========== matrix[2] ============\n";
nd::out::print_matrix(mat[2]);

std::cout << "========== matrix[2][3] ============\n";
nd::out::print_matrix(mat[2][2]);

std::cout << "\n========== Updated: op: diag(matrix) = 0 ============\n";

for (max_size_t i = 0; i < 3; i++) {
	for (max_size_t j = 0; j < 3; j++) {
		mat.assign( { i, j, j }, 0);
	}
}

nd::out::print_matrix(mat);

std::cout << "\n============ op: div =========\n";

mat /= 1;
nd::out::print_matrix(mat / 2);

std::cout << "\n============ op: mul =========\n";

mat *= 2;
nd::out::print_matrix(mat * mat * 2);

std::cout << "\n============ op: sub =========\n";

mat -= 2;
nd::out::print_matrix(mat);

std::cout << "\n============ op: add =========\n";

mat += 2;
nd::out::print_matrix(mat);

std::cout << "\n============ op: euqal =========\n";

std::cout << (mat == mat) << ", " << (mat == (mat + 1)) << '\n';

std::cout << "\n============ op: mask =========\n";

nd::out::print_matrix(mat == 2);

std::cout << "\n========== [1]: Identity - {3, 3} =======\n";

shape_t shape0 = { 3, 3 };
nd::matrix<int> mat0 = nd::linalg::eye<int>(shape0);

nd::out::print_matrix(mat0);

std::cout << "\n========== [2]: Diag(matrix) = 3 - {3, 3} =======\n";

shape_t shape1 = { 3, 3 };
nd::matrix<int> mat1 = nd::linalg::eye<int>(shape1);

mat1 *= 3;

nd::out::print_matrix(mat1);

std::cout << "\n========== Stack [1], [2] =======\n";

nd::matrix<int> result = nd::stack<int>( { mat0, mat1 });

nd::out::print_matrix(result);

```

-----------------------

### N-Dimensional Matrix Multiplication (C contiguous)
----
```c++

nd::matrix<int> mat1 = nd::random::uniform<int>(1, 10, { 3, 3, 2 });

nd::matrix<int> mat2 = nd::random::uniform<int>(1, 10, { 2, 4 });

std::cout << "=============== (3, 3, 2) ================\n";

nd::out::print_matrix(mat1);

std::cout << "=============== (2, 4) ================\n";

nd::out::print_matrix(mat2);

std::cout << "============= matmul: (3, 3, 2) - (2, 4) ================\n";

nd::matrix<int> result = nd::linalg::matmul<int>(mat1, mat2);

std::cout << "shape :" << result.shape() << " -- own-data :"
	<< result.own_data() << ln;

std::cout << "---------------------\n";

nd::out::print_matrix(result);

```
 
-----------------------

### N-Dimensional Matrix Dot Product (C contiguous)
----
  ```c++

nd::matrix<int> mat1 = nd::random::uniform<int>(0, 3, { 3, 3, 2 });

nd::matrix<int> mat2 = nd::random::uniform<int>(0, 3, { 3, 2, 3 });

std::cout << "=============== (3, 3, 2) ================\n";

nd::out::print_matrix(mat1);

std::cout << "=============== (3, 2, 3) ================\n";

nd::out::print_matrix(mat2);

std::cout << "============= dot: (3, 3, 2) - (3, 2, 3) ================\n";

nd::matrix<int> result = nd::linalg::dot<int>(mat1, mat2);

std::cout << "shape :" << result.shape() << " -- own-data :"
	<< result.own_data() << ln;

std::cout << "---------------------\n";

nd::out::print_matrix(result);

```


 ### N-Dimensional Matrix Transpose (C contiguous)
----
  ```c++

shape_t shape0 = { 3, 2 };
nd::matrix<int> mat0 = nd::random::uniform<int>(0, 5, shape0);

std::cout << "shape :" << mat0.shape() << ", own_data: " << mat0.own_data()
		<< ln;
std::cout << "------------\n";

nd::out::print_matrix(mat0);

//  nd::linalg::transpose<T>(nd::matrix<T> mat, axes = {...})
nd::matrix<int> result0 = nd::linalg::transpose<int>(mat0, { 1, 0 });

std::cout << "\n\n=========== transposed, axes = {1, 0} ==============\n";

std::cout << "shape :" << result0.shape() << ", own_data: "
		<< result0.own_data() << ln;

std::cout << "\n------------\n";

nd::out::print_matrix(result0);

std::cout << "\n\n==============================\n";

shape_t shape = { 3, 2, 2, 2 };

nd::matrix<int> mat = nd::random::uniform<int>(0, 5, shape);

std::cout << "shape :" << mat.shape() << ", own_data :" << mat.own_data()
		<< ln;

std::cout << "\n------------\n";
std::cout << "data : ";

nd::out::_h::print_vec1d(mat._m_begin(), 0, mat.size());

std::cout
		<< "\n\n============ transposed, axes = { 3, 0, 1, 2 } =============\n";

nd::matrix<int> result = nd::linalg::transpose<int>(mat, { 3, 0, 1, 2 });

std::cout << "shape :" << result.shape() << ", own_data :"
		<< result.own_data() << ln;

std::cout << "\n------------\n";
std::cout << "data : ";

nd::out::_h::print_vec1d(result._m_begin(), 0, result.size());

std::cout << "\n=================================\n";
	
```
  

 ```c++

shape :(3,2), own_data: 1
------------
[[5, 3]
[3, 3]
[3, 5]]


=========== transposed, axes = {1, 0} ==============
shape :(2,3), own_data: 1

------------
[[5, 3, 3]
[3, 3, 5]]


==============================
shape :(3,2,2,2), own_data :1

------------
data : [0, 0, 4, 0, 4, 4, 3, 1, 3, 4, 4, 4, 2, 1, 2, 4, 2, 1, 2, 5, 0, 1, 2, 3]

============ transposed, axes = { 3, 0, 1, 2 } =============
shape :(2,3,2,2), own_data :1

------------
data : [0, 4, 4, 3, 3, 4, 2, 2, 2, 2, 0, 2, 0, 0, 4, 1, 4, 4, 1, 4, 1, 5, 1, 3]
=================================
 ```


-----------------------