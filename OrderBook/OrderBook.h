#pragma once

#include "../Order/Order.h"

#include <iostream>
#include <unordered_map>

class OrderBook {
public:
	OrderBook() {}

	void addOrder(Order& order);

	void cancelOrder(GUID orderId);

	Order orderLookup(GUID orderId);

	void matchOrders();

	void printOrders();

private:
	// Use a unordered map to keep track of all orders for fast retrieval/update/delete times
	std::unordered_map<GUID, Order> orderMap;

	// Helper method to find a match for a given order
	std::unordered_map<GUID, Order>::iterator findMatch(OrderTypes::OrderSide orderSide, double orderPrice, int orderQuantity, bool fullMatch = false);

	// Helper method to execute an order
	void executeOrder(std::unordered_map<GUID, Order>::iterator& orderIt, std::unordered_map<GUID, Order>::iterator& matchIt);

	// Helper method for printing order contents
	void printOrder(Order& order);
};
