#include<iostream>
#include<cstring>

class String
{
    public:
        String();
        String(const char *str);
        String(const String &rhs);
        ~String();
		//赋值运算符重载
        String &operator=(const String &rhs);
        String operator+(const String &rhs);
        char operator[](const unsigned int index);
        bool operator==(const String &rhs);
        friend std::ostream &operator<<(std::ostream &out, const String &rhs);
    private:
        char *m_data;
};

String::String()
{
    std::cout << "default constructor" << std::endl;
    m_data = new char[1];
    m_data[0] = '\0';
}

String::String(const char *str)
{
    std::cout << "non-default constructor" << std::endl;
    if (NULL == str)
    {
        m_data = new char[1];
        m_data[0] = '\0';
    }
    else
    {
        m_data = new char[strlen(str)+1];
        strcpy(m_data, str);
    }
}

String::String(const String &another)
{
    std::cout << "copy constructor" << std::endl;
    m_data = new char[strlen(another.m_data)+1];
    strcpy(m_data, another.m_data);
}

bool String::operator==(const String &rhs)
{
    std::cout << "bool == " << std::endl;
    int result = strcmp(m_data, rhs.m_data);
    if (0 == result)
        return true;
    else
        return false;
}

String &String::operator=(const String &rhs)
{
    std::cout << "assign constructor" << std::endl;
    if (this == &rhs)
        return *this;
    delete []m_data;
    m_data = new char[strlen(rhs.m_data)+1];
    strcpy(m_data, rhs.m_data);
    return *this;
}

String String::operator+(const String &rhs)
{
    std::cout << "+" << std::endl;
    String newString;
    if (NULL == rhs.m_data)
        newString = *this;
    else if(NULL == m_data)
        newString = rhs;
    else
    {
        newString.m_data = new char[strlen(rhs.m_data)+strlen(m_data)+1];
        strcpy(newString.m_data, m_data);
        strcat(newString.m_data, rhs.m_data);
    }
    return newString;
}

char String::operator[](const unsigned int index)
{
    std::cout << "[]" << std::endl;
    return m_data[index];
}

std::ostream &operator<<(std::ostream &out, const String &rhs)
{
    out << rhs.m_data;
    return out;
}

String::~String()
{
    std::cout << "destructor" << std::endl;
    delete []m_data;
}

int main(void)
{
    const char *p = "hello, world";
    String s = "hello, world"; // 构造函数隐式转换 调用非默认构造函数
    String s1(p); // 调用非默认构造函数
    String s2 = s1; // 调用非默认构造函数
    String s3; // 调用默认构造函数
    s3 = s1; // 调用赋值构造函数
    String s4 = s3 + s1; // 调用+运算符，同时调用默认构造函数
    bool flag(s1 == s2); // 调用==运算符
    std::cout << s << std::endl;
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << flag << std::endl;
    char result = s3[1]; // 调用[]运算符
    std::cout << result << std::endl;
    std::cout << s4 << std::endl;

    return 0;
}