#include"include/httplib.h"
#include"include/json.hpp"
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
using namespace httplib;
using json = nlohmann::json;

int main()
{
	Server svr;
	svr.Post("/api/uppercase",
		[&](const Request& req, Response& res) {

			string a = req.body;
			// cout << a << endl;

			transform(a.begin(), a.end(), a.begin(), ::toupper);

			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_content(a, "text/plain");
		});
	svr.listen("localhost", 8080);

	return 0;
}