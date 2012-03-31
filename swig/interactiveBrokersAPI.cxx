#include "interactiveBrokersAPI.h"

#include "EPosixClientSocket.h"
#include "EPosixClientSocketPlatform.h"

#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "Execution.h"
#include "ScannerSubscription.h"

const int PING_DEADLINE       = 5;
const int SLEEP_BETWEEN_PINGS = 30;

InteractiveBrokersAPIClient::InteractiveBrokersAPIClient(EWrapper *e)
    : m_pClient( new EPosixClientSocket(e) )
    , m_state(ST_DISCONNECTED)
    , m_sleepDeadline(0)
    , m_orderId(0)
{
#ifdef DEBUG
    std::cout << "C++ constructor" << std::endl;
#endif
}


InteractiveBrokersAPIClient::~InteractiveBrokersAPIClient()
{
    delete m_pClient;
    m_pClient = 0;
#ifdef DEBUG
    std::cout << "C++ destructor" << std::endl;
#endif
}

void InteractiveBrokersAPIClient::processMessages()
{

    fd_set readSet, writeSet, errorSet;

    struct timeval tval;
    tval.tv_usec = 0;
    tval.tv_sec = 0;

    time_t now = time(NULL);

    switch( m_state ) {
        case ST_PING:
            if( m_sleepDeadline < now ) {
                std::cerr << "Warning: Server ping timeout" << std::endl;
                eDisconnect();
                return;
            }
            break;
        case ST_IDLE:
            if( m_sleepDeadline < now ) {
                m_state = ST_PING;
                reqCurrentTime();
                // keep going and process this outgoing ping
                // return;
            }
            break;
        default:
            ;
    }

    //initialize select() timeout with m_sleepDeadline - now
    if( m_sleepDeadline > 0 )
    {
        tval.tv_sec = m_sleepDeadline - now;
    }

    if( m_pClient->fd() >= 0 )
    {
        FD_ZERO( &readSet );
        errorSet = writeSet = readSet;

        FD_SET( m_pClient->fd(), &readSet );

        if( !m_pClient->isOutBufferEmpty() )
            FD_SET( m_pClient->fd(), &writeSet );

        FD_CLR( m_pClient->fd(), &errorSet );

        int ret = select( m_pClient->fd() + 1,
                          &readSet, &writeSet, &errorSet, &tval );

        // timeout
        if( ret == 0 ) {  
            return;
        }

        // error
        if( ret < 0 ) {  
            eDisconnect();
            return;
        }

        if( m_pClient->fd() < 0 )
            return;

        if( FD_ISSET( m_pClient->fd(), &errorSet ) ) {
            // error on socket
            m_pClient->onError();
        }

        if( m_pClient->fd() < 0 )
            return;

        if( FD_ISSET( m_pClient->fd(), &writeSet ) ) {
            // socket is ready for writing
            m_pClient->onSend();
        }

        if( m_pClient->fd() < 0 )
            return;

        if( FD_ISSET( m_pClient->fd(), &readSet ) ) {
            // socket is ready for reading
            m_pClient->onReceive();
        }
    } 
}


bool InteractiveBrokersAPIClient::eConnect( const char *host, unsigned int port, int clientId )
{
    bool connectOk = false;

#ifdef DEBUG
    std::cout << "C++ eConnect()" << std::endl;
#endif
    m_state = ST_CONNECTING;
    connectOk = m_pClient->eConnect( host, port, clientId );
    if( connectOk )
        m_state = ST_IDLE;
    else
        m_state = ST_DISCONNECTED;

    return connectOk;
}

void InteractiveBrokersAPIClient::eDisconnect()
{
#ifdef DEBUG
    std::cout << "C++ eDisconnect()" << std::endl;
#endif
    m_pClient->eDisconnect();
    m_state = ST_DISCONNECTED;
}

bool InteractiveBrokersAPIClient::isConnected()
{
#ifdef DEBUG
    std::cout << "C++ isConnected()" << std::endl;
#endif
    return m_pClient->isConnected();
}

void InteractiveBrokersAPIClient::reqCurrentTime()
{
#ifdef DEBUG
    std::cout << "C++ reqCurrentTime()" << std::endl;
#endif
    // reset ping deadline to "now + n seconds"
    m_sleepDeadline = time( NULL) + PING_DEADLINE;

    m_pClient->reqCurrentTime();
}

int InteractiveBrokersAPIClient::serverVersion()
{
#ifdef DEBUG
    std::cout << "C++ reqCurrentTime()" << std::endl;
#endif
    return m_pClient->serverVersion();
}

void InteractiveBrokersAPIClient::setServerLogLevel( int logLevel )
{
#ifdef DEBUG
    std::cout << "C++ setServerLogLevel()" << std::endl;
#endif
    m_pClient->setServerLogLevel( logLevel );
}

void InteractiveBrokersAPIClient::checkMessages()
{
#ifdef DEBUG
    std::cout << "C++ checkMessages()" << std::endl;
#endif
    std::cerr << "Warning: Use processMessages() instead." << std::endl;
    processMessages();
}

IBString InteractiveBrokersAPIClient::TwsConnectionTime()
{
#ifdef DEBUG
    std::cout << "C++ TwsConnectionTime()" << std::endl;
#endif
    return m_pClient->TwsConnectionTime();
}


void InteractiveBrokersAPIClient::reqMktData( TickerId id, const Contract &contract,
                              const IBString& genericTicks, bool snapshot )
{
#ifdef DEBUG
    std::cout << "C++ reqMktData()" << std::endl;
#endif
    m_pClient->reqMktData( id, contract, genericTicks, snapshot );
}

void InteractiveBrokersAPIClient::cancelMktData( TickerId id )
{
#ifdef DEBUG
    std::cout << "C++ cancelMktData()" << std::endl;
#endif
    m_pClient->cancelMktData( id );
}

void InteractiveBrokersAPIClient::calculateImpliedVolatility( TickerId reqId,
                                              const Contract &contract,
                                              double optionPrice,
                                              double underPrice )
{
#ifdef DEBUG
    std::cout << "C++ calculateImpliedVolatility()" << std::endl;
#endif
    m_pClient->calculateImpliedVolatility( reqId, contract,
                                           optionPrice, underPrice );
}

void InteractiveBrokersAPIClient::cancelCalculateImpliedVolatility( TickerId reqId )
{
#ifdef DEBUG
    std::cout << "C++ cancelCalculateImpliedVolatility()" << std::endl;
#endif
    m_pClient->cancelCalculateImpliedVolatility( reqId );
}

void InteractiveBrokersAPIClient::calculateOptionPrice( TickerId reqId,
                                        const Contract &contract,
                                        double volatility,
                                        double underPrice )
{
#ifdef DEBUG
    std::cout << "C++ calculateOptionPrice()" << std::endl;
#endif
    m_pClient->calculateOptionPrice( reqId, contract, volatility, underPrice );
}

void InteractiveBrokersAPIClient::cancelCalculateOptionPrice( TickerId reqId )
{
#ifdef DEBUG
    std::cout << "C++ cancelCalculateOptionPrice()" << std::endl;
#endif
    m_pClient->cancelCalculateOptionPrice( reqId );
}

void InteractiveBrokersAPIClient::placeOrder( OrderId id, const Contract &contract,
                              const Order &order )
{
#ifdef DEBUG
    std::cout << "C++ placeOrder()" << std::endl;
#endif
    m_pClient->placeOrder( id, contract, order );
}

void InteractiveBrokersAPIClient::cancelOrder( OrderId id )
{
#ifdef DEBUG
    std::cout << "C++ cancelOrder()" << std::endl;
#endif
    m_pClient->cancelOrder( id );
}

void InteractiveBrokersAPIClient::reqOpenOrders()
{
#ifdef DEBUG
    std::cout << "C++ reqOpenOrders()" << std::endl;
#endif
    m_pClient->reqOpenOrders();
}

void InteractiveBrokersAPIClient::reqAllOpenOrders()
{
#ifdef DEBUG
    std::cout << "C++ reqAllOpenOrders()" << std::endl;
#endif
    m_pClient->reqAllOpenOrders();

}

void InteractiveBrokersAPIClient::reqAutoOpenOrders( bool bAutoBind )
{
#ifdef DEBUG
    std::cout << "C++ reqAutoOpenOrders()" << std::endl;
#endif
    m_pClient->reqAutoOpenOrders( bAutoBind );
}

void InteractiveBrokersAPIClient::reqIds( int numIds )
{
#ifdef DEBUG
    std::cout << "C++ reqIds()" << std::endl;
#endif
    m_pClient->reqIds( numIds );
}

void InteractiveBrokersAPIClient::exerciseOptions( TickerId id, const Contract &contract,
                                   int exerciseAction, int exerciseQuantity,
                                   const IBString &account, int override )
{
#ifdef DEBUG
    std::cout << "C++ exerciseOptions()" << std::endl;
#endif
    m_pClient->exerciseOptions( id, contract,
                                exerciseAction, exerciseQuantity,
                                account, override );
}

void InteractiveBrokersAPIClient::reqAccountUpdates( bool subscribe, const IBString& acctCode )
{
#ifdef DEBUG
    std::cout << "C++ reqAccountUpdates()" << std::endl;
#endif
    m_pClient->reqAccountUpdates( subscribe, acctCode );
}

void InteractiveBrokersAPIClient::reqExecutions( int reqId, const ExecutionFilter& filter )
{
#ifdef DEBUG
    std::cout << "C++ reqExecutions()" << std::endl;
#endif
    m_pClient->reqExecutions( reqId, filter );
}

void InteractiveBrokersAPIClient::reqContractDetails( int reqId, const Contract &contract )
{
#ifdef DEBUG
    std::cout << "C++ reqContractDetails()" << std::endl;
#endif
    m_pClient->reqContractDetails( reqId, contract );
}

void InteractiveBrokersAPIClient::reqMktDepth( TickerId id, const Contract &contract,
                               int numRows )
{
#ifdef DEBUG
    std::cout << "C++ reqMktDepth()" << std::endl;
#endif
    m_pClient->reqMktDepth( id, contract, numRows );
}

void InteractiveBrokersAPIClient::cancelMktDepth( TickerId id )
{
#ifdef DEBUG
    std::cout << "C++ cancelMktDepth()" << std::endl;
#endif
    m_pClient->cancelMktDepth( id );
}


void InteractiveBrokersAPIClient::reqNewsBulletins( bool allMsgs )
{
#ifdef DEBUG
    std::cout << "C++ reqNewsBulletins()" << std::endl;
#endif
    m_pClient->reqNewsBulletins( allMsgs );
}

void InteractiveBrokersAPIClient::cancelNewsBulletins()
{
#ifdef DEBUG
    std::cout << "C++ cancelNewsBulletins()" << std::endl;
#endif
    m_pClient->cancelNewsBulletins();
}

void InteractiveBrokersAPIClient::reqManagedAccts()
{
#ifdef DEBUG
    std::cout << "C++ reqManagedAccts()" << std::endl;
#endif
    m_pClient->reqManagedAccts();
}

void InteractiveBrokersAPIClient::requestFA( faDataType pFaDataType )
{
#ifdef DEBUG
    std::cout << "C++ requestFA()" << std::endl;
#endif
    m_pClient->requestFA( pFaDataType );
}

void InteractiveBrokersAPIClient::replaceFA( faDataType pFaDataType, const IBString& cxml )
{
#ifdef DEBUG
    std::cout << "C++ replaceFA()" << std::endl;
#endif
    m_pClient->replaceFA( pFaDataType, cxml );
}

void InteractiveBrokersAPIClient::reqHistoricalData( TickerId id, const Contract &contract,
                                     const IBString &endDateTime,
                                     const IBString &durationStr,
                                     const IBString &barSizeSetting,
                                     const IBString &whatToShow,
                                     int useRTH, int formatDate )
{
#ifdef DEBUG
    std::cout << "C++ reqHistoricalData()" << std::endl;
#endif
    m_pClient->reqHistoricalData( id, contract,
                                  endDateTime, durationStr,
                                  barSizeSetting, whatToShow,
                                  useRTH, formatDate );
}

void InteractiveBrokersAPIClient::cancelHistoricalData( TickerId tickerId )
{
#ifdef DEBUG
    std::cout << "C++ cancelHistoricalData()" << std::endl;
#endif
    m_pClient->cancelHistoricalData( tickerId );
}

void InteractiveBrokersAPIClient::reqScannerParameters()
{
#ifdef DEBUG
    std::cout << "C++ reqScannerParameters()" << std::endl;
#endif
    m_pClient->reqScannerParameters();
}

void InteractiveBrokersAPIClient::reqScannerSubscription( int tickerId,
                                     const ScannerSubscription &subscription )
{
#ifdef DEBUG
    std::cout << "C++ reqScannerSubscription()" << std::endl;
#endif
    m_pClient->reqScannerSubscription( tickerId, subscription );
}

void InteractiveBrokersAPIClient::cancelScannerSubscription( int tickerId )
{
#ifdef DEBUG
    std::cout << "C++ cancelScannerSubscription()" << std::endl;
#endif
    m_pClient->cancelScannerSubscription( tickerId );
}

void InteractiveBrokersAPIClient::reqRealTimeBars( TickerId id, const Contract &contract,
                                   int barSize, const IBString &whatToShow,
                                   bool useRTH )
{
#ifdef DEBUG
    std::cout << "C++ reqRealTimeBars()" << std::endl;
#endif
    m_pClient->reqRealTimeBars( id, contract, barSize, whatToShow, useRTH );
}

void InteractiveBrokersAPIClient::cancelRealTimeBars( TickerId tickerId )
{
#ifdef DEBUG
    std::cout << "C++ cancelRealTimeBars()" << std::endl;
#endif
    m_pClient->cancelRealTimeBars( tickerId );
}

void InteractiveBrokersAPIClient::reqFundamentalData( TickerId reqId, const Contract& contract,
                                      const IBString& reportType )
{
#ifdef DEBUG
    std::cout << "C++ reqFundamentalData()" << std::endl;
#endif
    m_pClient->reqFundamentalData( reqId, contract, reportType );
}

void InteractiveBrokersAPIClient::cancelFundamentalData( TickerId reqId )
{
#ifdef DEBUG
    std::cout << "C++ cancelFundamentalData()" << std::endl;
#endif
    m_pClient->cancelFundamentalData( reqId );
}
