#pragma once

namespace OrderTypes {
	enum class OrderType {
		Market,				// Executed immediately at the best price
		Limit,				// Buy/sell at the specified price/a better price
		Stop,				// Executed when a specified price has been reached
		TrailingStop,		// Orders that are adjusted based on the price of the asset 
		FillOrKill,			// Must be executed immediately in its entirety, no partial execution
		GoodTillCanceled,	// Remains active until it is executed or canceled
		None
	};

	enum class OrderSide
	{
		Buy,
		Sell,
		None
	};
}
