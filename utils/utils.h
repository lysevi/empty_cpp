#pragma once

#include <string>
#include <list>

#include <boost/filesystem.hpp>

#define NOT_IMPLEMENTED throw std::logic_error("Not implemented");

namespace utils {

    class NonCopy {
    private:
        NonCopy(const NonCopy&) = delete;
        NonCopy& operator=(const NonCopy&) = delete;
    protected:
        NonCopy() = default;
    };
	
    std::list<boost::filesystem::path> ls(const std::string& path);
	std::list<boost::filesystem::path> ls(const std::string& path, const std::string& ext);
    bool rm(const std::string&rm_path);
	std::string filename(std::string fname); //without ex
	std::string parent_path(std::string fname);

	template<typename T>
	bool inInterval(T from, T to, T value) {
		return value >= from && value <= to;
	}
}
