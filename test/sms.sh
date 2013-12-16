#!/bin/bash           
########################################  
# Homepage: http://netkiller.github.io  
# Author: neo <netkiller@msn.com>  
########################################  
NAME=demo
PIPE=/tmp/myfifo
########################################  
LOGFILE=/tmp/$NAME.log
PIDFILE=/tmp/${NAME}.pid
########################################  

function start(){
	if [ -f "$PIDFILE" ]; then
		exit 2
	fi

        if [ ! -f "$LOGFILE" ]; then
                > ${LOGFILE}
        fi

	for (( ; ; ))
	do
            while read line   
            do  

                NOW=$(date '+%Y-%m-%d %H:%M:%S')
                echo "[${NOW}] [OK] ${line}" >> ${LOGFILE}

            done < $PIPE  
	done &
	echo $! > $PIDFILE
}
function stop(){
  	[ -f $PIDFILE ] && kill `cat $PIDFILE` && rm -rf $PIDFILE
}

case "$1" in
  start)
  	start
	;;
  stop)
  	stop
	;;
  status)
  	ps ax | grep ${0} | grep -v grep | grep -v status
	;;
  restart)
  	stop
	start
	;;
  *)
	echo $"Usage: $0 {start|stop|status|restart}"
	exit 2
esac

exit $? 
