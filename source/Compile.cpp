#include "Compile.h"
void getIncludes(std::vector<std::string>& includes,
	const std::vector<std::string>& allHeaders,
	const std::vector<std::string>& allSource,
	const std::string& path)
{
    std::string l;
    std::ifstream input(path);
    if (input.is_open()){
  		while (std::getline(input, l)){
        	if(l.find("#include") != std::string::npos){
        		std::string s;
        		
        		for(int j = 10; j < l.size() && l[j] != '>' && l[j] != '"'; ++j)
        			s+=l[j];
        		std::string newline;
        		bool b = false;
        		for(int j = 0; j < allHeaders.size(); ++j){
        			if(find(allHeaders[j], s) != -1){
        				b = true;
        				newline = allHeaders[j];
        				break;
        			}
        		}
        		for(int j = 0; j < allSource.size(); ++j){
        			if(find(allSource[j], s) != -1){
        				b = true;
        				newline = allSource[j];
        				break;
        			}
        		}
        		if(b && find(includes, newline) == -1){
        			includes.push_back(newline);
        			getIncludes(includes,allHeaders,allSource,newline);
        		}
    		}
        }
    }
    input.close();
}
void compile(std::vector<std::string>& allHeaders, 
    std::vector<std::string>& allSource,
    bool changeSet)
{
    
}