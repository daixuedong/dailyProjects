#include "fileCMD.hpp"
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

std::vector<std::string> fileCMD::todos;

void fileCMD::traverse(const std::string& files)
{
    // 遍历文件夹下的所有文件
    for (auto entry : std::filesystem::recursive_directory_iterator(files))
    {
        if (std::filesystem::is_regular_file(entry.path()))
        {
            std::string file = entry.path().string();
            // 获取扩展名
            std::string ext = entry.path().extension().string();
            TODO: "C 2026-04-24 将后缀存储到数组中";
            if (ext == ".h" || ext == ".c" || ext == ".cpp" || ext == ".hpp" || ext == ".rs")
            {
                fileOpen(file);
            }
        }
    }
}

bool fileCMD::fileOpen(const std::string& filePath)
{
    std::ifstream file = std::ifstream(filePath);
    if (!file.is_open())
        return false;
    // 查找字符

    std::string line;
    int countline = 0;

    while (std::getline(file, line))
    {
        countline++;
        // 区分大小写查找
        if (line.find("TODO: \"") != std::string::npos)
        {
            size_t todoPos = line.find("TODO: \"");
            std::string todoLine = line.substr(todoPos)+ "[" + filePath + ":" + std::to_string(countline) + "行]";
            todos.push_back(todoLine);
        }
    }

    file.close();
    return true;
}
