#include"httplib.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
using namespace httplib;
int main()
{
	Server svr;
	svr.Post("/api/uppercase",
		[&](const Request& req, Response& res) {
		// req 请求对象, res 响应对象

		string a = req.body;
		cout << a << endl;

		transform(a.begin(), a.end(), a.begin(), ::toupper);

		res.set_header("Access-Control-Allow-Origin", "*"); // 添加 'Access-Control-Allow-Origin' 头部，方法添加了一个 ‘Access-Control-Allow-Origin’ 头部，并设置其值为 “*”，这表示服务器允许任何源访问其资源
		res.set_content(a, "text/plain"); // 设置响应对象的content内容
		});
	svr.listen("localhost", 8080);
	return 0;
}