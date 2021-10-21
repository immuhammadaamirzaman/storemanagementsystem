#include"Node.h"
#include"Functions.h"
#include<chrono>

#define wait system("pause")
#define cls system("cls")

using namespace std;
using namespace chrono;
class TimeX{
private:
	time_point<high_resolution_clock>Start;
public:
	TimeX(){ Start = high_resolution_clock::now(); }
	void Stop(){
		auto End = high_resolution_clock::now();
		auto start = time_point_cast<seconds>(Start).time_since_epoch().count();
		auto end = time_point_cast<seconds>(End).time_since_epoch().count();
		duration<long>dur(end - start);
		cout << dur.count() << " s!\n";
	}
	~TimeX(){ Stop(); }
};


int main(){
	TimeX t;
	SetFonts();
	{
		Store s;
		char option;
		vector<short>V_items, V_quantity, V_purchased;
		vector<short>::iterator it;
		cls;
		Menu();
		do{
		back:
			cls;
			cout << "1) Admin\n2) User\n Select:";
			cin >> option;
			if (option == '1'){
					Login();
				do{
					cls;
					Mem();
					cout << "Variables Memory:" << s.Memory() << " Bytes\n";
					cout << "\nExecution Time:"; t.Stop();
					cout << "\n1) Add item\n2) Edit\n3) List items\n4) Search Name\n5) Search ID\n6) Back\n Select:";
					cin >> option;
					if (option == '1'){
						cls;
						s.AddItem();
					}
					else if (option == '2'){
						cls;
						cout << "Enter item# to Edit:";
						uint16_t id;
						cin >> id;
						s.EditItem(id);
					}
					else if (option == '3'){
						cls;
						s.PrintList();
						wait;
					}

					else if (option == '4'){
						s.SeachItemName();
						wait;
					}
					else if (option == '5'){
						s.SeachItemID();
						wait;
					}
					else
						goto back;
				} while (1);
			}
			else if (option == '2'){//user
				do{
					static short items = 0, Totalquantity = 0;
					cls;
					if (s.TotalItems()){
						cout << "\t\t\t\t\t\t\tBill:" << s.Bill() << endl;
						s.PrintList();
						uint16_t id, quantity;
						cout << "\n\n 1)Purchase\n 2)Search Item by Id\n 3)Search Item by Name\n 4)Return Item\n 5)Exit \n Select:";
						cin >> option;
						if (option == '1'){
							bool xo = true;
							do{
								cls;
								s.PrintList();//prints all items
								cout << "Enter Item# to Purchase item:";
								cin >> id;
								if (s.TotalItems() >= id){//checks if entered id is available
									for (auto&i : V_items){
										if (id == i){//if id is repeated 
											xo = false;
											break;
										}
									}
									if (xo)//if id is new
										V_items.push_back(id);
									break;
								}
								else{
									cout << "\nNot Enough Items!\n";
									Sleep(1000);
								}
							} while (1);
							do{
								cout << "Enter Quantity of the item#" << id << ":";
								cin >> quantity;
								it = find(V_items.begin(), V_items.end(), id);
								int index = distance(V_items.begin(), it);
								if (s.QuantityofItem(id) >= quantity){
									if (!xo){//if it repeats
										V_purchased.at(index) = V_purchased[index] + quantity;
										V_quantity.at(index) = V_quantity.at(index) + quantity;
										break;
									}
									else{
										V_quantity.push_back(quantity);
										V_purchased.push_back(quantity);//use its values in output
										break;
									}
								}
								else{
									cout << "\nNot Enough Quantity!\n";
									Sleep(1000);
								}
							} while (1);
							if (s.ShopItem(id, quantity)){
								if (xo)
									++items;
								Totalquantity = Totalquantity + quantity;
							}
						}
						else if (option == '2'){
							s.SeachItemID();
							wait;
						}
						else if (option == '3'){
							s.SeachItemName();
							wait;
						}
						else if (option == '4'){//returnitem
							cls;
							if (Totalquantity){
								//find() to get if element is in list or not
								s.PurchasedList(V_items, V_quantity);
								bool flag = false;
								do{
									cout << "\nEnter Item# you Want to Return:";
									cin >> id;
									for (auto&i : V_items){
										if (id == i){//cheking if id is in vector or not
											flag = true;
											break;
										}
									}
									if (flag)//if found
										break;
								} while (1);
								if (flag){//item id is ok
										flag = false;
										cout << "Enter Quantity you Want to Return:";
										cin >> quantity;
											it = find(V_items.begin(), V_items.end(), id);
											int index = distance(V_items.begin(), it);
											for (auto&l : V_quantity) {
												if (quantity <= V_quantity[index]) {//if entered quant is ok
													flag = true;
													Totalquantity -= quantity;
													V_quantity.at(index) = V_quantity[index] - quantity;
													V_purchased.at(index) = V_purchased[index] - quantity;
													if (V_quantity[index] == 0) {//error could be here
														V_items.erase(V_items.begin() + index);
														V_purchased.erase(V_purchased.begin() + index );
														V_quantity.erase(V_quantity.begin() + index);
														items--;
													}
													break;
												}
											}
									if (!flag){
										cout << "You haven't Purchased " << quantity << " items!\n";
										Sleep(1000);
										break;
									}
								}
								s.ReturnItem(id, quantity);
							}
							else{
								cout << "\nYou haven't Purchased any item!\n";
								Sleep(800);
								break;
							}
						}
						else if (option == '5'){
							if (s.Bill()){
								cls;
								s.PurchasedList(V_items, V_purchased);
								cout << "\n\nTotal Items: " << items << "\n\nTotal Quantity: " << Totalquantity;
								cout << "\n\nTotal Bill:" << s.Bill();
								cout << "\n\n\t\tThank you for Shopping!\n";
								items = Totalquantity = 0;
								V_items.clear();
								V_quantity.clear();
								V_purchased.clear();
								s.SetSum(0);
								wait;
								break;
							}
							else{
								cout << "Thank you for Using our Softwares!\n";
								Sleep(1000);
								goto back;
							}
						}
						else{
							cout << "\nInvalid Entry!\n";
							Sleep(1000);
						}
					}

					else{
						cout << "\nList is Empty!\n";
						wait;
						break;
					}
				} while (1);
			}
			else
				exit(0);
		} while (1);
	}//timer
	wait;
}