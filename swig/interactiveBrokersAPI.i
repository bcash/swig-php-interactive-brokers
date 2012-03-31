
%module(directors="1") "InteractiveBrokersAPI"
 
%{

#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "Execution.h"
#include "ScannerSubscription.h"
#include "EWrapper.h"
#include "EClient.h"
#include "EClientSocketBase.h"
#include "EPosixClientSocket.h"

#include "interactiveBrokersAPI.h"

%}

%include "std_vector.i"
%include "std_string.i"

%rename(ComboLegEqual) ComboLeg::operator==(const ComboLeg& other) const; 
%apply std::string { IBString }
typedef std::string IBString;
typedef long TickerId;
typedef long OrderId;

#if 1
%typemap(directorin) IBString const %{
  ZVAL_STRINGL($input, $1_name.c_str(), $1_name.length(),  1);
%}
# endif

%feature("director") EWrapper;

%include "Contract.h"
%include "Order.h"
%include "OrderState.h"
%include "Execution.h"
%include "ScannerSubscription.h"
%include "EWrapper.h"
%import "EClient.h"
%import "EClientSocketBase.h"
%include "EPosixClientSocket.h"


%include "interactiveBrokersAPI.h"

