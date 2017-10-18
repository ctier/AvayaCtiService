
#pragma once

enum AgentState {
	asNone = -1,	// exception
	asNotReady = 0,	// Not Ready State for Agent
	asNull = 1,		// Agent is not logged in
	asReady = 2,	// Agent is in ready State
	asWorkNotReady = 3	// Agent is in Work Not Ready State ( BUSY )
	} ;

enum AgentTalkState{
	atsNone = 0,
	atsIdle = 1,		// Idle :  Agent is available for handling a call
	atsOnCall = 2		// OnCall : Agent is handling a Call
	};


class AgentStateObserver
{
public:
	/// <summary>
	/// This is abstract method that is used by the AgentStateUI class for displaying Agent State 
	/// and Agent Talk State. 
	/// </summary>
	/// <param name="agentState">Represent agent's current state i.e. Ready, NotReady etc</param>
	/// <param name="agentTalkState">Represent agent's current talk state i.e. Idle, OnCall.</param>
	virtual void Notify( AgentState agentState, AgentTalkState  agentTalkState)= 0;	
};

/*
Name: 
Description:
Parameter:
*/