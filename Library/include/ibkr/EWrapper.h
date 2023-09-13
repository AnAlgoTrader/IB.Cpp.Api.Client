/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EWRAPPER_H
#define TWS_API_CLIENT_EWRAPPER_H

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include "CommonDefs.h"
#include "SoftDollarTier.h"
#include "DepthMktDataDescription.h"
#include "FamilyCode.h"
#include "NewsProvider.h"
#include "TickAttrib.h"
#include "HistogramEntry.h"
#include "Bar.h"
#include "PriceIncrement.h"
#include "HistoricalTick.h"
#include "HistoricalTickBidAsk.h"
#include "HistoricalTickLast.h"
#include "Decimal.h"
#include "HistoricalSession.h"

enum TickType
{
	BID_SIZE,
	BID,
	ASK,
	ASK_SIZE,
	LAST,
	LAST_SIZE,
	HIGH,
	LOW,
	VOLUME,
	CLOSE,
	BID_OPTION_COMPUTATION,
	ASK_OPTION_COMPUTATION,
	LAST_OPTION_COMPUTATION,
	MODEL_OPTION,
	OPEN,
	LOW_13_WEEK,
	HIGH_13_WEEK,
	LOW_26_WEEK,
	HIGH_26_WEEK,
	LOW_52_WEEK,
	HIGH_52_WEEK,
	AVG_VOLUME,
	OPEN_INTEREST,
	OPTION_HISTORICAL_VOL,
	OPTION_IMPLIED_VOL,
	OPTION_BID_EXCH,
	OPTION_ASK_EXCH,
	OPTION_CALL_OPEN_INTEREST,
	OPTION_PUT_OPEN_INTEREST,
	OPTION_CALL_VOLUME,
	OPTION_PUT_VOLUME,
	INDEX_FUTURE_PREMIUM,
	BID_EXCH,
	ASK_EXCH,
	AUCTION_VOLUME,
	AUCTION_PRICE,
	AUCTION_IMBALANCE,
	MARK_PRICE,
	BID_EFP_COMPUTATION,
	ASK_EFP_COMPUTATION,
	LAST_EFP_COMPUTATION,
	OPEN_EFP_COMPUTATION,
	HIGH_EFP_COMPUTATION,
	LOW_EFP_COMPUTATION,
	CLOSE_EFP_COMPUTATION,
	LAST_TIMESTAMP,
	SHORTABLE,
	FUNDAMENTAL_RATIOS,
	RT_VOLUME,
	HALTED,
	BID_YIELD,
	ASK_YIELD,
	LAST_YIELD,
	CUST_OPTION_COMPUTATION,
	TRADE_COUNT,
	TRADE_RATE,
	VOLUME_RATE,
	LAST_RTH_TRADE,
	RT_HISTORICAL_VOL,
	IB_DIVIDENDS,
	BOND_FACTOR_MULTIPLIER,
	REGULATORY_IMBALANCE,
	NEWS_TICK,
	SHORT_TERM_VOLUME_3_MIN,
	SHORT_TERM_VOLUME_5_MIN,
	SHORT_TERM_VOLUME_10_MIN,
	DELAYED_BID,
	DELAYED_ASK,
	DELAYED_LAST,
	DELAYED_BID_SIZE,
	DELAYED_ASK_SIZE,
	DELAYED_LAST_SIZE,
	DELAYED_HIGH,
	DELAYED_LOW,
	DELAYED_VOLUME,
	DELAYED_CLOSE,
	DELAYED_OPEN,
	RT_TRD_VOLUME,
	CREDITMAN_MARK_PRICE,
	CREDITMAN_SLOW_MARK_PRICE,
	DELAYED_BID_OPTION_COMPUTATION,
	DELAYED_ASK_OPTION_COMPUTATION,
	DELAYED_LAST_OPTION_COMPUTATION,
	DELAYED_MODEL_OPTION_COMPUTATION,
	LAST_EXCH,
	LAST_REG_TIME,
	FUTURES_OPEN_INTEREST,
	AVG_OPT_VOLUME,
	DELAYED_LAST_TIMESTAMP,
	SHORTABLE_SHARES,
	DELAYED_HALTED,
	REUTERS_2_MUTUAL_FUNDS,
	ETF_NAV_CLOSE,
	ETF_NAV_PRIOR_CLOSE,
	ETF_NAV_BID,
	ETF_NAV_ASK,
	ETF_NAV_LAST,
	ETF_FROZEN_NAV_LAST,
	ETF_NAV_HIGH,
	ETF_NAV_LOW,
	SOCIAL_MARKET_ANALYTICS,
	ESTIMATED_IPO_MIDPOINT,
	FINAL_IPO_LAST,
	NOT_SET
};

typedef std::map<int, std::tuple<std::string, char>> SmartComponentsMap;
typedef std::vector<HistogramEntry> HistogramDataVector;

inline bool isPrice(TickType tickType)
{
	return tickType == BID || tickType == ASK || tickType == LAST
			|| tickType == DELAYED_BID || tickType == DELAYED_ASK
			|| tickType == DELAYED_LAST;
}

struct Contract;
struct ContractDetails;
struct ContractDescription;
struct Order;
struct OrderState;
struct Execution;
struct DeltaNeutralContract;
struct CommissionReport;

class EWrapper
{
	public:
		virtual ~EWrapper()
		{
		}
		;

		virtual void tickPrice(TickerId tickerId, TickType field, double price,
				const TickAttrib &attrib);
		virtual void tickSize(TickerId tickerId, TickType field, Decimal size);
		virtual void tickOptionComputation(TickerId tickerId, TickType tickType,
				int tickAttrib, double impliedVol, double delta,
				double optPrice, double pvDividend, double gamma, double vega,
				double theta, double undPrice);
		virtual void tickGeneric(TickerId tickerId, TickType tickType,
				double value);
		virtual void tickString(TickerId tickerId, TickType tickType,
				const std::string &value);
		virtual void tickEFP(TickerId tickerId, TickType tickType,
				double basisPoints, const std::string &formattedBasisPoints,
				double totalDividends, int holdDays,
				const std::string &futureLastTradeDate, double dividendImpact,
				double dividendsToLastTradeDate);
		virtual void orderStatus(OrderId orderId, const std::string &status,
				Decimal filled, Decimal remaining, double avgFillPrice,
				int permId, int parentId, double lastFillPrice, int clientId,
				const std::string &whyHeld, double mktCapPrice);
		virtual void openOrder(OrderId orderId, const Contract&, const Order&,
				const OrderState&);
		virtual void openOrderEnd();
		virtual void winError(const std::string &str, int lastError);
		virtual void connectionClosed();
		virtual void updateAccountValue(const std::string &key,
				const std::string &val, const std::string &currency,
				const std::string &accountName);
		virtual void updatePortfolio(const Contract &contract, Decimal position,
				double marketPrice, double marketValue, double averageCost,
				double unrealizedPNL, double realizedPNL,
				const std::string &accountName);
		virtual void updateAccountTime(const std::string &timeStamp);
		virtual void accountDownloadEnd(const std::string &accountName);
		virtual void nextValidId(OrderId orderId);
		virtual void contractDetails(int reqId,
				const ContractDetails &contractDetails);
		virtual void bondContractDetails(int reqId,
				const ContractDetails &contractDetails);
		virtual void contractDetailsEnd(int reqId);
		virtual void execDetails(int reqId, const Contract &contract,
				const Execution &execution);
		virtual void execDetailsEnd(int reqId);
		virtual void error(int id, int errorCode,
				const std::string &errorString,
				const std::string &advancedOrderRejectJson);
		virtual void updateMktDepth(TickerId id, int position, int operation,
				int side, double price, Decimal size);
		virtual void updateMktDepthL2(TickerId id, int position,
				const std::string &marketMaker, int operation, int side,
				double price, Decimal size, bool isSmartDepth);
		virtual void updateNewsBulletin(int msgId, int msgType,
				const std::string &newsMessage, const std::string &originExch);
		virtual void managedAccounts(const std::string &accountsList);
		virtual void receiveFA(faDataType pFaDataType, const std::string &cxml);
		virtual void historicalData(TickerId reqId, const Bar &bar);
		virtual void historicalDataEnd(int reqId,
				const std::string &startDateStr, const std::string &endDateStr);
		virtual void scannerParameters(const std::string &xml);
		virtual void scannerData(int reqId, int rank,
				const ContractDetails &contractDetails,
				const std::string &distance, const std::string &benchmark,
				const std::string &projection, const std::string &legsStr);
		virtual void scannerDataEnd(int reqId);
		virtual void realtimeBar(TickerId reqId, long time, double open,
				double high, double low, double close, Decimal volume,
				Decimal wap, int count);
		virtual void currentTime(long time);
		virtual void fundamentalData(TickerId reqId, const std::string &data);
		virtual void deltaNeutralValidation(int reqId,
				const DeltaNeutralContract &deltaNeutralContract);
		virtual void tickSnapshotEnd(int reqId);
		virtual void marketDataType(TickerId reqId, int marketDataType);
		virtual void commissionReport(const CommissionReport &commissionReport);
		virtual void position(const std::string &account,
				const Contract &contract, Decimal position, double avgCost);
		virtual void positionEnd();
		virtual void accountSummary(int reqId, const std::string &account,
				const std::string &tag, const std::string &value,
				const std::string &curency);
		virtual void accountSummaryEnd(int reqId);
		virtual void verifyMessageAPI(const std::string &apiData);
		virtual void verifyCompleted(bool isSuccessful,
				const std::string &errorText);
		virtual void displayGroupList(int reqId, const std::string &groups);
		virtual void displayGroupUpdated(int reqId,
				const std::string &contractInfo);
		virtual void verifyAndAuthMessageAPI(const std::string &apiData,
				const std::string &xyzChallange);
		virtual void verifyAndAuthCompleted(bool isSuccessful,
				const std::string &errorText);
		virtual void connectAck();
		virtual void positionMulti(int reqId, const std::string &account,
				const std::string &modelCode, const Contract &contract,
				Decimal pos, double avgCost);
		virtual void positionMultiEnd(int reqId);
		virtual void accountUpdateMulti(int reqId, const std::string &account,
				const std::string &modelCode, const std::string &key,
				const std::string &value, const std::string &currency);
		virtual void accountUpdateMultiEnd(int reqId);
		virtual void securityDefinitionOptionalParameter(int reqId,
				const std::string &exchange, int underlyingConId,
				const std::string &tradingClass, const std::string &multiplier,
				const std::set<std::string> &expirations,
				const std::set<double> &strikes);
		virtual void securityDefinitionOptionalParameterEnd(int reqId);
		virtual void softDollarTiers(int reqId,
				const std::vector<SoftDollarTier> &tiers);
		virtual void familyCodes(const std::vector<FamilyCode> &familyCodes);
		virtual void symbolSamples(int reqId,
				const std::vector<ContractDescription> &contractDescriptions);
		virtual void mktDepthExchanges(
				const std::vector<DepthMktDataDescription> &depthMktDataDescriptions);
		virtual void tickNews(int tickerId, time_t timeStamp,
				const std::string &providerCode, const std::string &articleId,
				const std::string &headline, const std::string &extraData);
		virtual void smartComponents(int reqId,
				const SmartComponentsMap &theMap);
		virtual void tickReqParams(int tickerId, double minTick,
				const std::string &bboExchange, int snapshotPermissions);
		virtual void newsProviders(
				const std::vector<NewsProvider> &newsProviders);
		virtual void newsArticle(int requestId, int articleType,
				const std::string &articleText);
		virtual void historicalNews(int requestId, const std::string &time,
				const std::string &providerCode, const std::string &articleId,
				const std::string &headline);
		virtual void historicalNewsEnd(int requestId, bool hasMore);
		virtual void headTimestamp(int reqId, const std::string &headTimestamp);
		virtual void histogramData(int reqId, const HistogramDataVector &data);
		virtual void historicalDataUpdate(TickerId reqId, const Bar &bar);
		virtual void rerouteMktDataReq(int reqId, int conid,
				const std::string &exchange);
		virtual void rerouteMktDepthReq(int reqId, int conid,
				const std::string &exchange);
		virtual void marketRule(int marketRuleId,
				const std::vector<PriceIncrement> &priceIncrements);
		virtual void pnl(int reqId, double dailyPnL, double unrealizedPnL,
				double realizedPnL);
		virtual void pnlSingle(int reqId, Decimal pos, double dailyPnL,
				double unrealizedPnL, double realizedPnL, double value);
		virtual void historicalTicks(int reqId,
				const std::vector<HistoricalTick> &ticks, bool done);
		virtual void historicalTicksBidAsk(int reqId,
				const std::vector<HistoricalTickBidAsk> &ticks, bool done);
		virtual void historicalTicksLast(int reqId,
				const std::vector<HistoricalTickLast> &ticks, bool done);
		virtual void tickByTickAllLast(int reqId, int tickType, time_t time,
				double price, Decimal size,
				const TickAttribLast &tickAttribLast,
				const std::string &exchange,
				const std::string &specialConditions);
		virtual void tickByTickBidAsk(int reqId, time_t time, double bidPrice,
				double askPrice, Decimal bidSize, Decimal askSize,
				const TickAttribBidAsk &tickAttribBidAsk);
		virtual void tickByTickMidPoint(int reqId, time_t time,
				double midPoint);
		virtual void orderBound(long long orderId, int apiClientId,
				int apiOrderId);
		virtual void completedOrder(const Contract &contract,
				const Order &order, const OrderState &orderState);
		virtual void completedOrdersEnd();
		virtual void replaceFAEnd(int reqId, const std::string &text);
		virtual void wshMetaData(int reqId, const std::string &dataJson);
		virtual void wshEventData(int reqId, const std::string &dataJson);
		virtual void historicalSchedule(int reqId,
				const std::string &startDateTime,
				const std::string &endDateTime, const std::string &timeZone,
				const std::vector<HistoricalSession> &sessions);
		virtual void userInfo(int reqId, const std::string &whiteBrandingId);
};

#endif
