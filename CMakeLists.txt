# CMakeList.txt : CMake project for OrderBook, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OrderBook")

# Add source to this project's executable.
add_executable (OrderBook "main.cpp"  "Order/Order.cpp" "Order/Order.h" "OrderBook/OrderBook.cpp" "OrderBook/OrderBook.h" "OrderTypes.h")

# TODO: Add tests and install targets if needed.
