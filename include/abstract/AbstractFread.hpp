#pragma once
#include <cstdint>
#include "Global.hpp"

DEFINE_CLASS(AbstractFread)
class AbstractFread {
public:
	virtual ~AbstractFread() {;}
	virtual int64_t read(void* data, int64_t size) = 0;
	virtual int64_t seek(int64_t position) = 0;
	virtual int64_t tell() = 0;
	virtual int64_t size() = 0;
	virtual char getc() = 0;
private:
};
