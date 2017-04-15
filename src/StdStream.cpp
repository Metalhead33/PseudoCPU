/* 
 * File:   StdStream.cpp
 * Author: metalhead33
 * 
 * Created on 2017. február 23., 17:46
 */

#include "include/StdStream.hpp"
#include "Global.hpp"
namespace Io {


StdStream::StdStream()
{
	active = false;
	path = "";
	chandle = 0;
}

StdStream::StdStream(std::string newpath, bool ro)
{
	chandle = 0;
	open(newpath,ro);
}

StdStream::~StdStream()
{
	close();
}

int64_t StdStream::read(void* data, int64_t size)
{
	if(!active) return -1;
	else return (int64_t)fread(data,1,size,chandle);
}

int64_t StdStream::seek(int64_t position)
{
	if(!active) return -1;
	else return (int64_t)fseek(chandle,position,SEEK_SET);
}

int64_t StdStream::tell()
{
	if(!active) return -1;
	else return (int64_t)ftell(chandle);
}

int64_t StdStream::size()
{
	if(!active) return -1;
	else
	{
		int64_t pos = (int64_t)ftell(chandle);
		fseek(chandle,0,SEEK_END);
		int64_t size = (int64_t)ftell(chandle);
		fseek(chandle,pos,SEEK_SET);
		return size;
	}
}

int64_t StdStream::write(void* data, int64_t size)
{
	if(!active) return -1;
	else return (int64_t)fwrite(data,1,size,chandle);
}

int64_t StdStream::rel_rewind(int64_t position)
{
	if(!active) return -1;
	else return (int64_t)fseek(chandle,position,SEEK_CUR);
}

int64_t StdStream::abs_rewind(int64_t position)
{
	if(!active) return -1;
	else return (int64_t)fseek(chandle,position,SEEK_SET);
}

std::string StdStream::GetPath()
{
	return path;
}

void StdStream::close()
{
	if(active) fclose(chandle);
	chandle = 0;
	path = "";
	active = false;
}

bool StdStream::IsActive()
{
	return active;
}

bool StdStream::open(std::string newpath, bool ro)
{
	if(chandle) fclose(chandle);
	if(ro) chandle = fopen(newpath.c_str(),"rb");
	else
	{
		chandle = fopen(newpath.c_str(),"r+b");
		if(!chandle) chandle = fopen(newpath.c_str(),"wb");
	}
	if(chandle)
	{
		path = newpath;
		active = true;
		IF_DEBUG(
		std::cout << "Succesfully opened \"" << newpath << "\".\n";
		)
		return true;
	}
	else
	{
		path = "";
		active = false;
		IF_DEBUG(
		std::cout << "Failed to open \"" << newpath << "\".\n";
		)
		return false;
	}
}
char StdStream::getc()
{
	return fgetc(chandle);
}
}
