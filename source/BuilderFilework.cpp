#include "BuilderFilework.h"
const std::string root = getHomedir() + "/builder";
const std::string cd = cwd();
std::string cwd(){
	char cwd0[PATH_MAX];
    if (getcwd(cwd0, sizeof(cwd0)) != nullptr) {
    	return cwd0;
    } 
    else {
    	std::cout << "==================== ERROR ====================" << std::endl;
    	std::cout << "====== some error in install.cpp : std::string cwd() ======";
    	std::cout << std::endl;
    	return "";
    }
}
std::string getName(const std::string& path){
    for(int i = path.size() - 1; i >= 0; --i){
        if(path[i] == '/')
            return std::string(path.begin() + i + 1, path.end()); 
    }
    return "";
}
std::string getFolder(const std::string& path){
    for(int i = path.size() - 1; i >= 0; --i){
        if(path[i] == '/')
            return std::string(path.begin(), path.begin() + i);
    }
    return "";
}
void getAllheaders(std::vector<std::string>& headers,const std::string& path){
    auto dirs = getDirs(path);
    for(int i = 1; i < dirs.size(); ++i){
        if(dirs[i][dirs[i].size()-2] == '.' && dirs[i][dirs[i].size()-1] == 'h' && find(headers, dirs[i]) == -1)
            headers.push_back(dirs[i]);
        if(std::filesystem::is_directory(dirs[i]))
            getAllheaders(headers, dirs[i]);
    }
    merge_sort(headers);
}
void getAllsource(std::vector<std::string>& source, const std::string& path){
    auto dirs = getDirs(path);
    for(int i = 1; i < dirs.size(); ++i){
        int index = -1;
        for(int j = dirs[i].size()-1; j>=0; --j){
            if(dirs[i][j] == '.' && j != 0){
                index = j;
                break;
            }
        }
        if(index != -1){
            std::string ext(dirs[i].begin() + index + 1,dirs[i].end());
            if(find(source, dirs[i]) == -1 && (ext == "cpp" || ext == "c"))
                source.push_back(dirs[i]);
        }
        if(std::filesystem::is_directory(dirs[i]))
            getAllsource(source, dirs[i]);
    }
    merge_sort(source);
}
std::string getHomedir(){
    const char* homeDir = getenv("HOME");
    if (homeDir) {
        return homeDir;
    } else {
        std::cout << "======================== ERROR ========================" << std::endl;
        std::cout << "==== some error in BuilderFilework.cpp: getHomedir() ====" << std::endl;
        std::cout << std::endl;      
        return "";
    }
}
bool exists(const std::string& path){
    return std::filesystem::exists(path);
}
void appendToFile(const std::string& path, const std::string& s){
    std::ofstream out(path, std::ios::app);
    if(out.is_open()){
        out << s;
        out.close();
    }
    else{
        std::cout << "============================ ERROR ============================" << std::endl;
        std::cout << "======= BuilderFilework.cpp: appendToFile() ======" << std::endl;
        std::cout << "Cannot open file: " << path << std::endl;
        std::cout << std::endl;
    }
}
std::string formatTime(time_t timestamp) {
    std::tm *timeInfo = localtime(&timestamp);
    if (timeInfo == nullptr) {
        std::cout << "===================== ERROR =====================" << std::endl;
        std::cout << "====== BuilderFilework.cpp: formatTime() - some error idn ======" << std::endl;
        std::cout << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
std::string getChangeTime(const std::string& path){
    const char *filename = path.c_str();
    struct stat fileInfo;
    if (stat(filename, &fileInfo) != 0) {
        std::cout << "===================== ERROR =====================" << std::endl;
        std::cout << "====== BuilderFilework.cpp: getChangeTime() ======" << std::endl;
        std::cout << "Error getting file information: " << filename << std::endl;
        std::cout << std::endl;
        return "";
    }
    time_t modificationTime = fileInfo.st_mtime;
    return formatTime(modificationTime);
}