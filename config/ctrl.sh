#!/bin/bash
#created by wangfengliang

#Source function library.
. /etc/rc.d/init.d/functions

#Check that networking is up.
if [ "$NETWORKING" = "no" ]
then
    exit 0
fi

WORKDIR=$(cd `dirname $0`; pwd)

if [ "$HOSTNAME" == "" ];then
    HOSTNAME=`hostname`
fi

SERVICE=`cat $WORKDIR/config.json | fgrep '"SERVICE"' | awk -F'"' '{print $(NF-1)}'`
if [ x"$SERVICE" == x"" ]; then
    echo "SERVICE not defined"
    exit 1
fi

ICENODENAME="$SERVICE@$HOSTNAME"
SERVER_NAME="$ICENODENAME"

RETVAL=0

ulimit -c unlimited
. ${WORKDIR}/setenv.sh

start(){
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server start $SERVER"
    RETVAL=$?
    if [ $RETVAL -ne 0 ] ; then
        action "start $SERVER fail......"  /bin/false
        exit 1
    else
        action "start $SERVER success......"  /bin/true
    fi
}

stop(){
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server stop $SERVER"
    RETVAL=$?
    if [ $RETVAL -ne 0 ] ; then
        action "stop $SERVER fail......"  /bin/false
        exit 1
    else
        action "stop $SERVER success......"  /bin/true
    fi
}

list(){
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server list" | fgrep $SERVER
}

add_app() {
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "application add $WORKDIR/application.xml"
}

update_app() {
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "application update $WORKDIR/application.xml"
}

disable() {
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server disable $SERVER"
}
stop_disable() {
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server disable $SERVER; server stop $SERVER"
    RETVAL=$?
    if [ $RETVAL -ne 0 ] ; then
        action "stop $SERVER fail......"  /bin/false
        exit 1
    else
        action "stop $SERVER success......"  /bin/true
    fi

}

enable() {
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server enable $SERVER"
}

start_enable() {
    SERVER=$1
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server enable $SERVER; server start $SERVER"
    RETVAL=$?
    if [ $RETVAL -ne 0 ] ; then
        action "start $SERVER fail......"  /bin/false
        exit 1
    else
        action "start $SERVER success......"  /bin/true
    fi

}

status() {
    SERVER=$1
    if [ "x$SERVER" == "x" ];then
        action "Usage: $0 SERVER"  /bin/false
        exit 1
    fi
    icegridadmin --Ice.Config=$WORKDIR/ice.admin.conf -e "server describe $SERVER; server state $SERVER"
}

#See how we were called.
case "$1" in
  add)
    add_app
    ;;
  update)
    update_app
    ;;
  start)
    start $SERVER_NAME
    ;;
  stop)
    stop $SERVER_NAME
    ;;
  enable)
    enable $SERVER_NAME
    ;;
  disable)
    disable $SERVER_NAME
    ;;
  status)
    status $SERVER_NAME
    ;;
  list)
    list $SERVICE
    ;;
  start_enable)
    start_enable $SERVER_NAME
    ;;
  stop_disable)
    stop_disable $SERVER_NAME
    ;;
  *)
    echo "Usage: $0 {add|update|start|stop|disable|enable|status|list|start_enable|stop_disable}"
    exit 1
esac

exit 0
