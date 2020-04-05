# Alpaca Trade API C++ Client

This document has the following sections:

- [Overview](#overview)
- [Contributing](#contributing)
- [Client Usage](#client-usage)
  - [Environment Variables](#environment-variables)
  - [Account API](#account-api)
  - [Account Configuration API](#account-configuration-api)
  - [Account Activities API](#account-activities-api)
  - [Orders API](#orders-api)
  - [Positions API](#positions-api)
  - [Assets API](#assets-api)
  - [Watchlist API](#watchlist-api)
  - [Calendar API](#calendar-api)
  - [Clock API](#clock-api)


## Overview

`alpaca-trade-api-cpp` is a C++ library for the [Alpaca Commission Free Trading API](https://alpaca.markets). The official HTTP API documentation can be found at https://docs.alpaca.markets/.

## Contributing

For information on building, testing, and contributing to this repository, please see the [Contributor Guide](./CONTRIBUTING.md).

## Client Usage

### Environment Variables

The Alpaca SDK will check the environment for a number of variables which can be used rather to authenticate with and connect to the Alpaca API.

| Environment | Default Value | Description  |
| --- | --- | --- |
| APCA_API_KEY_ID | | Your API Key. |
| APCA_API_SECRET_KEY | | Your API Secret Key. |
| APCA_API_BASE_URL | paper-api.alpaca.markets | The endpoint for API calls. Note that the default is paper so you must specify this to switch to the live endpoint. |
| APCA_API_DATA_URL | data.alpaca.markets | The endpoint for the Data API. |

### Account API

The account API serves important information related to an account, including account status, funds available for trade, funds available for withdrawal, and various flags relevant to an account’s ability to trade. An account maybe be blocked for just for trades (the `trades_blocked` property of `alpaca::Account`) or for both trades and transfers (the `account_blocked` property of `alpaca::Account`) if Alpaca identifies the account to engaging in any suspicious activity. Also, in accordance with FINRA’s pattern day trading rule, an account may be flagged for pattern day trading (the `pattern_day_trader` property of `alpaca::Account`), which would inhibit an account from placing any further day-trades.

For more information the Account API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/account/.

### Account Configuration API

The account configuration API provides custom configurations about your trading account settings. These configurations control various allow you to modify settings to suit your trading needs. For DTMC protection, see the documentation on [Day Trade Margin Call Protection](https://alpaca.markets/docs/trading-on-alpaca/user-protections/#day-trade-margin-call-dtmc-protection-at-alpaca).

For more information on the Account Configuration API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/account-configuration/.

### Account Activities API

The account activities API provides access to a historical record of transaction activities that have impacted your account. Trade execution activities and non-trade activities, such as dividend payments, are both reported through this endpoint. At the time of this writing, the following are the types of activities that may be reported:

| Activity Type | Description |
| --- | --- |
| `FILL` |  Order fills (both partial and full fills) |
| `TRANS` | Cash transactions (both CSD and CSR) |
| `MISC` | Miscellaneous or rarely used activity types (All types except those in `TRANS`, `DIV`, or `FILL`) |
| `ACATC` | ACATS IN/OUT (Cash) |
| `ACATS` | ACATS IN/OUT (Securities) |
| `CSD` | Cash disbursement(+) |
| `CSR` | Cash receipt(-) |
| `DIV` | Dividends |
| `DIVCGL` | Dividend (capital gain long term) |
| `DIVCGS` | Dividend (capital gain short term) |
| `DIVFEE` | Dividend fee |
| `DIVFT` | Dividend adjusted (Foreign Tax Withheld) |
| `DIVNRA` | Dividend adjusted (NRA Withheld) |
| `DIVROC` | Dividend return of capital |
| `DIVTW` | Dividend adjusted (Tefra Withheld) |
| `DIVTXEX` | Dividend (tax exempt) |
| `INT` | Interest (credit/margin) |
| `INTNRA` | Interest adjusted (NRA Withheld) |
| `INTTW` | Interest adjusted (Tefra Withheld) |
| `JNL` | Journal entry |
| `JNLC` | Journal entry (cash) |
| `JNLS` | Journal entry (stock) |
| `MA` | Merger/Acquisition |
| `NC` | Name change |
| `OPASN` | Option assignment |
| `OPEXP` | Option expiration |
| `OPXRC` | Option exercise |
| `PTC` | Pass Thru Charge |
| `PTR` | Pass Thru Rebate |
| `REORG` | Reorg CA |
| `SC` | Symbol change |
| `SSO` | Stock spinoff |
| `SSP` | Stock split |

For more information on the Account Activities API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/account-activities/.

### Orders API

The Orders API allows a user to monitor, place and cancel their orders with Alpaca. Each order has a unique identifier provided by the client. This client-side unique order ID will be automatically generated by the system if not provided by the client, and will be returned as part of the order object along with the rest of the fields described below. Once an order is placed, it can be queried using the client-side order ID to check the status. Updates on open orders at Alpaca will also be sent over the streaming interface, which is the recommended method of maintaining order state.

For further details on order functionality, please see the [Trading On Alpaca - Orders](https://alpaca.markets/docs/trading-on-alpaca/orders/) page.

For more information on the Orders API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/orders/.

### Positions API

The positions API provides information about an account’s current open positions. The response will include information such as cost basis, shares traded, and market value, which will be updated live as price information is updated. Once a position is closed, it will no longer be queryable through this API.

For more information on the Positions API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/positions/.

### Assets API

The assets API serves as the master list of assets available for trade and data consumption from Alpaca. Assets are sorted by asset class, exchange and symbol. Some assets are only available for data consumption via Polygon, and are not tradable with Alpaca. These `alpaca::Asset` objects will be marked with the `tradable` property set to `false`.

For more information on the Assets API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/assets/.

### Watchlist API

The watchlist API provides CRUD operation for the account’s watchlist. An account can have multiple watchlists and each is uniquely identified by id but can also be addressed by user-defined name. Each watchlist is an ordered list of assets.

For more information on the Watchlist API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/watchlist/.

### Calendar API

The calendar API serves the full list of market days from 1970 to 2029. It can also be queried by specifying a start and/or end time to narrow down the results. In addition to the dates, the response also contains the specific open and close times for the market days, taking into account early closures.

For more information on the Calendar API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/calendar/.

### Clock API

The clock API serves the current market timestamp, whether or not the market is currently open, as well as the times of the next market open and close.

For more information on the Clock API, see the official API documentation: https://alpaca.markets/docs/api-documentation/api-v2/clock/.
