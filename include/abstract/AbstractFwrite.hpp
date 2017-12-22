/*
 * File:   AbstractFwrite.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 17:38
 */

#ifndef ABSTRACTFWRITE_HPP
#define ABSTRACTFWRITE_HPP
#include <cstdint>
#include <memory>

class AbstractFwrite {
public:
	virtual ~AbstractFwrite() {;}
	virtual int64_t write(void* data, int64_t size) = 0;
	virtual int64_t rel_rewind(int64_t position) = 0;
	virtual int64_t abs_rewind(int64_t position) = 0;
private:
};

typedef AbstractFwrite* pAbstractFwrite;
typedef std::shared_ptr<AbstractFwrite> sAbstractFwrite;
#endif /* ABSTRACTFWRITE_HPP */
