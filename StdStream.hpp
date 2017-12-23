/*
 * File:   StdStream.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 17:46
 */

#ifndef STDSTREAM_HPP
#define STDSTREAM_HPP
#include "include/abstract/AbstractFread.hpp"
#include "include/abstract/AbstractFwrite.hpp"
#include <cstdio>
#include <string>
class StdStream : public AbstractFread, public AbstractFwrite {
public:
	StdStream();
	StdStream(std::string newpath, bool ro = false);
	~StdStream();
	int64_t read(void* data, int64_t size);
	int64_t seek(int64_t position);
	int64_t tell();
	int64_t size();
	int64_t write(void* data, int64_t size);
	int64_t rel_rewind(int64_t position);
	int64_t abs_rewind(int64_t position);
	char getc();
	std::string GetPath();
	void close();
	bool IsActive();
	bool open(std::string newpath, bool ro = false);

	static sAbstractFread createReader(std::string newpath);
	static sAbstractFwrite createWriter(std::string newpath);
private:
	std::string path;
	FILE* chandle;
	bool active;
};
#endif /* STDSTREAM_HPP */
