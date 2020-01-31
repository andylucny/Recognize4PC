#include "BoeBotControl.h"
#include "serial.h"

BoeBotControl::BoeBotControl (string serialPort)
{
  printf("control starting...\n");
	fd = openLine(serialPort.c_str());
}

BoeBotControl::~BoeBotControl ()
{
  closeLine(fd);
}

bool BoeBotControl::opened ()
{
  return (fd >= 0);
}

void BoeBotControl::sendToLine (string data)
{
  writeToLine(fd, data.c_str(), data.length());
}

void BoeBotControl::forward ()
{
	sendToLine("pf\r");
}

void BoeBotControl::backward ()
{
	sendToLine("pb\r");
}

void BoeBotControl::rotateLeft ()
{
	sendToLine("pl\r");
}

void BoeBotControl::rotateRight ()
{
	sendToLine("pr\r");
}

void BoeBotControl::stop ()
{
	sendToLine("pz\r");
}
