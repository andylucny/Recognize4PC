#ifndef BOEBOT_CONTROL_H
#define BOEBOT_CONTROL_H

#include <string>
using namespace std;

class BoeBotControl
{
public:
	BoeBotControl (string serialPort);
	~BoeBotControl ();
	bool opened ();
	void forward ();
	void backward ();
	void rotateLeft ();
	void rotateRight ();
	void stop ();
private:
  int fd;
  void sendToLine(string data);
};

#endif // BOEBOT_CONTROL_H