#include "OrderBook.h"
#include "OrderBook.h"
#include "../OrderTypes.h"

void OrderBook::addOrder(Order& order)
{
    GUID currentOrderId = order.getOrderId();

    if (orderMap.find(currentOrderId) == orderMap.end()) {
        orderMap[currentOrderId] = order;
    }
    else {
        std::cout << "Order with orderId already exists" << std::endl;
    }
}

void OrderBook::cancelOrder(GUID orderId)
{
    if (orderMap.find(orderId) != orderMap.end()) {
        orderMap.erase(orderId);
    }
}

Order OrderBook::orderLookup(GUID orderId)
{
    if (orderMap.find(orderId) != orderMap.end()) {
        return orderMap[orderId];
    }
    return Order(-1, "", OrderTypes::OrderType::None, OrderTypes::OrderSide::None, 0, 0);
}

void OrderBook::matchOrders()
{
    for (auto it = orderMap.begin(); it != orderMap.end(); it++) {
        Order currentOrder = it->second;
        if (currentOrder.getOrderType() == OrderTypes::OrderType::Market) {
            auto matchIt = findMatch(currentOrder.getOrderSide(), currentOrder.getPrice(), currentOrder.getQuantity());
            if (matchIt != orderMap.end()) {
                executeOrder(it, matchIt);
                it = orderMap.erase(it);
            }
        }
    }

    // Handle GoodTillCanceled orders
    for (auto it = orderMap.begin(); it != orderMap.end(); it++) {
        Order currentOrder = it->second;
        if (currentOrder.getOrderType() == OrderTypes::OrderType::GoodTillCanceled) {
            auto matchIt = findMatch(currentOrder.getOrderSide(), currentOrder.getPrice(), currentOrder.getQuantity());
            if (matchIt != orderMap.end()) {
                executeOrder(it, matchIt);
                it = orderMap.erase(it);
            }
        }
    }

    // Handle Fill-Or-Kill orders separately
    for (auto it = orderMap.begin(); it != orderMap.end(); it++) {
        Order currentOrder = it->second;
        if (currentOrder.getOrderType() == OrderTypes::OrderType::FillOrKill) {
            auto matchIt = findMatch(currentOrder.getOrderSide(), currentOrder.getPrice(), currentOrder.getQuantity(), true); // Ensure full match
            if (matchIt != orderMap.end() && matchIt->second.getQuantity() >= it->second.getQuantity()) {
                executeOrder(it, matchIt);
                it = orderMap.erase(it);
            }
            else {
                OLECHAR* guidString;
                StringFromCLSID(currentOrder.getOrderId(), &guidString);
                std::cout << "Canceled FOK Order ID: " << guidString << std::endl;
                it = orderMap.erase(it);
            }
        }
    }

    // Finally, handle Limit orders that were not matched by Market or GTC orders
    for (auto it = orderMap.begin(); it != orderMap.end(); it++) {
        Order currentOrder = it->second;
        if (currentOrder.getOrderType() == OrderTypes::OrderType::Limit) {
            auto matchIt = findMatch(currentOrder.getOrderSide(), currentOrder.getPrice(), currentOrder.getQuantity());
            if (matchIt != orderMap.end()) {
                executeOrder(it, matchIt);
                it = orderMap.erase(it);
            }
        }
    }
}

void OrderBook::printOrders() {
    for (auto& order : orderMap) {
        printOrder(order.second);
    }
}

std::unordered_map<GUID, Order>::iterator OrderBook::findMatch(OrderTypes::OrderSide orderSide, double orderPrice, int orderQuantity, bool fullMatch)
{
    for (auto it = orderMap.begin(); it != orderMap.end(); it++) {
        Order currentOrder = it->second;

        if (currentOrder.getOrderSide() != orderSide &&
            ((orderSide == OrderTypes::OrderSide::Buy && currentOrder.getPrice() <= orderPrice) ||
                (orderSide == OrderTypes::OrderSide::Buy && currentOrder.getPrice() >= orderPrice)) &&
            (!fullMatch || currentOrder.getQuantity() >= orderQuantity)) {
            return it;
        }
    }
    return orderMap.end();
}

void OrderBook::executeOrder(std::unordered_map<GUID, Order>::iterator& orderIt, std::unordered_map<GUID, Order>::iterator& matchIt)
{
    double fillPrice = matchIt->second.getPrice();

    OLECHAR* guidStringOrder;
    OLECHAR* guidStringMatch;
    StringFromCLSID(orderIt->second.getOrderId(), &guidStringOrder);
    StringFromCLSID(orderIt->second.getOrderId(), &guidStringMatch);

    std::cout << "Matched Order ID: " << guidStringOrder << " with Order ID: " << guidStringMatch << " at Price: " << fillPrice << " quantity: " << orderIt->second.getQuantity() << std::endl;
    matchIt->second.setQuantity(matchIt->second.getQuantity() - orderIt->second.getQuantity());
    if (matchIt->second.getQuantity() == 0) {
        orderMap.erase(matchIt->first);
    }
}

void OrderBook::printOrder(Order& order) {
    OLECHAR* guidString;
    StringFromCLSID(order.getOrderId(), &guidString);

    std::cout << "Order ID: " << guidString
        << ", Type: " << static_cast<int>(order.getOrderType())
        << ", Side: " << (order.getOrderSide() == OrderTypes::OrderSide::Buy ? "Buy" : "Sell")
        << ", Price: " << order.getPrice()
        << ", Quantity: " << order.getQuantity() << std::endl;
}
