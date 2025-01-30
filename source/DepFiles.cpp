#include "DepFiles.h"
bool createDepfiles(const std::string& wd,
	const std::vector<std::string>& allHeaders, 
	const std::vector<std::string>& allSource)
{
	bool changeSet = false;
	auto dirs = getDirs(wd);
	for(int i = 0; i < dirs.size(); ++i){
		if(getName(dirs[i]) != "config" && !std::filesystem::is_directory(dirs[i])){
			std::ifstream file(dirs[i]);
			std::string line;
			std::getline(file, line);
			if(!exists(line)){
				changeSet = true;
				std::string cmd = "rm " + dirs[i];
				system(cmd.c_str());
			}
			file.close();
		}
	}


	for(int i = 0; i < allHeaders.size(); ++i){
		std::string file = wd + "/" + getName(allHeaders[i]);
		if(!exists(file)){
			changeSet = true;
			std::string cmd = "touch " + file;
			system(cmd.c_str());
			std::ofstream newfile(file);
			newfile << allHeaders[i] << std::endl;
			newfile << "-1" << std::endl;
			newfile.close();
		}
	}

	for(int i = 0; i < allSource.size(); ++i){
		std::string file = wd + "/" + getName(allSource[i]);
		if(!exists(file)){
			changeSet = true;
			std::string cmd = "touch " + file;
			system(cmd.c_str());
			std::ofstream newfile(file);
			newfile << allSource[i] << std::endl;
			newfile << "-1" << std::endl;
			newfile.close();
		}
	}
	return changeSet;
}