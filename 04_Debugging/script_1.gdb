set pagination off
b 29 if i % 5 == 0
command 1
        echo @@@
        p start
        echo @@@
        p stop
        echo @@@
        p step
        echo @@@
        p i
end

run
quit