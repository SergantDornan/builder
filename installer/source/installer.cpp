#include "installer.h"
void install(){
	auto dirs = getDirs(root);
	for(int i = 0; i < dirs.size(); ++i)
		dirs[i] = getName(dirs[i]);
	if(find(dirs, mainFolder) == -1){
		std::string fldr = root + "/" + mainFolder;
		std::string cmd = "mkdir " + fldr;
		system(cmd.c_str());
		compileBuilder(fldr);
	}
	else{
		std::cout << "================ INSTALLED ================" << std::endl;
		std::cout << std::endl;
	}
}
void uninstall(){
	std::string cmd = "rm -rf " + root + "/" + mainFolder;
	system(cmd.c_str());
}
void reinstall(){
	uninstall();
	install();
}
void compileBuilder(const std::string& path){}