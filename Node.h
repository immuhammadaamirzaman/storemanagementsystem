#include<iostream>
#include<Windows.h>
#include<string>
#include<memory>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

class Node{
private:
	shared_ptr<Node>next;
	string Name;
	uint16_t Price, Quantity;
	uint16_t Id;
public:
	Node() :next(nullptr), Name("\0"), Price(0), Quantity(0){ Id = 0; }

	void setName(string n){ Name = n; }
	void setPrice(uint16_t p){ Price = p; }
	void setQuantity(uint16_t q){ Quantity = q; }
	void setId(uint16_t id){ Id = id; }
	void setNext(shared_ptr<Node>p){ next = p; }
	string getName()const{ return Name; }
	uint16_t getPrice()const{ return Price; }
	uint16_t getQuantity()const{ return Quantity; }
	uint16_t getID()const{ return Id; }
	shared_ptr<Node> getNext(){ return next; }
};
class Store{
private:
	shared_ptr<Node>head, current, precurrent;
	uint16_t Sum;
	uint16_t id;
	bool isEmpty()const{ return head == nullptr; }
public:
	Store() :head(NULL), current(nullptr), precurrent(NULL), Sum(0){}
	//file handling
	
	void SetSum(short s){ Sum = s; }

	void AddItem(){//add
		shared_ptr<Node>ptr = make_shared<Node>();
		ptr->setNext(nullptr);
		ptr->setId(++id);
		string name;
		uint16_t price, quantity;
		cout << "Enter Name of Item#" << ptr->getID() << ":";
		cin >> name;
		ptr->setName(name);
		cout << "Enter Price of Item#" << ptr->getID() << ":";
		cin >> price;
		ptr->setPrice(price);
		cout << "Enter Quantity of Item#" << ptr->getID() << ":";
		cin >> quantity;
		ptr->setQuantity(quantity);

		if (!isEmpty()){
			precurrent->setNext(current);
			current->setNext(ptr);
			precurrent = current;
			current = ptr;
		}
		else
			current = precurrent = head = ptr;
		cout << "\n\nRecord has been Added\n";
		Sleep(700);

	}//add
	void ReturnItem(uint16_t index, uint16_t quantity){
		current = precurrent = head;
		short x = 1;
		if (index == 1){
			head->setQuantity(head->getQuantity() + quantity);
		}
		else{
			while (x < index){//i<id
				precurrent = current;
				current = current->getNext();
				x++;
			}
			current->setQuantity(current->getQuantity() + quantity);
		}
		Sum = Sum - current->getPrice()*quantity;
		cout << "Item Returned Successfully!\n";
		Sleep(1000);
	}//ret
	void PurchasedList(vector<short>&items, vector<short>&quantity){
		try{
			cout << "\t\t\tPurchased items!\n";
			cout << "Item#\t\tName\t\tPrice\t\tQuantity\n";
			vector<short>::iterator i;
			for (auto&vec : items){
				current = precurrent = head;
				short count = 1;
				i = find(items.begin(), items.end(),vec);
				short c = distance(items.begin(), i);
				while (count < vec){
					precurrent = current;
					current = current->getNext();
					count++;
				}
				cout << vec << "\t\t" << current->getName() << "\t\t" << current->getPrice() << "\t\t"<< quantity.at(c)<<endl;
			}
		}
		catch (...){
			cout << "Subscript out of range!\n";
		}
	}//buy
	short QuantityofItem(uint16_t id){
		current = precurrent = head;
		uint16_t i = 1;
		while (i < id){
			precurrent = current;
			current = current->getNext();
			i++;
		}
		return current->getQuantity();
	}
	short TotalItems(){ return id; }

	void EditItem(uint16_t index){//edit
		if (!isEmpty()){
			if (index <=id){
				shared_ptr<Node>ptr = head;
				short i = 1;
				while (i < index){
					ptr = ptr->getNext();
					i++;
				}
				string name;
				uint16_t price, quantity;
				cout << "item#\tName\tPrice\tQuantity\n";
				cout << ptr->getID() << "\t" << ptr->getName() << "\t" << ptr->getPrice() << "\t"<< ptr->getQuantity() << endl;
				cout << "\n\nEnter New Name for Item#" << index << ":";
				cin >> name;
				ptr->setName(name);
				cout << "\nEnter New Price for Item#" << index << ":";
				cin >> price;
				ptr->setPrice(price);
				cout << "\nEnter New Quantity for Item#" << index << ":";
				cin >> quantity;
				ptr->setQuantity(quantity);
				cout << "\nRecord has been Modified!\n";
				Sleep(700);
			}
			else{
				cout << "\nWe have only " << this->id << " available!\n";
				Sleep(1000);
			}
		}
		else{
			cout << "\nNo Item to be Edited!\n";
			Sleep(700);
		}
	}//edit
	bool ShopItem(uint16_t id, uint16_t quantity){//shop
		if (id <= this->id){
			precurrent = current = head;
			short i = 1;
			
			while (i < id){
				precurrent = current;
				current = current->getNext();
				i++;
			}
			if (current->getQuantity() >= quantity){
				current->setQuantity(current->getQuantity() - quantity);
				Sum = Sum + (current->getPrice()* quantity);
				cout << "\nItem#" << id << " has been Puchased!\n";
				Sleep(800);
				return 1;
			}
			else{
				cout << "\nWe have " << current->getQuantity() << " items for item#" << id << endl;
				Sleep(1000);
				return 0;
			}
		}
		else{
			cout << "\nThere is no item with " << id << "#\n";
			Sleep(700);
			return 0;
		}
	}//shop
	short Bill(){ return Sum; }

	void SeachItemName(){
		if (!isEmpty()){
			system("cls");
			PrintList();
			cout << "Enter Item Name:";
			string name;
			cin >> name;
			bool check = false;
			precurrent = current = head;
			system("cls");
			cout << "Item#\t\tName\t\tPrice\t\tQuantity\n";
			while (current){
				if (current->getName() == name){
					cout << current->getID() << "\t\t" << current->getName() << "\t\t" << current->getPrice() << "\t\t" << current->getQuantity() << endl;
					check = true;
				}
				if (!check) {
					if (current->getName()[0] == name[0]) {
						cout << current->getID() << "\t\t" << current->getName() << "\t\t" << current->getPrice() << "\t\t" << current->getQuantity() << endl;
					}
					check = true;
				}
				precurrent = current;
				current = current->getNext();
			}
			if (!check)
				cout << "\nNo item found with Name:" << name << " !\n";
		}
		else
			cout << "\nNo Item is Currently Available!\n";
	}
	void SeachItemID(){
		if (!isEmpty()){
			system("cls");
			PrintList();
			cout << "Enter Item#:";
			uint16_t id;
			cin >> id;
			bool check = false;
			precurrent = current = head;
			system("cls");
			cout << "Item#\t\tName\t\tPrice\t\tQuantity\n";
			while (current){
				if (current->getID() == id){
					cout << current->getID() << "\t\t" << current->getName() << "\t\t" << current->getPrice() << "\t\t" << current->getQuantity() << endl;
					check = 1;
					break;
				}
				precurrent = current;
				current = current->getNext();
			}
			if (!check)
				cout << "\nNo item found with #:" << id << " !\n";
		}
		else
			cout << "\nNo Item is Currently Available!\n";
	}//search name
	void PrintList(){//print
		if (!isEmpty()){
			current = precurrent = head;
			cout << "Item#\t\tName\t\tPrice\t\tQuantity\n";
			while (true){
				if (current->getQuantity() != 0)//if quantity is not 0 else dont print that item
				cout << current->getID() << "\t\t" << current->getName() << "\t\t" << current->getPrice() << "\t\t" << current->getQuantity() << endl;
				if (current->getNext()){
					precurrent = current;
					current = current->getNext();
				}
				else
					break;
			}
		}
		else
			cout << "\nList is Empty!\n";
	}//print
	size_t Memory(){ return sizeof(Node)*id; }	
};