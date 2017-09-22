#!/bin/sh

help() {
	
	echo "$0 action [interface]"
	echo ""
	echo "help   show this help"
	echo "start  load the kernel module for virtual can"
	echo "stop   unload the kernel module"
	echo "up     start virtual can interface"
	echo "down   stop virtual can interface"
	echo ""
}

start() {
# loads the kernel module
	
	sudo modprobe vcan
	
	echo "VCAN kernel module loaded"
}

stop() {
# unloads the kernel module
	
	sudo modprobe -r vcan
	
	echo "VCAN kernel module unloaded"
}

up() {
# bring up a virtual can device
# $1: interface
	
	local iface=$1
	echo "Start interface $iface..."
	
	sudo ip link add dev $iface type vcan
	sudo ip link set up $iface
}

down() {
# bring up a virtual can device
# $1: interface
	
	local iface=$1
	echo "Stop interface $iface"
	
	sudo ip link set down $iface
	sudo ip link delete dev $iface type vcan
}

check_iface() {
# check if interface name ok
# $1: interface
	
	local iface="$1"
	
	if [ "X$iface" = "X" ]; then
		echo "No interface defined"
		exit 4
	fi
	
	return 0
}

check_if_up() {
# check if the interface is already up
# $1: interface
	
	local iface="$1"
	
	if [ "$(ifconfig | grep $iface)" != "" ]; then
		echo "Interface $iface already started"
		exit 5
	fi
	
	return 0
}

action="$1"
interface="$2"
if [ "X$action" = "X" ]; then
	echo ""
	echo "Define action"
	echo ""
	help
	exit 1
fi

if [ "$action" = "help" ]; then
	help
	exit 0
fi

if [ "$(id -g)" != "0" ]; then
	echo ""
	echo "Please run as root"
	echo ""
	help
	exit 2
fi

case $action in
	"start") start;;
	"stop")  stop ;;
	"up")    check_iface $interface; check_if_up $interface; up $interface;;
	"down")  check_iface $interface; down $interface;;
	*)       help; exit 3;;
esac

exit 0