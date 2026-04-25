#ifndef FILECMD_HPP
#define FILECMD_HPP

#include <string>
#include <vector>

class fileCMD
{
public:
    // 存储有TODO的行
    static std::vector<std::string> todos;
    void traverse(const std::string& files);
    static std::vector<std::string> getTodos() { return todos; }
private:
    bool fileOpen(const std::string& filePath);
};


#endif
