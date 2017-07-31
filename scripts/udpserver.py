#!/usr/bin/env python
import rospy
from little_bots.msg import botMsg


import socket


UDP_PORT = 1112
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # UDP


def CMD_CB(data):
	for i in range(0,data.num_players):
		forward = int((-data.velocity[i])+100)
		turning = int((data.turning[i])+100)
		UDP_message = str(forward) + ":" + str(turning)
		print UDP_message 
		sock.sendto(UDP_message, (data.ip[i], UDP_PORT))
	

   
def udpserver():
	rospy.init_node('udpserver')

	rospy.Subscriber("botCMD", botMsg, CMD_CB)
	rospy.spin()


if __name__ == '__main__':
    udpserver()