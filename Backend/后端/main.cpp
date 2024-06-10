#include"include/httplib.h"
#include"include/json.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<cmath>
#include<algorithm>
#include<memory>

#define HashMap unordered_map

using namespace std;
using namespace httplib;
using ll = long long;
using db = double;
using json = nlohmann::json;


const enum class TYPE : int {
	// Foods
	fruits,
	vegetables,
	meat,
	snacks,
	drinks,

	// Medicines
	medicines,

	// DailyNecessities
	stationery_office_supplies,
	daily_necessities,

	// ElectronicProduct
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
	

	virtual void set_power(const db& _power) {
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
	}
};

///////////////////////////////////////




////////// Electronic Product //////////
class ElectronicProduct : public Goods {
private:
	CLASS_NAME className = CLASS_NAME::ElectronicProduct;

	db power;
	const string UNIT = "W";
public:
	ElectronicProduct(string _name, TYPE _type,
		db _price, db _stock, string _priceUnit, string _stockUnit,
		db _power,
		string _detail = "") :
		Goods(_name, _type, _price, _stock, _priceUnit, _stockUnit, _detail), power(_power) {};

	void set_power(const db& _power) override { power = _power; }
	string get_power() const override { return to_string(power) + UNIT; }

	string get_class_name() const override { return ClassName[static_cast<int>(className)]; }

	ostream& print(ostream& out) const override {
		Goods::print(out);
		out << "功率：" << get_power() << endl
		    << "描述：" << get_detail() << endl;
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
		out << "服用说明：" << get_dose() << endl
			<< "描述：" << get_detail() << endl;
	}
};

////////////////////////////////



// Json 的 key
const enum class CONFIG : int{
	name,
	type,
	className,
	price,
	priceUnit,
	stock,
	stockUnit,
	flavor,
	power,
	dose,
	detail
};

string KEYS[] = {
	"name",
	"type",
	"className",
	"price",
	"priceUnit",
	"stock",
	"stockUnit",
	"flavor",
	"power",
	"dose",
	"detail"
};
////////////////




vector<shared_ptr<Goods>>dataBase;


int main()
{
	dataBase.push_back(make_shared<Goods>(new Foods("你妈",TYPE::meat,100,100,"个","个",FLAVOR::sour,"尼姆死了")));

	Server svr;
	svr.Get("/api/ShowAllData",
		[&](const Request& req, Response& res) {
			json data;

			for (shared_ptr<Goods> item : dataBase) {
				data[1][KEYS[static_cast<int>(CONFIG::name)]] = item->get_name();
				item->print(cout) << endl;
			}


			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Content-Type", "application/json; charset=utf-8");

			string a = data.dump(-1, ' ', false, nlohmann::json::error_handler_t::replace);
			res.set_content(a, "application/json; charset=utf-8");
		});



	svr.listen("localhost", 8080);

	return 0;
}