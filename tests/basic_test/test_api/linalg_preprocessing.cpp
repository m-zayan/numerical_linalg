/*
 * linalg_preprocessing.cpp
 *
 *      Author: Z. Mohamed
 */

#include "./test_api.hpp"

void test0(nd::matrix<double> mat) {

	uflag8_t state;

	max_size_t ccols = 3;

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	nd::matrix<double, false> mview = mat.op_view_2d();

	nd::iterator::Iterator *it = nd::iterator::init_iterator(mview._m_coords());

	// forward
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, false);

	nd::out::print_matrix(mat);

	std::cout << "\n-----------------------\n";

	std::cout << "state : " << static_cast<min_t>(state) << ln;

	std::cout << "\n===============================\n";
}

void test1(nd::matrix<double> mat) {

	uflag8_t state;

	max_size_t ccols = 3;

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	nd::matrix<double, false> mview = mat.op_view_2d();

	nd::iterator::Iterator *it = nd::iterator::init_iterator(mview._m_coords());

	// forward ---> backward
	BITER_ROTATE(it);

	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, false);

	nd::out::print_matrix(mat);

	std::cout << "\n-----------------------\n";

	std::cout << "state : " << static_cast<min_t>(state) << ln;
}

void test2(nd::matrix<double> mat) {

	uflag8_t state;

	max_size_t ccols = 3;

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";

	nd::matrix<double, false> mview = mat.op_view_2d();

	nd::iterator::Iterator *it = nd::iterator::init_iterator(mview._m_coords());

	// forward
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, true);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, true);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, true);

	std::cout << "state : " << static_cast<min_t>(state) << ln;

	std::cout << "\n-----------------------\n";

	// forward ---> backward
	BITER_ROTATE(it);

	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, false);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, false);

	nd::out::print_matrix(mat);

	std::cout << "\n-----------------------\n";

	std::cout << "state : " << static_cast<min_t>(state) << ln;
}

void test3(nd::matrix<double> mat) {

	uflag8_t state;

	max_size_t ccols = 3;

	nd::out::print_matrix(mat);

	std::cout << "\n===============================\n";
	nd::matrix<double> mcopy = mat.op_view_2d();

	nd::matrix<double, false> mview = mat.op_view_2d();

	nd::matrix<double> inv = nd::linalg::eye<double>(mview.shape());

	nd::iterator::Iterator *it = nd::iterator::init_iterator(mview._m_coords());

	// forward
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, true, &inv);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, true, &inv);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, true, &inv);

	std::cout << "state : " << static_cast<min_t>(state) << ln;

	std::cout << "\n-----------------------\n";

	// forward ---> backward
	BITER_ROTATE(it);

	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 0, false,
			&inv);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 1, false,
			&inv);
	state = nd::linalg::inplace::gsubstitution_step(mview, it, ccols, 2, false,
			&inv);

	nd::out::print_matrix(mat);

	std::cout << "\n-----------------------\n";

	std::cout << "state : " << static_cast<min_t>(state) << ln;

	std::cout << "\n===============================\n";

	std::cout << "inverse-matrix\n--------------\n";

	nd::out::print_matrix(inv);

	std::cout << "\n-----------------------\n";

	nd::matrix<double> mminv = nd::linalg::matmul<double>(mcopy[0], inv[0]);

	nd::out::print_matrix(mminv);
}

void test_api::linalg_preprocessing() {

	shape_t s = { 3, 3 };

	nd::matrix<double> mat = nd::random::uniform(1, 10, s);
	nd::matrix<double> S = nd::linalg::matmul<double>(mat,
			mat.permute( { 1, 0 }));

	test3(S);
}

