#!/bin/bash

function doit(){
	for file in `ls $1`
	do
		name=$1"/"${file}
		#echo $name
		if [ -d $name ]
		then
			doit $name
		else 
			tmp=$(dirname $name)
			tmp2=$(dirname $tmp)
			project_name="${tmp2##*/}"
            main="${path##*/}"
			if [ "$project_name" !=  "$main" ]
			then
				echo $name goto up
				cp $name $tmp2
				echo $tmp2
			fi
		fi
	done
}

path=$(cd $(dirname $0); pwd)
doit $path
