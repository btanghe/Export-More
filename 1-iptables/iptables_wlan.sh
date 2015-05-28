#!/bin/sh
# based on http://www.revsys.com/writings/quicktips/nat.html
# wlan0 is the interface to internet, eth0 to the raspberry pi

echo 1 > /proc/sys/net/ipv4/ip_forward

iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE
iptables -A FORWARD -i wlan0 -o eth0 -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -i eth0 -o wlan0 -j ACCEPT
