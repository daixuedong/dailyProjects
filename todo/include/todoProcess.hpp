#ifndef TODOPROCESS_HPP
#define TODOPROCESS_HPP

#include "fileCMD.hpp"
#include <string>
#include <vector>

struct itemTode
{
    std::string raw; // 原始内容
    char level; // 等级
    std::string date; // 日期
    std::string content; // 内容
    std::string filePath;   // 文件路径
    int lineNum;            // 行号

    bool operator<(const itemTode& other) const {
        // 先按等级排序 (A > B > C > D)
        if (level != other.level) {
            return level < other.level;  // 'A' < 'B' < 'C' < 'D'
        }
         // 等级相同按日期排序
        if (date != other.date) {
            return date < other.date;
        }
        // 日期相同按文件路径排序
        if (filePath != other.filePath) {
            return filePath < other.filePath;
        }
        // 文件相同按行号排序
        return lineNum < other.lineNum;
    }
};

class todoProcess
{
public:
    todoProcess(): todos(fileCMD::todos) {};
    void todoSort(const std::string& path);

private:
    std::vector<std::string>& todos; 
    std::vector<itemTode> todoItems;
    itemTode todoItem(std::string& todoStr, const std::string& path);
    void coutTode();
};

#endif
