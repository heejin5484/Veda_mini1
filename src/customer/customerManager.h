#pragma once
#include <unordered_map>
#include "Observer.h"
#include "customer.h"
using namespace std;


class customerManager : public Observer{
private :
	
	static customerManager* instance;

	customerManager() : userCount(0) {};
	customerManager(const customerManager&) = delete;
	customerManager& operator=(const customerManager&) = delete;

	unordered_map<string, Customer> customermap;

	int userCount;

	const string filepath = "./data/customersList.csv";

public :
	static customerManager* getInstance();
	void getRegisteredUsers();
	int getuserCount() { return userCount;}

	Customer* getCustomer(string id) {
		return &customermap[id];
	}

	void update(const string& userId, const string& productName, int quantity) override {
		customermap[userId].updateTotalPurchase(quantity);
		updateUserInfo(customermap[userId]);
	}

	void showManageSystem();

	bool Login(const string& id, const string& pwd);
	bool registerUser(); // 회원가입
	void deleteUser(Customer& customer); // customermap 에서 유저 정보 삭제, txt파일에 업데이트 
	void addUser(Customer& customer);

	void showUserList(); // customermap 전부 출력 (sorting 기준 (totalpurchase 순, 이름순.. ?) 세울지)
	void showUserInfo(Customer& customer); // user 한명 정보 보기 (id / pw / 이름 / 성별 / 전화번호 / 주소 / 총구매금액 ) 
	void updateUserInfo(Customer& customer); // user 정보 변경 후 txt 파일에 업데이트

	void addUserToGroup(const string& userId, const string& groupName); 
	void removeUserFromGroup(const string& userId, const string& groupName);
};

/* 

1. 옵저버 패턴으로 구매시 고객 정보 / group 업데이트 여부 체크 ->>>>> 도입.

4. 그룹(티어) 관리 -> 알맞게 쿠폰이나 포인트 배부..?  ->>>> getter 넣기 (티어 확인할수있게 멤버변수추가)
*/ 