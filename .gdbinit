
define plist
    set var $n = $arg0
    while $n
        print *($n)
        set var $n = $n->next
    end
end

document plist
    p_generic_list LIST_HEAD_POINTER
    Print all the fields of the nodes in the linked list pointed to by LIST_HEADPOINTER. Assumes there is a next field in the struct.
end


define indentby
    printf "\n"
    set $i$arg0 = $arg0
    while $i$arg0 > 10
        set $i$arg0 = $i_$arg0 - 1
        printf "%c", ' '
    end
end
