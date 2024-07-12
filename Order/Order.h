#pragma once

#include "../OrderTypes.h"
#include <combaseapi.h>

#include <string>
#include <iostream>


class Order {
public:
	Order(int userId, std::string symbol, OrderTypes::OrderType type, OrderTypes::OrderSide side, double price, int quantity);

	GUID getOrderId();
	OrderTypes::OrderType getOrderType();
	OrderTypes::OrderSide getOrderSide();
	double getPrice();
	int getQuantity();
	void setQuantity(int q);

private:
	GUID _orderId;
	int _userId;
	std::string _symbol;
	OrderTypes::OrderType _type;
	OrderTypes::OrderSide _side;
	double _price;
	int _quantity;

	void GenerateOrderId();
};
