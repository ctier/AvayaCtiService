/* This class defines the enums
*	Call / Connection State.
*	Agent State and Agent Talk State.
*	This class also defines the abstract method for notifying the AgentStateUI class
*/
#pragma once

enum  connectionState {
	conNone = -1,	// exception
	conNull = 0,	
	conInitiate = 1,	// Call Initiated
	conAlerting = 2,	// Call is delivered
	conConnect = 3,		// Call is established
	conConfer = 4,		// Conference Call
	conTransfer = 5,	// Transfer Call
	conHold = 6,		// Call on Hold
	conReterieved = 7	// Call reterieved
} ;

enum callState {
	caActive = 1,		// Call is Active
	caInvalid = 0,		// Call is Invalid
	caIdle = 2			// No call
} ;
class CallStateObserver
{
public:
	// This is abstract method that is used by the AgentStateUI class for displaying Call details
	virtual void Notify(long, callState , connectionState, char [], char [] , char []) = 0;		

};
