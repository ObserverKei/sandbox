#!/bin/bash

g_fff=09

fn_cat_memery()
{
	local cmd=cat_info
	echo $cmd
}

fn_cat_info()
{
	echo "cat info, run:$$"
}

h_cat_self()
{
	local __see=/tmp/sandbox_cat_see.log
	local __work=/tmp/sandbox_cat_work.log
	local __time=/time/sandbox_cat_time.log
	local __fn_info=fn_cat_info
	local __fn_memery=fn_cat_memery

	case $1 in
		see) echo $__see;;
		work) echo $__work;;
		time) echo $__time;;
		fn_info) echo $__fn_info;;
		fn_memery) echo $__fn_memery;;
		*) echo ;;
	esac
}

echo "$(ls)"


h_cat_self see|
h_cat_self work|
h_cat_self time|
h_cat_self info|

$(h_cat_self fn_memery)|

`h_cat_self fn_info`
echo $(h_cat_self see)


exit 0
