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
