#include "fileCMD.hpp"
#include "todoProcess.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[])
{
    fileCMD cmd;
    todoProcess tp;

    std::string filePath; // 目录

    if (argc != 2)
    {
        std::cout << "命令错误\n";
        std::cout << "格式为：TODO <文件目录>";
    }
    
    filePath = argv[1];

    try {
        // 使用filesystem解析路径
        std::filesystem::path searchPath = std::filesystem::canonical(filePath);

        //std::cout << searchPath.string() << std::endl;

        cmd.traverse(searchPath);
        tp.todoSort(searchPath);

        // 检查是否为目录
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr<< "❌ 错误：" << e.what() << std::endl;
    }


    return 0;
}
