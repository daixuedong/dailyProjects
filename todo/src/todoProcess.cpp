#include "todoProcess.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>

itemTode todoProcess::todoItem(std::string& todoStr, const std::string& path)
{
    itemTode item;
    item.raw = todoStr;

    // 默认值
    item.level = 'D';
    item.date = "9999-12-31";
    item.content = "";

    // 查找""中的内容
    size_t todoStart = todoStr.find("TODO: \"");
    if (todoStart == std::string::npos)
    {
        return item;
    }

    todoStart += 7;
    size_t todoEnd = todoStr.find("\"", todoStart);
    if (todoEnd == std::string::npos)
    {
        return item;
    }

    // 提取""中的内容
    std::string inner = todoStr.substr(todoStart, todoEnd - todoStart);

    // 使用stringstream解析
    std::stringstream iss(inner);
    std::string levelStr, date, content;

    // 读取等级
    if (iss >> levelStr && !levelStr.empty())
    {
        item.level = levelStr[0];// 取第一个值作为等级
    }

    // 读取日期
    if (iss >> date)
    {
        // 验证日期格式
        if (date.length() == 10 && date[4] == '-' && date[7] == '-')
        {
            item.date = date;
        }
        else
        {
            item.content = date;
        }
    }

    // 读取内容
    std::string remaining;
    while(iss >> remaining)
    {
        if (!item.content.empty())
        {
            item.content += " ";
        }
        item.content += remaining;
    }

    // 提取文件路径和行号
    size_t bracketStart = todoStr.find("[", todoEnd);
    size_t bracketEnd = todoStr.find("]", bracketStart);
    if (bracketStart != std::string::npos && bracketEnd != std::string::npos) 
    {
        std::string location = todoStr.substr(bracketStart + 1, bracketEnd - bracketStart - 1);
        size_t colonPos = location.rfind(":");
        if (colonPos != std::string::npos) {
            std::string fullPath = location.substr(0, colonPos);
            item.lineNum = std::stoi(location.substr(colonPos + 1));

            // 处理路径：提取相对于输入目录的部分
            // 假设 searchRoot 已经保存了输入的目录路径
            std::string relativePath = fullPath;

            // 查找 searchRoot 在 fullPath 中的位置
            size_t rootPos = fullPath.find(path);
            if (rootPos != std::string::npos) {
                // 找到搜索根目录，提取后面的部分
                relativePath = fullPath.substr(rootPos + path.length());

                // 去掉开头的斜杠
                if (!relativePath.empty() && relativePath[0] == '/') {
                    relativePath = relativePath.substr(1);
                }

                // 如果 relativePath 为空，说明就是根目录下的文件
                if (relativePath.empty()) {
                    // 提取文件名
                    size_t lastSlash = fullPath.rfind('/');
                    if (lastSlash != std::string::npos) {
                        relativePath = fullPath.substr(lastSlash + 1);
                    } else {
                        relativePath = fullPath;
                    }
                }
            } else {
                // 如果没有找到搜索根目录，只显示文件名
                size_t lastSlash = fullPath.rfind('/');
                if (lastSlash != std::string::npos) {
                    relativePath = fullPath.substr(lastSlash + 1);
                }
            }

            item.filePath = relativePath;
        }
    }

    return item;
}

void todoProcess::todoSort(const std::string& path)
{
    for (auto todo : todos)
    {
        todoItems.push_back(todoItem(todo, path)); 
    }

    if (todoItems.empty())
    {
        std::cout << "没有TODO\n";
        return;
    }

    std::sort(todoItems.begin(), todoItems.end());
    coutTode();
}

void todoProcess::coutTode()
{
    for (size_t i = 0; i < todoItems.size(); i++) {
        const auto& item = todoItems[i];
        
        // 等级图标
        std::string levelIcon;
        switch (item.level) {
            case 'A': levelIcon = "🔴 A (最高)"; break;
            case 'B': levelIcon = "🟠 B ( 高 )"; break;
            case 'C': levelIcon = "🟡 C ( 中 )"; break;
            case 'D': levelIcon = "🟢 D ( 低 )"; break;
            default:  levelIcon = "⚪ " + std::string(1, item.level);
        }
        
        // 显示 TODO 内容
        std::cout << i + 1 << ". "
                  << "[" << levelIcon << "] "
                  << "[" << item.date << "] "
                  << item.content;
        
        // 显示文件位置（缩进显示）
        if (!item.filePath.empty()) {
            std::cout << "    📍 " << item.filePath << ":" << item.lineNum << " 行" << std::endl;
        }
    }
}
