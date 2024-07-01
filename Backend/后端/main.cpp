#include"include/httplib.h"
#include"include/json.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<set>
#include<map>
#include<cmath>
#include<algorithm>
#include<memory>
#include<Windows.h>
#include <functional>

#define HashMap unordered_map
#define fa(i,op,n) for(int i=op;i<=n;i++)

using namespace std;
using namespace httplib;
using ll = long long;
using db = double;
using json = nlohmann::json;


const enum class TYPE : int {
	// Foods(0 ~ 4)
	fruits,
	vegetables,
	meat,
	snacks,
	drinks,

	// Medicines(5)
	medicines,

	// DailyNecessities(6 ~ 7)
	stationery_office_supplies,
	daily_necessities,

	// ElectronicProduct(8)
	electronic_product
};

string Type[] = {
	// Foods
	"水果",
	"蔬菜",
	"肉",
	"零食",
	"饮料",

	// Medicines
	"药品",

	// DailyNecessities
	"办公用品",
	"日用品",

	// ElectronicProduct
	"电子产品"
};


const enum class CLASS_NAME : int {
	Foods,
	Medicines,
	DailyNecessities,
	ElectronicProduct,
};

string ClassName[] = {
	"Foods", "Medicines","DailyNecessities", "ElectronicProduct"
};


const enum class FLAVOR : int {
	sour,
	sweet,
	bitter,
	spicy,
	salty
};


string Flavor[] = {
	"酸","甜","苦","辣","咸"
};


class Base {
public:
	virtual ostream& print(ostream& out) const = 0;
};

ostream& operator<<(ostream& out, const Base& a) {
	return a.print(out);
}


class Goods : public Base {
public:
	Goods(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		string _detail = "") :
		name(_name), type(_type),
		price(_price), stock(_stock), priceUnit(_priceUnit), stockUnit(_stockUnit),
		detail(_detail) {};

	void set_price(const db& p) { price = p; }
	db get_price()const { return price; }

	void set_stock(const db& s) { stock = s; }
	db get_stock()const { return stock; }

	void set_priceUnit(const string& u) { priceUnit = u; }
	string get_priceUnit()const { return priceUnit; }

	void set_stockUnit(const string& u) { stockUnit = u; }
	string get_stockUnit()const { return stockUnit; }

	void set_detail(const string& d) { detail = d; }
	string get_detail()const { return detail; }

	void set_type(const TYPE& _type) { type = _type; }
	string get_type() const { return Type[static_cast<int>(type)]; }

	void set_name(const string& _name) { name = _name; }
	string get_name() const { return name; }


	ostream& print(ostream& out) const override {
		out << "种类：" << get_type() << endl
			<< "名称：" << get_name() << endl
			<< "价格：" << get_price() << ' ' << get_priceUnit() << endl
			<< "存货量：" << get_stock() << ' ' << get_stockUnit() << endl;
		return out;
	};

	virtual string get_class_name() const {
		cerr << "Warning：It is Goods" << endl;
		return "";
	}


	virtual void set_flavor(const FLAVOR& _flavor) {
		cerr << "Warning：It is Goods" << endl;
		return;
	}
	virtual string get_flavor() const {
		cerr << "Warning：It is Goods" << endl;
		return "";
	}


	virtual void set_power(const int& _power) {
		cerr << "Warning：It is Goods" << endl;
		return;
	}
	virtual string get_power() const {
		cerr << "Warning：It is Goods" << endl;
		return "";
	}

	virtual void set_dose(const int& _dose) {
		cerr << "Warning：It is Goods" << endl;
		return;
	}
	virtual string get_dose() const {
		cerr << "Warning：It is Goods" << endl;
		return "";
	}

private:
	db price, stock;
	string priceUnit, stockUnit; // 价格单位，存货量单位
	string name;
	string detail;
	TYPE type;
};



////////// FOODS //////////


class Foods : public Goods {
private:
	CLASS_NAME className = CLASS_NAME::Foods;

	FLAVOR flavor;
public:
	Foods(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		FLAVOR _f,
		string _detail = "") :
		Goods(_name, _type, _price, _stock, _priceUnit, _stockUnit, _detail), flavor(_f) {};

	void set_flavor(const FLAVOR& _flavor) override { flavor = _flavor; }
	string get_flavor() const override { return Flavor[static_cast<int>(flavor)]; }

	string get_class_name() const override { return ClassName[static_cast<int>(className)]; }

	ostream& print(ostream& out) const override {
		Goods::print(out);
		out << "味道：" << get_flavor() << endl
			<< "描述：" << get_detail() << endl;
		return out;
	}
};

///////////////////////////




////////// Daily Necessities //////////
class DailyNecessities : public Goods {
private:
	CLASS_NAME className = CLASS_NAME::DailyNecessities;

public:
	DailyNecessities(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		string _detail = "") :
		Goods(_name, _type, _price, _stock, _priceUnit, _stockUnit, _detail) {};


	string get_class_name() const override { return ClassName[static_cast<int>(className)]; }

	ostream& print(ostream& out) const override {
		Goods::print(out);
		out << "描述：" << get_detail() << endl;
		return out;
	}
};

///////////////////////////////////////




////////// Electronic Product //////////
class ElectronicProduct : public Goods {
private:
	CLASS_NAME className = CLASS_NAME::ElectronicProduct;

	int power;
	const string UNIT = "W";
public:
	ElectronicProduct(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		int _power,
		string _detail = "") :
		Goods(_name, _type, _price, _stock, _priceUnit, _stockUnit, _detail), power(_power) {};

	void set_power(const int& _power) override { power = _power; }
	string get_power() const override { return to_string(power) + UNIT; }

	string get_class_name() const override { return ClassName[static_cast<int>(className)]; }

	ostream& print(ostream& out) const override {
		Goods::print(out);
		out << "功率：" << get_power() << endl
			<< "描述：" << get_detail() << endl;
		return out;
	}
};

////////////////////////////////////////




////////// Medicines //////////
class Medicines : public Goods {
private:
	CLASS_NAME className = CLASS_NAME::Medicines;

	int dose;
	const string UNIT = "次一天";
public:
	Medicines(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		int _dose,
		string _detail = "") :
		Goods(_name, _type, _price, _stock, _priceUnit, _stockUnit, _detail), dose(_dose) {};

	void set_dose(const int& _dose) override { dose = _dose; }
	string get_dose() const override { return to_string(dose) + UNIT; }

	string get_class_name() const override { return ClassName[static_cast<int>(className)]; }

	ostream& print(ostream& out) const override {
		Goods::print(out);
		out << "用量：" << get_dose() << endl
			<< "描述：" << get_detail() << endl;
		return out;
	}
};

////////////////////////////////



// Json 的 key
const enum class CONFIG : int {
	name,
	type,
	className, // 2
	price,
	stock,
	flavor,
	power,
	dose,
	detail
}; // 0 ~ 8

string KEYS[] = {
	"名称",
	"类型",
	"className",
	"价格",       // price + priceUnit
	"存货量",     // stock + stockUnit
	"味道",
	"功率",
	"用量",
	"描述"
};
////////////////



ll dbKey = 1; // 数据id
map<ll, shared_ptr<Goods>>dataBase;


class API {
private:
	Server* svr;

	vector<function<void(void)>> apis{


		// 显示数据
		[&](void)->void { 
			svr->Options("/api/ShowData", [&](const Request& req, Response& res) {
				//cout << "OPTIONS ACCESS" << endl;
				res.status = 200;
			});


			svr->Post("/api/ShowData",
				[&](const Request& req, Response& res) {

					json reqData = json::parse(req.body);

					int CN = reqData["_value"] - 1; // 前端请求显示的 ClassName 类别

					json data;

					int id = 0; // 第几个数据

					cout << "前端查询了以下数据：" << endl << endl;

					for (auto [_, item] : dataBase) {

						if (item->get_class_name() != ClassName[CN] and CN != -2)continue;  // CN == -2 : 全部

						int now = 0; // 保证顺序正确


						data[id][now++] = { "id", _ };
						data[id][now++] = { KEYS[int(CONFIG::name)], item->get_name() };
						data[id][now++] = { KEYS[int(CONFIG::type)], item->get_type() };
						data[id][now++] = { KEYS[int(CONFIG::price)], item->get_price(), item->get_priceUnit() };
						data[id][now++] = { KEYS[int(CONFIG::stock)], item->get_stock(), item->get_stockUnit() };

						if (item->get_class_name() == ClassName[(int)CLASS_NAME::Foods]) {
							data[id][now++] = { KEYS[(int)CONFIG::flavor], item->get_flavor() };
						}

						if (item->get_class_name() == ClassName[(int)CLASS_NAME::Medicines]) {
							data[id][now++] = { KEYS[(int)CONFIG::dose], item->get_dose() };
						}

						if (item->get_class_name() == ClassName[(int)CLASS_NAME::ElectronicProduct]) {
							data[id][now++] = { KEYS[(int)CONFIG::power], item->get_power() };
						}

						data[id][now++] = { KEYS[(int)CONFIG::detail], item->get_detail() };

						id++;

						item->print(cout) << endl;
					}

					string a = data.dump(-1, ' ', false, nlohmann::json::error_handler_t::replace);
					res.set_content(a, "application/json; charset=utf-8");
				});

		},


		// 删除数据
		[&](void)->void { 
			svr->Options("/api/DeleteData", [&](const Request& req, Response& res) {
				//cout << "OPTIONS ACCESS" << endl;
				res.status = 200;
			});


			svr->Post("/api/DeleteData", [&](const Request& req, Response& res) {

				json reqData = json::parse(req.body);

				cout << "前端删除了以下数据：" << endl << endl;

				for (int i : reqData["id"]) {
					dataBase[i]->print(cout) << endl;

					dataBase.erase(i);
				}
			});
		},


		// 导入数据
		[&](void)->void {
			svr->Options("/api/ImportData", [&](const Request& req, Response& res) {
				//cout << "OPTIONS ACCESS" << endl;
				res.status = 200;
			});


			svr->Post("/api/ImportData", [&](const Request& req, Response& res) {

				json reqData = json::parse(req.body);

				int type = reqData["type"]; // 类型

				string name = reqData["name"];
				db price = reqData["price"];
				db stock = reqData["stock"];
				string priceUnit = reqData["priceUnit"];
				string stockUnit = reqData["stockUnit"];
				string detail = reqData["detail"];

				cout << "前端导入了以下数据：" << endl << endl;

				if (type >= 1 and type <= 5) {
					FLAVOR flavor = FLAVOR(reqData["flavor"] - 1);
					dataBase[dbKey] = make_shared<Foods>(Foods(name, (TYPE)type, price, stock, priceUnit, stockUnit, flavor, detail));
				}
				else if (type == 6) {
					int dose = reqData["dose"];
					dataBase[dbKey] = make_shared<Medicines>(Medicines(name, (TYPE)type, price, stock, priceUnit, stockUnit, dose, detail));
				}
				else if (type >= 7 and type <= 8) {
					dataBase[dbKey] = make_shared<DailyNecessities>(DailyNecessities(name, (TYPE)type, price, stock, priceUnit, stockUnit, detail));
				}
				else if (type == 9) {
					int power = reqData["power"];
					dataBase[dbKey] = make_shared<ElectronicProduct>(ElectronicProduct(name, (TYPE)type, price, stock, priceUnit, stockUnit, power, detail));
				}

				dbKey++;

				dataBase[dbKey - 1]->print(cout) << endl;
			});
		},
	};

public:
	API(Server* svr) :svr(svr) {};

	void all_start() {
		for (auto& api : apis)
			api();
	}
};



int main()
{
	SetConsoleOutputCP(CP_UTF8);

	dataBase[dbKey++] = make_shared<Foods>("猪肉", TYPE::meat, 15, 100, "元/斤", "斤", FLAVOR::sour, "新鲜猪里脊");
	dataBase[dbKey++] = make_shared<DailyNecessities>("笔", TYPE::daily_necessities, 1, 100, "元/支", "支", "黑色笔");
	dataBase[dbKey++] = make_shared<ElectronicProduct>("电水壶", TYPE::electronic_product, 100, 100, "元/个", "个", 100, "烧热水的");


	Server svr;
	Server* svrPtr = &svr;

	svr.set_default_headers({  // 设置头部
		{ "Access-Control-Allow-Origin", "*" },
		{ "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS" },
		{ "Access-Control-Allow-Headers", "*" },
		{ "Access-Control-Max-Age", "3600" },
		{ "Content-Type", "application/json;charset=utf-8" }
		});


	API api(svrPtr);
	api.all_start();

	svr.listen("localhost", 8080);

	return 0;
}