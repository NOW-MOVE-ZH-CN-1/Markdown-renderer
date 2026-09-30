#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


std::vector<std::string> lines;


bool load_file(const std::string& filepath)
{
    std::ifstream fin(filepath);
    if (!fin.is_open())
    {
        std::cerr << "无法打开文件：" << filepath << std::endl;
        return false;
    }
    lines.clear();
    std::string line;
    while (std::getline(fin, line))
    {
        lines.push_back(line);
    }
    fin.close();
    return true;
}


std::string parse_heading(const std::string& line)
{
    if (line.substr(0, 2) == "# ")
    {
        return "\n===== " + line.substr(2) + " =====\n";
    }
    if (line.substr(0, 3) == "## ")
    {
        return "\n--- " + line.substr(3) + " ---\n";
    }
    return line;
}


std::string parse_list(const std::string& line)
{
    if (line.substr(0,2) == "- ")
    {
        return " • " + line.substr(2);
    }
    return line;
}

// 解析 **粗体**
std::string parse_bold(const std::string& line)
{
    std::string s = line;
    size_t pos1 = 0;
    while ((pos1 = s.find("**", pos1)) != std::string::npos)
    {
        size_t pos2 = s.find("**", pos1 + 2);
        if (pos2 == std::string::npos) break;

        std::string text = s.substr(pos1+2, pos2 - pos1 -2);
        s.replace(pos1, pos2 - pos1 + 2, "【" + text + "】");
        pos1 += 3;
    }
    return s;
}


std::string render_line(const std::string& line)
{
    std::string res = parse_heading(line);
    res = parse_list(res);
    res = parse_bold(res);
    return res;
}


void render_all()
{
    for(const auto& line : lines)
    {
        std::cout << render_line(line) << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "用法：./md-renderer test.md\n";
        return 1;
    }
    if (!load_file(argv[1]))
    {
        return 1;
    }
    render_all();
    return 0;
}
