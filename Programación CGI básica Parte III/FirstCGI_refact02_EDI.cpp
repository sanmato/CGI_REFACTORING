#include <iostream>
#include <string>
#include <unordered_map>
#include <stdio.h>
using namespace std;

//Lucas Osacar Discovery:
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
unordered_map<string, string> generateUriMap(string uri)
{
    unordered_map<string, string> m;
    string equal = "=";
    string ampersand = "&";
    size_t pos = 0;
    string key;
    string value;
    while ((pos = uri.find(equal)) != std::string::npos)
    {
        key = uri.substr(0, pos);
        uri.erase(0, pos + equal.length());
        value = uri.substr(0,uri.find(ampersand));
        uri.erase(0, uri.find(ampersand) + ampersand.length());
        m[key]= value;
    }
    return m;
}

string urlDecode(string &src)
{
    string ret;
    char ch;
    int i, ii;
    for(i=0;i < src.length();i++)
    {
        if(int(src[i])==37)
        {
            sscanf(src.substr(i+1,2).c_str(),"%x",&ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        }
        else if (int(src[i])==43)
		{
			ch= ' ';
			ret+=ch;
        } 
        else
        {
            ret +=src[i];
        }
    }
    return (ret);
}

int main()
{
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Hello World - Second CGI Program</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";

    cout << "<form action='FirstCGI_refact02_EDI.cgi' method='post'>";
    cout << "<label>Introduzca su nombre:</label>\n";
    cout << "<input type='text' name='name'>\n";
    cout << "<label>Introduzca su apellido:</label>\n";
    cout << "<input type='text' name='surname'>\n";
    cout << "<input type='submit' name='sbmt' value='enviar'>\n";
    cout << "</form>\n";

    string str = "";
    cin >> str;
    if (str != "")
    {
        unordered_map<string,string> uriMap = generateUriMap(str);
        cout << "<h2>Hello! your name is: " << urlDecode(uriMap["name"]) << "</h2>\n";
        cout << "<h2>your surname is: " << urlDecode(uriMap["surname"]) << "</h2>\n";
    }

    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
