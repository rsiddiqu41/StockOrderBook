#include "Order.h"
#include "../OrderTypes.h"



Order::Order(int userId, std::string symbol, OrderTypes::OrderType type, OrderTypes::OrderSide side, double price, int quantity)
{
	_userId = userId;
	_symbol = symbol;
	_type = type;
	_side = side;
	_price = price;
	_quantity = quantity;

	GenerateOrderId();
}

// HRESULT values -> https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values
void Order::GenerateOrderId()
{
	HRESULT hCreateGuid = CoCreateGuid(&_orderId);
	if (hCreateGuid == 0x00000000) {
		std::cout << "Successfully created OrderId" << std::endl;
	}
	else {
		std::cout << "Unable to create OrderId" << std::endl;
	}
}

GUID Order::getOrderId() {
	return _orderId;
}

OrderTypes::OrderType Order::getOrderType()
{
	return _type;
}

OrderTypes::OrderSide Order::getOrderSide()
{
	return _side;
}

double Order::getPrice()
{
	return _price;
}

int Order::getQuantity()
{
	return _quantity;
}

void Order::setQuantity(int q)
{
	_quantity = q;
}
