#include "utils.h"
#include "ProcessLogger.h"

std::list<boost::filesystem::path> utils::ls(const std::string& path){
    std::list<boost::filesystem::path> result;

    std::copy(boost::filesystem::directory_iterator(path),
              boost::filesystem::directory_iterator(),
              std::back_inserter(result));

    return result;
}

std::list<boost::filesystem::path> utils::ls(const std::string& path, const std::string& ext) {
	std::list<boost::filesystem::path> result;

	std::copy(boost::filesystem::directory_iterator(path),
			  boost::filesystem::directory_iterator(),
			  std::back_inserter(result));

	// ext filter
	result.remove_if([&ext](boost::filesystem::path p){return p.extension().string() != ext;});

	return result;
}

bool utils::rm(const std::string&rm_path){
    if(!boost::filesystem::exists(rm_path))
        return true;
	try {
		boost::filesystem::path path_to_remove(rm_path);
		for (boost::filesystem::directory_iterator end_dir_it, it(path_to_remove); it != end_dir_it; ++it) {
			if (!boost::filesystem::remove_all(it->path())) {
				return false;
			}
		}
		boost::filesystem::remove_all(rm_path);
		return true;
	} catch (boost::filesystem::filesystem_error& ex) {
		std::string msg = ex.what();
		logger << "utils::rm exception: " << msg;
		throw;
	}
}

//without ex
std::string utils::filename(std::string fname) {
	boost::filesystem::path p(fname);
	return p.stem().string();
}


std::string utils::parent_path(std::string fname) {
	boost::filesystem::path p(fname);
	
	return p.parent_path().string();
}