/*
 * sum_alg.cpp
 *
 *	Author: Z. Mohamed
 */

#include "./test_api.hpp"

std::vector<bool> is_prime;
const char *output_file = "test_api/gen_test_cases.txt";

double power2(double val) {
	return val * val;
}

template<typename T>
void print_vec1d(vec1d<T> vec) {

	std::cout << "[";

	for (max_size_t i = 0; i < vec.size() - 1; i++) {
		std::cout << vec[i] << ", ";

		if (i && i % 10 == 0)
			std::cout << ln;
	}

	std::cout << vec[vec.size() - 1] << "]\n";
}

template<typename T>
void print_vec1d(std::vector<T> vec) {
	std::cout << "[";
	for (max_size_t i = 0; i < vec.size() - 1; i++) {
		std::cout << vec[i] << ", ";

		if (i && i % 10 == 0)
			std::cout << ln;
	}
	std::cout << vec[vec.size() - 1] << "]\n";
}

void checkflow(double &val, double prop_min, double prop_max) {
	if (val <= prop_min) {
		val = 0.1;
	} else if (val >= prop_max) {
		val /= prop_max;
	}
}

void sieve(max_size_t test_size) {

	is_prime.resize(test_size + 1);

	std::fill(is_prime.begin(), is_prime.end(), 1);

	is_prime[0] = is_prime[1] = 0;

	for (max_size_t i = 2; i * i <= test_size; i++) {

		if (is_prime[i]) {
			for (max_size_t j = i * i; j < test_size; j += i) {
				is_prime[j] = 0;
			}
		}
	}
}

double exec_time_run(
		std::function<double(max_size_t, max_size_t, std::vector<double>)> sum_func,
		std::string alg_name, max_size_t begin, max_size_t end,
		std::vector<double> vec) {

	auto t_start = std::chrono::high_resolution_clock::now();

	double sum = sum_func(begin, end, vec);

	auto t_end = std::chrono::high_resolution_clock::now();

	long double time = std::chrono::duration_cast<std::chrono::milliseconds>(
			t_end - t_start).count();

	std::cout << "Execution Time of " + alg_name << " Sum :" << time << " ms"
			<< ln;

	return sum;
}

void test_api::sum_alg(max_size_t test_size) {

	if (test_size > static_cast<max_size_t>(1e8)) {
		std::cout << ("Test size greater than 10^8") << ln;
		return;
	}

	// 1.0 + 2.1 + 3.2 + 4.3 + 5.5 = 16.1
	std::vector<double> vec = { 1.0, 2.1, 3.2, 4.3, 5.5 };

	max_size_t n = vec.size();

	std::cout << "vector :";

	print_vec1d<double>(vec);

	std::cout << "\n========================\n";

	double sum1 = algorithm::naive_summation<double>(0, n, vec);
	double sum2 = algorithm::kahan_summation<double>(0, n, vec);
	double sum3 = algorithm::shift_reduce_sum<double>(0, n, vec);
	double sum4 = algorithm::pairwise_selection_sum<double>(0, n, vec);

	std::cout << "naive_summation :" << sum1 << ln;
	std::cout << "kahan_summation :" << sum2 << ln;
	std::cout << "shift_reduce_sum :" << sum3 << ln;
	std::cout << "pairwise_selection_sum :" << sum4 << ln;

	std::cout << "========================\n";

	// skip indices, 0, n-2 = 4

	// 2.1 + 3.2 + 4.3 = 9.6
	double sum = algorithm::shift_reduce_sum<double>(1, n - 1, vec);

	std::cout << "shift_reduce_sum - in range [1, 4)  :" << sum << ln;

	std::cout << "========================\n";
	// ================= Test apply_in_range ================

	vec1d<double> vec2 = { 1, 2, 3, 4, 5 };
	max_size_t n2 = vec2.size();

	std::cout << "apply_in_range vec1d: \n";

	std::cout << "------------------------\nvector :";

	print_vec1d<double>(vec2);

	// double power2(double val){}
	vec2.apply_in_range(0, n2, power2);

	std::cout << "vector^2 :";

	print_vec1d<double>(vec2);

	std::cout << "========================\n";

	// ================ Test Error Reduction ========================

	std::cout << "############# Test ############\n";

	double start = M_PI * sqrt(2);
	double H = 1e6; // 10^6 * test_size < MAX_DOUBLE_VALUE

	std::vector<double> vec3(test_size, start);

	sieve(test_size); // fill prime index - indicator

	srand(42); // seed

	// Generate test
	for (max_size_t i = 0; i < test_size - 1; i++) {

		vec3[i] += i;

		if (is_prime[i]) {
			vec3[i] = static_cast<double>(rand())
					/ (static_cast<double>(RAND_MAX / (H)));
		}
	}

	std::cout << "\n========================\n";

	double s1 = exec_time_run(algorithm::naive_summation<double, double>,
			"Naive", 0, test_size, vec3);

	double s2 = exec_time_run(algorithm::kahan_summation<double, double>,
			"Kahan", 0, test_size, vec3);

	double s3 = exec_time_run(algorithm::pairwise_summation<double, double>,
			"Pairwise", 0, test_size, vec3);

	double s4 = exec_time_run(algorithm::shift_reduce_sum<double, double>,
			"Shift Reduce", 0, test_size, vec3);

	double s5 = exec_time_run(algorithm::pairwise_selection_sum<double, double>,
			"Pairwise Selection", 0, test_size, vec3);

	std::cout << "========================\n";

	std::cout << "absolute - difference :" << ln;
	std::cout << "------------------------\n";

	std::cout << "kahan - naive : " << abs(s2 - s1) << ln;
	std::cout << "pairwise - naive : " << abs(s3 - s1) << ln;
	std::cout << "shift_reduce_sum - naive : " << abs(s4 - s1) << ln;
	std::cout << "pairwise_selection_sum - naive : " << abs(s5 - s1) << ln;

	std::cout << "========================\n";

	std::cout << "summation - result:" << ln;
	std::cout << "------------------------\n";

	std::cout << "naive : " << s1 << ln;
	std::cout << "kahan : " << s2 << ln;
	std::cout << "pairwise : " << s3 << ln;
	std::cout << "shift_reduce_sum : " << s4 << ln;
	std::cout << "pairwise_selection_sum : " << s5 << ln;

	std::cout << "========================\n";

	std::cout << "Generated Test Case - TXT - File :" << output_file << ln;

	std::cout << "========================\n";

	auto f = freopen(output_file, "w", stdout);

	print_vec1d(vec3);

	fclose(f);
}
