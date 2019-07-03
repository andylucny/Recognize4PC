# Recognize4PC
Android application for transmission of voice commands in form of text into destination device via TCP

User is asked for IP address and port of TCP server (entered as e.g. 192.168.1.2:8000) and connect to the server. 
Then user can click button Speak and record some voice. That voice is sent to Google cloud for Text-To-Speech translation
and returned text is written into the opened socket.

We use the application to make remote control of robot more attractive for student dealing with programming of Raspberry Pi3 
or other board equipped with WIFI. For connection we can use wireless LAN in classroom or access point in the mobile phone 
(in this case use e.g. Fing to find IP of the robot). Students in fact program text based control, but with this apk 
it is turned to voice control. Example of such student project is in directory VoiceControl.

The easiest way how install apk in the mobile phone is to install Total Commander into mobile phone and open by it the apk file
transferred somewhere to mobile phone filesystem.

cite <a href="https://www.researchgate.net/publication/332031468_Easy_Controlling_a_Robot_Using_Voice_for_Hobbyists">Lúčny, A. (2019). Easy Controlling a Robot using Voice for Hobbiests. Reserchgate.net, DOI: 10.13140/RG.2.2.25215.25761</a>
