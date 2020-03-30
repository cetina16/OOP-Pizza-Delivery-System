#include <iostream>
#include <bits/stdc++.h>
#define INGREDIENTS_MAX 6

using namespace std;

class Drink{
	friend class Order;
	friend class OrderList;
	friend class Pizza;
	int Cola;
	int Soda;
	int Ice_tea;
	int Fruit_juice;
	public:
	Drink(int cola,int soda,int ice_tea,int fruit_juice);
};
Drink::Drink(int cola,int soda,int ice_tea,int fruit_juice){
	Cola = cola;
	Soda = soda;
	Ice_tea = ice_tea;
	Fruit_juice= fruit_juice;
}
class Pizza{
	friend class Order;
	friend class OrderList;
	friend class Drink;
	string Pizza_Name;    //name of the pizza
	string Size;          //small-medium-big
	string Ingredients[INGREDIENTS_MAX]; 
	string Crust_type;    //thick-normal-thick
	public:
	Pizza *pizza_next;
	Pizza();   
	Pizza(string size, string crust_type, int pizza_type);
	Pizza(Pizza& mypizza);
};
Pizza::Pizza(){  // default constructor 
	Size = "medium";
	Crust_type ="normal";
	Ingredients[0]= "mozarella";
	pizza_next = NULL;
}
Pizza::Pizza(string size, string crust_type, int pizza_type){
	Size = size;
	Crust_type = crust_type;
	pizza_next = NULL;
	Ingredients[0]="mozarella";
	if(pizza_type == 1){
		Pizza_Name = "Chicken Pizza";
		Ingredients[1]="chicken";
		Ingredients[2]="mushroom";
		Ingredients[3]="corn";
		Ingredients[4]="onion";
		Ingredients[5]="tomato";
	}else if(pizza_type ==2){
		Pizza_Name = "Broccoli Pizza";
		Ingredients[1]="broccoli";
		Ingredients[2]="pepperoni";
		Ingredients[3]="olive";
		Ingredients[4]="corn";
		Ingredients[5]="onion";
	}else if(pizza_type==3){
		Pizza_Name = "Sausage Pizza";
		Ingredients[1]="Sausage";
		Ingredients[2]="tomato";
		Ingredients[3]="olive";
		Ingredients[4]="mushroom";
		Ingredients[5]="corn";
	}
}
Pizza::Pizza(Pizza& firstpizza){
	Pizza_Name = firstpizza.Pizza_Name;
	Size = firstpizza.Size;
	Crust_type = firstpizza.Crust_type;
	pizza_next = NULL;
	for(int i = 0 ; i < INGREDIENTS_MAX ;i++){
		Ingredients[i]=firstpizza.Ingredients[i];
	}
	int ch = -1;
	cout << "Please enter the number of the ingredient you want to remove from your pizza."<< endl;
	cout << "Press 0 to save it."<<endl;
	for(int i = 0 ; i < INGREDIENTS_MAX ; i++){
		cout << i+1 <<". "<< firstpizza.Ingredients[i]<< endl;
	}
	while(true){
		cin >> ch;  
		if (ch == 0){
			break;
		}
		if(ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5 && ch != 6 ){
			cout << "Wrong input , try again"<< endl;
			continue;
		}
		Ingredients[ch-1] = " "; // removed ingredients represented by space
	}
}
class Order{
	string customer_name;
	Pizza* pizzas_head;
	Drink* drinks_ptr;
	friend class OrderList;
	friend class Pizza;
	friend class Drink;
	public:
	Order(string name_taken , Pizza* pizzass);
	Order(string name_taken , Pizza* pizzas, Drink* drinks);
	Order* order_next;
	double getPrice();
	void printOrder();
};
Order::Order(string name_taken , Pizza* pizzas)
{
	order_next = NULL;
	customer_name = name_taken;
	pizzas_head = pizzas;
	drinks_ptr = NULL;
}
Order::Order(string name_taken , Pizza* pizzas, Drink* drinks)
{
	order_next = NULL;
	customer_name = name_taken;
	pizzas_head = pizzas;
	drinks_ptr = drinks;
}
double Order::getPrice(){
	double price=0;
	double result =0;
	if(pizzas_head->Size[0]== 's'){ //Small pizza 15 TL
		price = price + 15;
	}else if(pizzas_head->Size[0] == 'm'){ //Medium pizza 20 TL
		price = price + 20;
	}else if(pizzas_head->Size[0] == 'b'){  //Big pizza 25 TL
		price = price + 25;
	}
	result = price;
	Pizza* pizza_traverse = pizzas_head;
	while(pizza_traverse->pizza_next != NULL){
		result = result + price;
		pizza_traverse = pizza_traverse->pizza_next;
	}
	if(drinks_ptr != NULL){
		result = result + (drinks_ptr->Cola )*4 + (drinks_ptr->Soda)*2 + (drinks_ptr->Ice_tea)*3 + (drinks_ptr->Fruit_juice)*3.5;
	}	
	return result;
}

void Order::printOrder(){
	cout << "------------"<< endl;
	cout << "Name: "<< customer_name << endl ;
	
	Pizza* traverse = pizzas_head;
	while(traverse){
		cout << traverse->Pizza_Name<< "(";
		for(int i=0;i<6;i++){
			if(traverse->Ingredients[i] == " "){
				continue;
			}
			cout << traverse->Ingredients[i] << ",";
		}
		cout<<")"<<endl;
		cout <<"size: " <<traverse->Size << ", crust: " << traverse->Crust_type<< endl;
		traverse = traverse->pizza_next;
	}
	if(drinks_ptr != NULL){
		if(drinks_ptr->Cola != 0){
			cout << drinks_ptr->Cola << " cola," ;
		}
		if(drinks_ptr->Soda != 0){
			cout << drinks_ptr->Soda << " soda," ;
		}
		if(drinks_ptr->Ice_tea != 0){
			cout << drinks_ptr->Ice_tea<< " ice tea," ;
		}
		if(drinks_ptr->Fruit_juice != 0){
			cout << drinks_ptr->Fruit_juice << " fruit juice" ;
		}
		cout << endl;
	}
	cout << "------------"<< endl;
}


class OrderList{
	friend class Pizza;
	friend class Order;
	friend class Drink;
	int n; //number of orders
	Order* orders_head; 
	public:
	OrderList();
	int takeOrder();
	void listOrders();
	void deliverOrders();
};
OrderList::OrderList(){
	n = 0;
	orders_head = NULL;
}
void OrderList::listOrders(){
	int number = 1;
	if (orders_head == NULL){
		cout << "empty"<< endl;
	}else{
		Order* order_traverse = orders_head;
		while(order_traverse){
			cout << number << endl;
			order_traverse->printOrder();
			order_traverse = order_traverse ->order_next;
			number++;
		}
	}
}
void OrderList::deliverOrders(){
	string name_taken;
	double disc_price=0;
	char promotion_ch;
	string prcode;
	if(orders_head == NULL){
		cout << "empty"<< endl;
	}else{
		cout << "Please write the customer name in order to deliver his/her order:";
		cin >> name_taken;
		Order* orders_traverse = orders_head;
		Order* orders_tail;
		while(orders_traverse){
			if(orders_traverse->customer_name == name_taken){   
				break;
			}
			orders_tail = orders_traverse;
			orders_traverse = orders_traverse->order_next;
		}
		
		if(orders_traverse == NULL){
			cout << "Wrong name"<< endl;
		}else{
			cout << "Following order will be delivered..."<< endl;
			orders_traverse->printOrder();
			double price =  orders_traverse->getPrice();
			cout << "Total price: " << price <<endl;
			while(true){
				cout << "Do you have a promotion code? (y/n)"<< endl;
				cin >> promotion_ch;
				if(promotion_ch == 'y'){
					cout <<"Please enter your code: ";
					cin.ignore();
					getline(cin,prcode);
					if(prcode == "I am a student"){
						disc_price = price * 0.9;
						cout << "Discounted price: "<< disc_price <<endl;
						break;
					}else{
						cout << "Promotion code is not accepted."<<endl;
					}
				}else if(promotion_ch == 'n'){
					break;
				}else{
					cout << "Please enter y or n , try again" << endl;
				}
			}
			cout << "The order is delivered successfully!"<< endl;
			if(orders_traverse == orders_head){               //removing the first order
				orders_head=orders_traverse->order_next;
				delete orders_traverse;
			}else{
				orders_tail->order_next = orders_traverse->order_next;
				delete orders_traverse;
			}
		}
		
	}
}
int OrderList::takeOrder(){
	int input_cola = 0;
	int input_soda = 0;
	int input_icetea = 0;
	int input_fruit = 0;
	int pizza_choice ;
	int drink_choice = -2;
	int back_control = 1;
	string input_client;
	string selected_size;
	string selected_crust;
	int amount;
	cout<< "Pizza Menu"<< endl;
	cout<< "1. Chicken Pizza (mozarella, chicken, mushroom, corn, onion, tomato)" << endl;
	cout<< "2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)" << endl;
	cout<< "3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)" << endl;
	cout<< "0. Back to main menu" << endl;
	cin >> pizza_choice;
	while( pizza_choice != 0 && pizza_choice != 1 && pizza_choice != 2 && pizza_choice != 3){
		cout << "Wrong input , try again " << endl;
		cin >> pizza_choice;
	}
	if(pizza_choice == 0){ //back to main menu
		back_control = 0;
		return back_control;
	}else{
		cout<<"Select size: small (15 TL), medium (20 TL), big (25 TL)"<< endl;
		cin >> selected_size;
		while(selected_size != "small" && selected_size != "medium"&&  selected_size != "big" ){   
			cout << "Please enter small, medium or big..."<< endl;
			cin >> selected_size;
		}
		cout << "Select crust type: thin, normal, thick"<< endl;
		cin >>  selected_crust;
		while(selected_crust != "thin" && selected_crust != "normal"&&  selected_crust != "thick" ){   
			cout << "Please enter thin, normal or thick..."<< endl;
			cin >> selected_crust;
		}
		cout << "Enter the amount:";
		cin >> amount;
		if(amount <= 0 ){
			cout << "You entered unexceptible amount!"<< endl;
			back_control=0;
			return back_control;
		}
		Pizza* Pizza_head = new Pizza(selected_size, selected_crust, pizza_choice); // First pizza of an order created
		Pizza* traverse = Pizza_head;
		while (amount > 1 ){
			Pizza* extrapizza = NULL;
			extrapizza = new Pizza(*Pizza_head); //copy constructor invoked const!!!!!!!!!!!!!!!!
			traverse->pizza_next = extrapizza;
			traverse = extrapizza;
			amount--;
		}
		cout << "Please choose a drink:"<<endl;
		cout << "0. no drink"<< endl;
		cout << "1. cola 4 TL"<< endl;
		cout << "2. soda 2 TL"<< endl;
		cout << "3. ice tea 3 TL"<< endl;
		cout << "4. fruit juice 3.5 TL"<< endl;
		cout << "Press -1 for save your order"<< endl;
		while(true){
			if(drink_choice == -1 || drink_choice == 0){
				break;
			}
			cin >> drink_choice;
			while(drink_choice != -1 && drink_choice !=0 && drink_choice != 1 && drink_choice != 2 && drink_choice != 3 && drink_choice != 4 ){
				cout << "Wrong input, try agin !" << endl;
				cin >> drink_choice;
				if(drink_choice == -1){
					break;
				}
			}
			if(drink_choice == 1 ){   // creating a drink obj
				input_cola++;
			}else if(drink_choice ==2){
				input_soda++;
			}else if(drink_choice == 3){
				input_icetea++;
			}else if (drink_choice ==4){
				input_fruit++;
			}
			if(drink_choice == -1){
				break;
			}
		}
		cout << "Please enter your name: "<< endl;
		cin >> input_client;
		n++;
		Order* new_order = NULL;
		if(input_cola == 0 && input_soda == 0 && input_icetea == 0 && input_fruit==0){
			new_order = new Order(input_client , Pizza_head);
		}else{
			Drink *Drinks_ptr = new Drink(input_cola ,input_soda,input_icetea ,input_fruit);
			new_order = new Order(input_client , Pizza_head,Drinks_ptr );
		}
		Order *order_traverse = orders_head;
		if(orders_head == NULL){   // First Order will be adding to OrderList    
			orders_head = new_order;
		}else{
			while(order_traverse){
				if(order_traverse->order_next == NULL){
					order_traverse->order_next = new_order;
					break;
				}
				order_traverse = order_traverse->order_next;
				
			}
		}
		cout << "Your order is saved, it will be delivered when it is ready..."<< endl;
		new_order->printOrder();
		return back_control;
	}
}

int main(){
	OrderList OL1; // default constructor invoked, orderlist created
	int menu_choice=0 ;
	int control=1;
	string input_customer;
	while(menu_choice != 4){
		cout << "Welcome to Unicorn Pizza "<< endl;
		cout << "1. Add an order "<< endl;
		cout << "2. List the orders "<< endl;
		cout << "3. Deliver order "<< endl;
		cout << "4. Exit "<< endl;
		cout << "Choose what to do: ";
		cin >> menu_choice;
		
		if(menu_choice == 4 ){    // ending the program
			cout << "Goodbye..."<< endl;
			return EXIT_SUCCESS;
		}else if (menu_choice == 1){
			control = OL1.takeOrder();
			if(control == 0){
				continue;
			}
		}else if(menu_choice == 3){
			OL1.listOrders();
			OL1.deliverOrders();
		}else if(menu_choice == 2){
			OL1.listOrders();
		}else{
			cout << "Please try again..."<< endl;
		}	
	}

}