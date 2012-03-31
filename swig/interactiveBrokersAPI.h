#ifndef INTERACTIVEBROKERSAPI_H
#define INTERACTIVEBROKERSAPI_H

#include "CommonDefs.h"
#include "Contract.h"
#include "Order.h"
#include "Execution.h"
#include "ScannerSubscription.h"

#include "EWrapper.h"

#include <iostream>
#include <memory>

class EPosixClientSocket;

enum State {
    ST_DISCONNECTED,
    ST_CONNECTING,
    ST_IDLE,
    ST_PING
};


class InteractiveBrokersAPIClient
{
  public:
    InteractiveBrokersAPIClient(EWrapper *e);
    ~InteractiveBrokersAPIClient();

    void processMessages();

    bool eConnect( const char * host, unsigned int port, int clientId = 0 );
    void eDisconnect();
    bool isConnected();
    void reqCurrentTime();
    int serverVersion();
    void setServerLogLevel( int logLevel );
    void checkMessages();
    IBString TwsConnectionTime();

    void reqMktData( TickerId id, const Contract &contract,
                     const IBString& genericTicks, bool snapshot );
    void cancelMktData( TickerId id );
    void calculateImpliedVolatility( TickerId reqId, const Contract &contract,
                                     double optionPrice, double underPrice );
    void cancelCalculateImpliedVolatility( TickerId reqId );
    void calculateOptionPrice( TickerId reqId, const Contract &contract,
                               double volatility, double underPrice );
    void cancelCalculateOptionPrice( TickerId reqId );

    void placeOrder( OrderId id, const Contract &contract, const Order &order );
    void cancelOrder( OrderId id );
    void reqOpenOrders();
    void reqAllOpenOrders();
    void reqAutoOpenOrders( bool bAutoBind );
    void reqIds( int numIds );
    void exerciseOptions( TickerId id, const Contract &contract,
                          int exerciseAction, int exerciseQuantity,
                          const IBString &account, int override );
  

    void reqAccountUpdates( bool subscribe, const IBString& acctCode );

    void reqExecutions( int reqId, const ExecutionFilter& filter );

    void reqContractDetails( int reqId, const Contract &contract );

    void reqMktDepth( TickerId id, const Contract &contract, int numRows );
    void cancelMktDepth( TickerId id );

    void reqNewsBulletins( bool allMsgs );
    void cancelNewsBulletins();

    void reqManagedAccts();
    void requestFA( faDataType pFaDataType );
    void replaceFA( faDataType pFaDataType, const IBString& cxml );

    void reqHistoricalData( TickerId id, const Contract &contract,
                            const IBString &endDateTime,
                            const IBString &durationStr,
                            const IBString &barSizeSetting,
                            const IBString &whatToShow, int useRTH,
                            int formatDate );

    void cancelHistoricalData( TickerId tickerId );

    void reqScannerParameters();
    void reqScannerSubscription( int tickerId,
                                 const ScannerSubscription &subscription);
    void cancelScannerSubscription( int tickerId );

    void reqRealTimeBars( TickerId id, const Contract &contract, int barSize,
                          const IBString &whatToShow, bool useRTH );
    void cancelRealTimeBars( TickerId tickerId );

    void reqFundamentalData( TickerId reqId, const Contract& contract,
                             const IBString& reportType );

    void cancelFundamentalData( TickerId reqId );

private:
    EPosixClientSocket *m_pClient;
    State m_state;
    time_t m_sleepDeadline;

    OrderId m_orderId;

};

#endif

