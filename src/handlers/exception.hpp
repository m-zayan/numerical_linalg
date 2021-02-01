/*
 * linalg_exception.hpp
 *
 *	Author: Z. Mohamed
 */

#ifndef SRC_HANDLERS_EXCEPTION_HPP
#define SRC_HANDLERS_EXCEPTION_HPP

#include <exception>
#include <string>

namespace nd {
class exception: public std::exception {

private:
	std::string message;

public:

	explicit exception(const std::string &message);
	virtual const char* what() const throw ();

	virtual ~exception();
};
}
#endif /* HANDLERS_EXCEPTION_H_ */
