#include "essentials.h"
#include "DepFiles.h"
#include "Compile.h"
int main(int argc, char* argv[]){
	std::vector<std::string> allHeaders, allSource;
	getAllheaders(allHeaders,cd);
	getAllsource(allSource,cd);
	// std::string wd = createEssentials();
	// bool changeSet = createDepfiles(wd, allHeaders, allSource);
	compile(allHeaders,allSource,changeSet);
    return 0;
}