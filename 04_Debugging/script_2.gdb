set pagination off

set $count = 0

b range.c:29 if $count <= 35
    command 1
    silent

    if $count >= 28
        echo @@@
        p start
        echo @@@
        p stop
        echo @@@
        p step
        echo @@@
        p i
    end

    set $count = $count + 1
    continue
end

run
quit