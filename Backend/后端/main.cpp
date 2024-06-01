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
		// req �������, res ��Ӧ����

		string a = req.body;
		cout << a << endl;

		transform(a.begin(), a.end(), a.begin(), ::toupper);

		res.set_header("Access-Control-Allow-Origin", "*"); // ��� 'Access-Control-Allow-Origin' ͷ�������������һ�� ��Access-Control-Allow-Origin�� ͷ������������ֵΪ ��*�������ʾ�����������κ�Դ��������Դ
		res.set_content(a, "text/plain"); // ������Ӧ�����content����
		});
	svr.listen("localhost", 8080);
	return 0;
}