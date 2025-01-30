#include "essentials.h"
std::string createEssentials(){
	auto mainDirs = getDirs(root);
	bool isConfig = false;
	for(int i = 1; i < mainDirs.size(); ++i){
		std::string name = getName(mainDirs[i]);
		if(name == "config"){
			isConfig = true;
			break;
		}
	}
	if(!isConfig){
		for(int i = 1; i < mainDirs.size(); ++i){
			if(std::filesystem::is_directory(mainDirs[i])){
				std::string cmd = "rm -rf " + mainDirs[i];
				system(cmd.c_str()); 
 			}
		}
		std::string cmd = "touch " + root + "/config";
		system(cmd.c_str()); 
	}
	std::string configPath = root + "/config";
	std::ifstream config(configPath);
	std::string line;
	bool isDir = false;
	std::vector<std::string> projectList;
	while(std::getline(config,line))
		projectList.push_back(line);
	config.close();
	std::string index;
	for(int i = 0; i < projectList.size(); ++i){
		auto s = split(projectList[i]);
		if(s[0] == cd){
			index = s[1];
			isDir = true;
			break;
		}
	}
	if(!isDir){
		index = std::to_string(projectList.size() + 1);
		clear(configPath);
		std::ofstream config(configPath);
		for(int i = 0; i < projectList.size(); ++i)
			config << projectList[i] << std::endl;
		config << cd << ' ' << index << std::endl;
		config.close();
		std::string cmd = "mkdir " + root + "/" + index;
		system(cmd.c_str());
	}
	std::string folder = root + "/" + index;
	auto inDir = getDirs(folder);
	for(int i = 0; i < inDir.size(); ++i)
		inDir[i] = getName(inDir[i]);
	bool rebuild = false;
	for(int i = 0; i < reqFiles.size(); ++i){
		if(find(inDir,reqFiles[i]) == -1){
			rebuild = true;
			break;
		}
	}
	if(rebuild){
		inDir = getDirs(folder);
		for(int i = 1; i < inDir.size(); ++i){
			std::string cmd = "rm -rf " + inDir[i];
			system(cmd.c_str());
		}
		for(int i = 0; i < reqFiles.size(); ++i){
			std::string cmd = "touch " + folder + "/" + reqFiles[i];
			system(cmd.c_str());
		}
	}
	return folder;
}