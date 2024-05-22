#pragma once
#ifndef IMPTIMER_H_
#define IMPTIMER_H_

class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();


	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();

private:
	int start_tick;
	int pause_tick;

	bool is_paused_;
	bool is_started_;
};

#endif // !IMPTIMER_H_
