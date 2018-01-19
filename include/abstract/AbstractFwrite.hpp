#pragma once
#include <cstdint>
#include "Global.hpp"

DEFINE_CLASS(AbstractFwrite)
class AbstractFwrite {
public:
	virtual ~AbstractFwrite() {;}
	virtual int64_t write(void* data, int64_t size) = 0;
	virtual int64_t rel_rewind(int64_t position) = 0;
	virtual int64_t abs_rewind(int64_t position) = 0;
private:
};
