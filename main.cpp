// OrderBook.cpp : Defines the entry point for the application.
//

#include "OrderBook/OrderBook.h"
#include "OrderTypes.h"
#include "Order/Order.h"

using namespace std;

int main()
{
    // Create an instance of OrderBook
    OrderBook orderBook;

    // Create sample orders of different types
    Order order1(1, "NVDA", OrderTypes::OrderType::Market, OrderTypes::OrderSide::Buy, 0, 10);
    Order order2(2, "NVDA", OrderTypes::OrderType::Limit, OrderTypes::OrderSide::Sell, 101.0, 20);
    Order order3(3, "NVDA", OrderTypes::OrderType::Limit, OrderTypes::OrderSide::Sell, 99.0, 5);
    Order order4(4, "NVDA", OrderTypes::OrderType::Market, OrderTypes::OrderSide::Sell, 0, 15);
    Order order5(5, "NVDA", OrderTypes::OrderType::GoodTillCanceled, OrderTypes::OrderSide::Buy, 102.0, 10);
    Order order6(6, "NVDA", OrderTypes::OrderType::FillOrKill, OrderTypes::OrderSide::Sell, 100.0, 8);
    Order order7(7, "NVDA", OrderTypes::OrderType::FillOrKill, OrderTypes::OrderSide::Buy, 99.0, 12);
    Order order8(8, "NVDA", OrderTypes::OrderType::FillOrKill, OrderTypes::OrderSide::Buy, 101.0, 8);

    // Add orders to the order book
    orderBook.addOrder(order1);
    orderBook.addOrder(order2);
    orderBook.addOrder(order3);
    orderBook.addOrder(order4);
    orderBook.addOrder(order5);
    orderBook.addOrder(order6);
    orderBook.addOrder(order7);
    orderBook.addOrder(order8);

    // Print the order book before matching orders
    std::cout << "Order Book before matching:" << std::endl;
    orderBook.printOrders();

    // Match orders in the order book
    orderBook.matchOrders();

    // Print the order book after matching
    std::cout << "Order Book after matching:" << std::endl;
    orderBook.printOrders();

    return 0;
}
